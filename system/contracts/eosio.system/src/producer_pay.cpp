#include <eosio.system/eosio.system.hpp>

#include <eosio.token/eosio.token.hpp>

namespace eosiosystem {

   const int64_t  min_pervote_daily_pay = 100'0000;
   const int64_t  min_activated_stake   = 1'0000;
   const double   continuous_rate       = 0.0004879;          // 0.05% annual rate
   const double   perblock_rate         = 0.0025;           // 0.25%
   const double   standby_rate          = 0.0075;           // 0.75%
   const uint32_t blocks_per_year       = 52*7*24*2*3600;   // half seconds per year
   const uint32_t seconds_per_year      = 52*7*24*3600;
   const uint32_t blocks_per_day        = 2 * 24 * 3600;
   const uint32_t blocks_per_hour       = 2 * 3600;
   const int64_t  useconds_per_day      = 24 * 3600 * int64_t(1000000);
   const int64_t  useconds_per_year     = seconds_per_year*1000000ll;

   void system_contract::onblock( ignore<block_header> ) {
      using namespace eosio;

      require_auth(_self);
      
      update();

      action(
         permission_level{ _self, "active"_n },
         p2p_account, "uprate"_n,
         std::make_tuple( token_account, asset(0,core_symbol())) 
      ).send();
      
      block_timestamp timestamp;
      name producer;
      _ds >> timestamp >> producer;

      // if( timestamp.slot - _gstate.last_producer_schedule_update.slot > 120 ){
      //    checkstatus();
      // };
      

      // _gstate2.last_block_num is not used anywhere in the system contract code anymore.
      // Although this field is deprecated, we will continue updating it for now until the last_block_num field
      // is eventually completely removed, at which point this line can be removed.
      _gstate2.last_block_num = timestamp;
      
      if( (_gstate.thresh_activated_stake_time == time_point({ microseconds{0}}))  
         || (_gstate.thresh_activated_stake_time >= current_time_point() ))
      {
         return;
      } 

      if( _gstate.last_pervote_bucket_fill == time_point() )  /// start the presses
         _gstate.last_pervote_bucket_fill = current_time_point();

      const auto ct = current_time_point();
      const auto usecs_since_last_fill = (ct - _gstate.last_pervote_bucket_fill).count();

      if( usecs_since_last_fill > 0 && _gstate.last_pervote_bucket_fill > time_point() ) {
         emit(timestamp);
      }
      
            /**
       * At startup the initial producer may not be one that is registered / elected
       * and therefore there may be no producer object for them.
       */
      auto prod = _producers.find( producer.value );
      if ( prod != _producers.end() ) {
         _gstate.total_unpaid_blocks++;
         _producers.modify( prod, same_payer, [&](auto& p ) {
            p.unpaid_blocks++;
         });
      }


      


      /// only update block producers once every minute, block_timestamp is in half seconds
      if( timestamp.slot - _gstate.last_producer_schedule_update.slot > 120 ) {

         update_elected_producers( timestamp );

         if( (timestamp.slot - _gstate.last_name_close.slot) > blocks_per_day ) {
            name_bid_table bids(_self, _self.value);
            auto idx = bids.get_index<"highbid"_n>();
            auto highest = idx.lower_bound( std::numeric_limits<uint64_t>::max()/2 );
            if( highest != idx.end() &&
                highest->high_bid > 0 &&
                (current_time_point() - highest->last_bid_time) > microseconds(useconds_per_day) &&
                _gstate.thresh_activated_stake_time > time_point()
            ) {
               _gstate.last_name_close = timestamp;
               channel_namebid_to_rex( highest->high_bid );
               idx.modify( highest, same_payer, [&]( auto& b ){
                  b.high_bid = -b.high_bid;
               });
            }
         }
      }
   }

   using namespace eosio;


   void system_contract::emit( block_timestamp timestamp) {
      require_auth( _self );
      
      const auto ct = current_time_point();
      const asset token_supply   = eosio::token::get_supply(token_account, core_symbol().code() );
      const asset max_token_supply   = eosio::token::get_max_supply(token_account, core_symbol().code() );
      
      uint64_t new_tokens = _commstate.new_tokens_per_block;
      print("on emit: ", new_tokens);
      if (new_tokens > 0) {

         // if (max_token_supply.amount - token_supply.amount < new_tokens)                  
         //    new_tokens = max_token_supply.amount - token_supply.amount;
         
         auto to_producers = new_tokens; 
         auto to_per_block_pay = uint64_t((double)to_producers * (double)_commstate.per_block_pay_percent / 100);
         auto to_per_vote_pay  = uint64_t((double)to_producers * (double)_commstate.per_vote_pay_percent / 100);
         
      
         if (to_per_block_pay > 0){
            INLINE_ACTION_SENDER(eosio::token, transfer)(
               token_account, { {saving_account, active_permission} },
               { saving_account, bpay_account, asset(to_per_block_pay, core_symbol()), "fund per-block bucket" }
            );
         };

         if (to_per_vote_pay){
            INLINE_ACTION_SENDER(eosio::token, transfer)(
               token_account, { {saving_account, active_permission} },
               { saving_account, vpay_account, asset(to_per_vote_pay, core_symbol()), "fund per-vote bucket" }
            );
         };
         
         _gstate.pervote_bucket          += to_per_vote_pay;
         _gstate.perblock_bucket         += to_per_block_pay;
         _gstate.last_pervote_bucket_fill = ct;
         
      }
      /**
       * SPREAD MODULE
       * enabled / disabled
       * emit_amount
       * prods_amount
       * to_rotation / to_funds (%)
       * 
       */

      if (_commstate.spraying_enabled == true) { 
         
         emission_index emission(_self, _self.value);

         // auto to_rotation = _commstate.new_tokens_for_spraying * 100 / _commstate.spraying_rotation_percent / 100; 
         // auto to_funds = _commstate.new_tokens_for_spraying * 100 / _commstate.spraying_core_funds_percent / 100; 
   
         auto to_rotation = uint64_t((double)_commstate.new_tokens_for_spraying * (double)_commstate.spraying_rotation_percent / 100); 
         auto to_funds = uint64_t((double)_commstate.new_tokens_for_spraying * (double)_commstate.spraying_core_funds_percent / 100); 
                  
         auto em = emission.find(0);

         if (em == emission.end()) {
            
            emission.emplace(_self, [&](auto &e){
               e.id = 0;
               e.last_emission_at = timestamp;
            });
      
            if (to_funds > 0) {
               INLINE_ACTION_SENDER(eosio::token, transfer) (
                   token_account, { {saving_account, active_permission} },
                   { saving_account, core_account, asset(to_funds, core_symbol()), std::string("111-" + (name{_commstate.core_host}.to_string()) + "-" + (name{_commstate.core_host}.to_string()))}
               );
            }

            if (to_rotation > 0) {
               INLINE_ACTION_SENDER(eosio::token, transfer)(
                   token_account, { {saving_account, active_permission} },
                   { saving_account, core_account, asset(to_rotation, core_symbol()), std::string("800-" + (name{_commstate.core_host}.to_string()))}
               );
            }


         } else {
            if ( timestamp.slot - em -> last_emission_at.slot >= _commstate.spraying_period_in_blocks ) {
               
               emission.modify(em, _self, [&](auto &e){
                  e.last_emission_at = timestamp;
               });   

               if (to_funds > 0) {
                  INLINE_ACTION_SENDER(eosio::token, transfer) (
                      token_account, { {saving_account, active_permission} },
                      { saving_account, core_account, asset(to_rotation, core_symbol()), std::string("111-" + (name{_commstate.core_host}.to_string()) + "-" + (name{_commstate.core_host}.to_string()))}
                  );
               }

               if (to_rotation > 0){
                  INLINE_ACTION_SENDER(eosio::token, transfer)(
                     token_account, { {saving_account, active_permission} },
                     { saving_account, core_account, asset(to_rotation, core_symbol()), std::string("800-" + (name{_commstate.core_host}.to_string()))}
                  );
               }
            }
            
         } 
         
      }
   }


   // void system_contract::refill( ){


   // }


   void system_contract::checkstatus(){
      require_auth(_self);
       
      corepartners_index corepartners(core_account, "core"_n.value);
      
      auto expired_index = corepartners.template get_index<"byexpiration"_n>();
      auto expired_partner = expired_index.begin();

      if (expired_partner != expired_index.end())
         if(expired_partner -> expiration.sec_since_epoch() < current_time_point().sec_since_epoch())
            action(
               permission_level{ _self, "active"_n },
               core_account, "checkstatus"_n,
               std::make_tuple( "core"_n, expired_partner -> username) 
            ).send();
   }

   void system_contract::update(  ) {
      require_auth(_self);

      onupdate_index updates(_self, _self.value);

      auto expired_index = updates.template get_index<"byexpired"_n>();
      auto expired_host = expired_index.begin();
      
      auto wexpired_index = updates.template get_index<"bywexpired"_n>();
      auto wexpired_host = wexpired_index.begin();
      

      if (expired_host != expired_index.end()){

         if (expired_host -> pool_expired_at.sec_since_epoch() < current_time_point().sec_since_epoch()){
         
            action(
               permission_level{ _self, "active"_n },
               core_account, "refreshst"_n,
               std::make_tuple( "eosio"_n, expired_host -> host) 
            ).send();
         
         } else if (wexpired_host -> window_expired_at.sec_since_epoch() < current_time_point().sec_since_epoch()){
         
            action(
               permission_level{ _self, "active"_n },
               core_account, "refreshst"_n,
               std::make_tuple( "eosio"_n, wexpired_host -> host) 
            ).send();
         
         } else {



            auto is_updated_index = updates.template get_index<"isupdated"_n>();
            
            auto host = is_updated_index.find(0);
            
            if (host != is_updated_index.end()){
               if (host -> update_balances_is_finish == false) {
                  cycle_index cycles(core_account, host->host.value);
                  balance_index balances(core_account, host->host.value);

                  auto balance = balances.lower_bound(host -> current_balance_id);

                  if (balance != balances.end()) {
                     auto cycle = cycles.find(balance-> cycle_num - 1);

                     if (balance -> status == "process"_n && balance -> last_recalculated_win_pool_id < cycle -> finish_at_global_pool_id){
                        action(
                           permission_level{ _self, "active"_n },
                           core_account, "refreshbal"_n,
                           std::make_tuple( balance -> owner, balance -> host, balance -> id, uint64_t(25)) 
                        ).send();
                     }

                     balance++;

                     if (balance == balances.end()) {
                        
                        is_updated_index.modify(host, _self, [&](auto&u) {
                           // u.current_balance_id = 0;
                           u.update_balances_is_finish = true;
                        });

                     } else {

                        is_updated_index.modify(host, _self, [&](auto&u) {
                           u.current_balance_id = balance -> id;
                        });

                     }
                  }
               } 
               // else if (host -> convert_to_goals_is_finish == false) {
               //    //TODO конвертация убыточных балансов в цели
               //    //TODO конвертация прибыльных балансов в новые балансы
               //    if (balance -> available < balance -> purchase_amount) { //если убыток то конвертируем в цель
               //       print("convert balance to goal -> ", balance -> id);
               //       action(
               //          permission_level{ _self, "active"_n },
               //          core_account, "convert"_n,
               //          std::make_tuple( balance -> owner, balance -> host, balance -> id) 
               //       ).send();

               //    } else if (balance -> available >= balance -> purchase_amount) { //если прибыль или номинал - перевкладываем балансы в пулы

               //       print("should convert to balance");
               //       //ACTION 
               //    }

               // } 

               // else if (host -> convert_from_goals_is_finish == false){
               //    //TODO конвертация целей в балансы 
                  
               //    goals_index goals(core_account, host -> host.value);
               //    auto status_goals_index = goals.template get_index<"bystatus"_n>();
               //    auto goal = status_goals_index.lower_bound("filled"_n);
               //    if (goal != status_goals_index.end() && goal -> status == "filled"_n) {

               //       //ACTION convert goal to balance by priority tail


               //    } else {
               //       is_updated_index.modify(host, _self, [&](auto &h){
               //          h.convert_from_goals_is_finish = true;
               //       });
               //    }

               // }
            }
         }
      }
   }

   void system_contract::pushupdate(eosio::name host, uint64_t current_cycle_num, uint64_t current_pool_id, eosio::time_point_sec pool_expired_at, eosio::time_point_sec window_expired_at) {
      require_auth(core_account);

      onupdate_index updates(_self, _self.value);
      auto update = updates.find(host.value);

      if (update == updates.end()){
         updates.emplace(_self, [&](auto &u) {
            u.host = host;
            u.current_cycle_num = current_cycle_num;
            u.current_pool_id = current_pool_id;
            u.current_balance_id = 0;
            u.update_balances_is_finish = false;
            u.convert_to_goals_is_finish = true;
            u.convert_from_goals_is_finish = true;
            u.pool_expired_at = pool_expired_at;
            u.window_expired_at = window_expired_at;
         });
      } else {
         print("convert_to_goals_is_finish: ", update -> current_cycle_num == current_cycle_num && update -> convert_to_goals_is_finish);
         
         updates.modify(update, _self, [&](auto &u){
            u.convert_to_goals_is_finish = update -> current_cycle_num == current_cycle_num && update -> convert_to_goals_is_finish;
            u.convert_from_goals_is_finish = update -> current_cycle_num == current_cycle_num  && update -> convert_from_goals_is_finish;
            
            u.current_cycle_num = current_cycle_num;
            u.current_pool_id = current_pool_id;
            u.current_balance_id = 0;
            u.update_balances_is_finish = false;//update -> update_balances_is_finish && update -> current_pool_id == current_pool_id && update -> current_cycle_num == current_cycle_num;
            u.pool_expired_at = pool_expired_at;

            if (window_expired_at != eosio::time_point_sec(-1)) {
               u.window_expired_at = window_expired_at;
            };
         });
      };


   }


   void system_contract::claimrewards( const name owner ) {
      require_auth( owner );

      const auto& prod = _producers.get( owner.value );
      check( prod.active(), "producer does not have an active key" );
      const auto ct = current_time_point();

      check((_gstate.thresh_activated_stake_time != time_point{ microseconds{0}})
         || (_gstate.thresh_activated_stake_time <= ct), "cannot claim rewards until chain is activated" );

      // check( ct - prod.last_claim_time > microseconds(useconds_per_day), "already claimed rewards within past day" );

      const asset token_supply   = eosio::token::get_supply(token_account, core_symbol().code() );
      const auto usecs_since_last_fill = (ct - _gstate.last_pervote_bucket_fill).count();


      auto prod2 = _producers2.find( owner.value );

      /// New metric to be used in pervote pay calculation. Instead of vote weight ratio, we combine vote weight and
      /// time duration the vote weight has been held into one metric.
      const auto last_claim_plus_3days = prod.last_claim_time + microseconds(3 * useconds_per_day);

      bool crossed_threshold       = (last_claim_plus_3days <= ct);
      bool updated_after_threshold = true;
      if ( prod2 != _producers2.end() ) {
         updated_after_threshold = (last_claim_plus_3days <= prod2->last_votepay_share_update);
      } else {
         prod2 = _producers2.emplace( owner, [&]( producer_info2& info  ) {
            info.owner                     = owner;
            info.last_votepay_share_update = ct;
         });
      }

      // Note: updated_after_threshold implies cross_threshold (except if claiming rewards when the producers2 table row did not exist).
      // The exception leads to updated_after_threshold to be treated as true regardless of whether the threshold was crossed.
      // This is okay because in this case the producer will not get paid anything either way.
      // In fact it is desired behavior because the producers votes need to be counted in the global total_producer_votepay_share for the first time.

      int64_t producer_per_block_pay = 0;
      if( _gstate.total_unpaid_blocks > 0 ) {
         producer_per_block_pay = (_gstate.perblock_bucket * prod.unpaid_blocks) / _gstate.total_unpaid_blocks;
      }

      double new_votepay_share = update_producer_votepay_share( prod2,
                                    ct,
                                    updated_after_threshold ? 0.0 : prod.total_votes,
                                    true // reset votepay_share to zero after updating
                                 );

      int64_t producer_per_vote_pay = 0;
      if( _gstate2.revision > 0 ) {
         double total_votepay_share = update_total_votepay_share( ct );
         if( total_votepay_share > 0 && !crossed_threshold ) {
            producer_per_vote_pay = int64_t((new_votepay_share * _gstate.pervote_bucket) / total_votepay_share);
            if( producer_per_vote_pay > _gstate.pervote_bucket )
               producer_per_vote_pay = _gstate.pervote_bucket;
         }
      } else {
         if( _gstate.total_producer_vote_weight > 0 ) {
            producer_per_vote_pay = int64_t((_gstate.pervote_bucket * prod.total_votes) / _gstate.total_producer_vote_weight);
         }
      }

      if( producer_per_vote_pay < min_pervote_daily_pay ) {
         producer_per_vote_pay = 0;
      }

      _gstate.pervote_bucket      -= producer_per_vote_pay;
      _gstate.perblock_bucket     -= producer_per_block_pay;
      _gstate.total_unpaid_blocks -= prod.unpaid_blocks;

      update_total_votepay_share( ct, -new_votepay_share, (updated_after_threshold ? prod.total_votes : 0.0) );

      _producers.modify( prod, same_payer, [&](auto& p) {
         p.last_claim_time = ct;
         p.unpaid_blocks   = 0;
      });

      if( producer_per_block_pay > 0 ) {
         INLINE_ACTION_SENDER(eosio::token, transfer)(
            token_account, { {bpay_account, active_permission}, {owner, active_permission} },
            { bpay_account, owner, asset(producer_per_block_pay, core_symbol()), std::string("producer block pay") }
         );
      }
      if( producer_per_vote_pay > 0 ) {
         INLINE_ACTION_SENDER(eosio::token, transfer)(
            token_account, { {vpay_account, active_permission}, {owner, active_permission} },
            { vpay_account, owner, asset(producer_per_vote_pay, core_symbol()), std::string("producer vote pay") }
         );
      }
   }

} //namespace eosiosystem
