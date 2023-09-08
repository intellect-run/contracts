using namespace eosio;

void soviet::change(uint64_t order_id) { 
  require_auth(_marketplace);

  decision_index decisions(_soviet, _soviet.value);
  auto id = get_global_id(_soviet, "decisions"_n);
  
  decisions.emplace(_soviet, [&](auto &d){
    d.id = id;
    d.type = _change_action;
    d.secondary_id = order_id;
  });

  action(
    permission_level{ _soviet, "active"_n},
    _soviet,
    "newid"_n,
    std::make_tuple(id)
  ).send();
  
};


void soviet::change_effect(eosio::name executer, uint64_t decision_id, eosio::name username) { 
  decision_index decisions(_soviet, _soviet.value);
  auto decision = decisions.find(decision_id);
  
  action(
      permission_level{ _soviet, "active"_n},
      "marketplace"_n,
      "authorize"_n,
      std::make_tuple(username)
  ).send();
    
  decisions.modify(decision, executer, [&](auto &d){
    d.executed = true;
  });

};
