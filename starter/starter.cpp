#include "starter.hpp"
#include <ctime>
#include <eosio/transaction.hpp>
using namespace eosio;


void starter::hello(std::string message) {
  require_auth(_me);

  print("hello: ", message);
};


extern "C" {

/// The apply method implements the dispatch of events to this contract
void apply(uint64_t receiver, uint64_t code, uint64_t action) {
  if (code == _me.value) {
    switch (action) {
      EOSIO_DISPATCH_HELPER(
          starter, (hello)
      )
    }
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
        // starter::add_balance(op.from, op.quantity, name(code));
      }
    }
  }
};
};
