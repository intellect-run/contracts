#include "marketplace.hpp"
#include <eosio/transaction.hpp>

using namespace eosio;


void marketplace::addbalance(eosio::name contract, eosio::name username, eosio::asset quantity, std::string memo) {
   //TODO addbalance
   //TODO subbalance
}

[[eosio::action]] void marketplace::update() {

}


extern "C" {
   
   /// The apply method implements the dispatch of events to this contract
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
        if (code == _me.value) {
          if (action == "update"_n.value){
            execute_action(name(receiver), name(code), &marketplace::update);
          }
        } else {
          if (action == "transfer"_n.value){
            
            struct transfer{
                eosio::name from;
                eosio::name to;
                eosio::asset quantity;
                std::string memo;
            };

            auto op = eosio::unpack_action_data<transfer>();

            if (op.to == _me){
              marketplace::addbalance(name(code), op.from, op.quantity, op.memo);
            }
          }
        }
  };
};