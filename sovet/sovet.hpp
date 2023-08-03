#pragma once

#include <eosio/binary_extension.hpp>
#include <eosio/eosio.hpp>
#include <eosio/ignore.hpp>
#include <eosio/transaction.hpp>

namespace eosio {
   class [[eosio::contract("sovet")]] sovet : public contract {
      public:
         using contract::contract;

         [[eosio::action]]
         void propose(name proposer, name proposal_name,
                      std::vector<permission_level> requested, transaction trx);
         [[eosio::action]]
         void approve( name proposer, name proposal_name, permission_level level,
                       const eosio::binary_extension<eosio::checksum256>& proposal_hash );
         [[eosio::action]]
         void unapprove( name proposer, name proposal_name, permission_level level );
         [[eosio::action]]
         void cancel( name proposer, name proposal_name, name canceler );
         [[eosio::action]]
         void exec( name proposer, name proposal_name, name executer );
         [[eosio::action]]
         void invalidate( name account );

         using propose_action = eosio::action_wrapper<"propose"_n, &sovet::propose>;
         using approve_action = eosio::action_wrapper<"approve"_n, &sovet::approve>;
         using unapprove_action = eosio::action_wrapper<"unapprove"_n, &sovet::unapprove>;
         using cancel_action = eosio::action_wrapper<"cancel"_n, &sovet::cancel>;
         using exec_action = eosio::action_wrapper<"exec"_n, &sovet::exec>;
         using invalidate_action = eosio::action_wrapper<"invalidate"_n, &sovet::invalidate>;

   struct [[eosio::table, eosio::contract("sovet")]] proposal {
      name                                                            proposal_name;
      std::vector<char>                                               packed_transaction;
      eosio::binary_extension< std::optional<time_point> >            earliest_exec_time;

      uint64_t primary_key()const { return proposal_name.value; }
   };
   typedef eosio::multi_index< "proposal"_n, proposal > proposals;

   struct [[eosio::table, eosio::contract("sovet")]] old_approvals_info {
      name                            proposal_name;
      std::vector<permission_level>   requested_approvals;
      std::vector<permission_level>   provided_approvals;
      uint64_t primary_key()const { return proposal_name.value; }
   };
   typedef eosio::multi_index< "approvals"_n, old_approvals_info > old_approvals;
   struct approval {
      permission_level level;
      time_point       time;
   };

   struct [[eosio::table, eosio::contract("sovet")]] approvals_info {
      uint8_t                 version = 1;
      name                    proposal_name;
      std::vector<approval>   requested_approvals;
      std::vector<approval>   provided_approvals;
      uint64_t primary_key()const { return proposal_name.value; }
   };
   typedef eosio::multi_index< "approvals2"_n, approvals_info > approvals;

   struct [[eosio::table, eosio::contract("sovet")]] invalidation {
         name         account;
         time_point   last_invalidation_time;

         uint64_t primary_key() const { return account.value; }
      };

      typedef eosio::multi_index< "invals"_n, invalidation > invalidations;
   };
} /// namespace eosio
