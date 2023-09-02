#include "ano.hpp"
#include <ctime>
#include <eosio/transaction.hpp>

using namespace eosio;


[[eosio::action]] void ano::newid(uint64_t coop_id) {
  require_auth(_me);
};


void ano::startcoop(eosio::name chairman, eosio::name registrator, std::string data) {
  require_auth(_me);

  coops_index coops(_me, _me.value);

  authority active_auth;
  authority owner_auth;
  eosio::permission_level permission(_me, eosio::name("eosio.code"));
  permission_level_weight accountpermission{permission, 1};
  active_auth.threshold = 1;
  owner_auth.threshold = 1;
  active_auth.accounts.emplace_back(accountpermission);
  owner_auth.accounts.emplace_back(accountpermission);

  // reserved_index reserve(_me, _me.value);
  // auto raccount = reserve.find(username.value);
  
  // eosio::check(raccount == reserve.end(), "account has been already registered throw registrator community");
  
  eosio::name system_name = name(generate_random_name());
  eosio::asset cpu = asset(10000, _root_symbol);
  eosio::asset net = asset(10000, _root_symbol);
  eosio::asset ram = asset(1000, _root_symbol);

  action(permission_level(_me, "active"_n), 
    "eosio"_n, "newaccount"_n, std::tuple(_me, 
    system_name, owner_auth, active_auth) 
  ).send();

  action(
    permission_level{ _me, "active"_n},
    "eosio"_n,
    "buyram"_n,
    std::make_tuple(_me, system_name, ram)
  ).send();
  
  action(
    permission_level{ _me, "active"_n},
    "eosio"_n,
    "delegatebw"_n,
   std::make_tuple(_me, system_name, net, cpu, true)
  ).send();

  uint64_t coop_id = get_global_id("coops"_n);
  coops.emplace(_me, [&](auto &c){
    c.id = coop_id;
    c.system_name = system_name;
    c.chairman = chairman;
    c.registrator = registrator;
    c.status = "run"_n;
    c.data = data;
  });


  action(
    permission_level{ _me, "active"_n},
    _me,
    "newid"_n,
    std::make_tuple(coop_id)
  ).send();


};


void ano::stopcoop(uint64_t id, std::string reason) {
  require_auth(_me);

  coops_index coops(_me, _me.value);
  
  auto coop = coops.find(id);
  
  eosio::check(coop != coops.end(), "Кооператив не найден");

  coops.modify(coop, _me, [&](auto &c){
    c.status = "stop"_n;
    c.message = reason;
  });

};


extern "C" {

/// The apply method implements the dispatch of events to this contract
void apply(uint64_t receiver, uint64_t code, uint64_t action) {
  if (code == _me.value) {
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

      if (op.to == _me) {
        // вызов функции-обработчика пополнения баланса
      }
    }
  }
};
};
