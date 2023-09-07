#include "draft.hpp"
#include <ctime>
#include <eosio/transaction.hpp>
using namespace eosio;

void draft::hello(std::string message) {
  require_auth(_me);

  print("hello: ", message);
};

void draft::create(eosio::name lang, eosio::name action_name, std::string name,
                   std::string description, std::string context,
                   std::string data) {

  require_auth(_ano);
};

void draft::publish(uint64_t draft_id){

};

void draft::use(){

};

void draft::replace(){

};

void draft::delete (){

};

void draft::edit(){

};

extern "C" {

/// The apply method implements the dispatch of events to this contract
void apply(uint64_t receiver, uint64_t code, uint64_t action) {
  if (code == _me.value) {
    switch (action) { EOSIO_DISPATCH_HELPER(draft, (hello)) }
  } else {
    if (action == "transfer"_n.value) {
      struct transfer {
        eosio::name from;
        eosio::name to;
        eosio::asset quantity;
        std::string memo;
      };

      auto op = eosio::unpack_action_data<transfer>();

      if (op.to == _me) {
        // вызов функции-обработчика пополнения баланса
        // draft::add_balance(op.from, op.quantity, name(code));
      }
    }
  }
};
};
