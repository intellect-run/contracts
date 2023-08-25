using namespace eosio;

void soviet::regaccount(eosio::name username) { 
  require_auth(_registrator);

  decision_index decisions(_me, _me.value);

  decisions.emplace(_me, [&](auto &d){
    d.id = soviet::get_global_id("decisions"_n);
    d.type = _REGACCOUNT;
    d.secondary_id = username.value;
  });
};


void soviet::regaccount_effect(eosio::name executer, uint64_t decision_id, eosio::name username) { 
  decision_index decisions(_me, _me.value);
  auto decision = decisions.find(decision_id);
  
  action(
      permission_level{ _me, "active"_n},
      "registrator"_n,
      "confirmreg"_n,
      std::make_tuple(username)
  ).send();
    
  decisions.modify(decision, executer, [&](auto &d){
    d.executed = true;
  });

};