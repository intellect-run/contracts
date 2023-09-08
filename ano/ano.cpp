#include "ano.hpp"
#include <ctime>
#include <eosio/transaction.hpp>

using namespace eosio;


void ano::newid(uint64_t coop_id) {
  require_auth(_ano);
};


void ano::startcoop(eosio::name chairman, eosio::name registrator, std::string data) {
  require_auth(_ano);

  coops_index coops(_ano, _ano.value);

  authority active_auth;
  authority owner_auth;
  eosio::permission_level permission(_ano, eosio::name("eosio.code"));
  permission_level_weight accountpermission{permission, 1};
  active_auth.threshold = 1;
  owner_auth.threshold = 1;
  active_auth.accounts.emplace_back(accountpermission);
  owner_auth.accounts.emplace_back(accountpermission);

  eosio::name system_name = name(generate_random_name());
  eosio::asset cpu = asset(10000, _root_symbol);
  eosio::asset net = asset(10000, _root_symbol);
  eosio::asset ram = asset(1000, _root_symbol);

  action(permission_level(_ano, "active"_n), 
    "eosio"_n, "newaccount"_n, std::tuple(_ano, 
    system_name, owner_auth, active_auth) 
  ).send();

  action(
    permission_level{ _ano, "active"_n},
    "eosio"_n,
    "buyram"_n,
    std::make_tuple(_ano, system_name, ram)
  ).send();
  
  action(
    permission_level{ _ano, "active"_n},
    "eosio"_n,
    "delegatebw"_n,
   std::make_tuple(_ano, system_name, net, cpu, true)
  ).send();

  uint64_t coop_id = get_global_id(_ano, "coops"_n);
  
  coops.emplace(_ano, [&](auto &c){
    c.id = coop_id;
    c.system_name = system_name;
    c.chairman = chairman;
    c.registrator = registrator;
    c.status = "run"_n;
    c.data = data;
  });


  action(
    permission_level{ _ano, "active"_n},
    _ano,
    "newid"_n,
    std::make_tuple(coop_id)
  ).send();


};


void ano::stopcoop(uint64_t id, std::string reason) {
  require_auth(_ano);

  coops_index coops(_ano, _ano.value);
  
  auto coop = coops.find(id);
  
  eosio::check(coop != coops.end(), "Кооператив не найден");

  coops.modify(coop, _ano, [&](auto &c){
    c.status = "stop"_n;
    c.message = reason;
  });

};


extern "C" {

/// The apply method implements the dispatch of events to this contract
void apply(uint64_t receiver, uint64_t code, uint64_t action) {
  if (code == _ano.value) {
    switch (action) {
      EOSIO_DISPATCH_HELPER(
          ano, (startcoop)(stopcoop)(newid)
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

      if (op.to == _ano) {
        // вызов функции-обработчика пополнения баланса
      }
    }
  }
};
};
