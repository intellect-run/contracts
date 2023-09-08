using namespace eosio;

void soviet::regaccount(eosio::name username) { 
  require_auth(_registrator);

  decision_index decisions(_soviet, _soviet.value);
  auto id = get_global_id(_soviet, "decisions"_n);
  decisions.emplace(_soviet, [&](auto &d){
    d.id = id;
    d.type = _regaccount_action;
    d.secondary_id = username.value;
  });

  action(
    permission_level{ _soviet, "active"_n},
    _soviet,
    "newid"_n,
    std::make_tuple(id)
  ).send();
};


void soviet::regaccount_effect(eosio::name executer, uint64_t decision_id, eosio::name username) { 
  decision_index decisions(_soviet, _soviet.value);
  auto decision = decisions.find(decision_id);
  
  action(
      permission_level{ _soviet, "active"_n},
      "registrator"_n,
      "confirmreg"_n,
      std::make_tuple(username)
  ).send();
    
  decisions.modify(decision, executer, [&](auto &d){
    d.executed = true;
  });

};
