using namespace eosio;

void soviet::change(uint64_t order_id) { 
  require_auth(_marketplace);

  decision_index decisions(_me, _me.value);
  decisions.emplace(_me, [&](auto &d){
    d.id = soviet::get_global_id("decisions"_n);
    d.type = _CHANGE;
    d.secondary_id = order_id;
  });

};


void soviet::change_effect(eosio::name executer, uint64_t decision_id, eosio::name username) { 
  decision_index decisions(_me, _me.value);
  auto decision = decisions.find(decision_id);
  
  action(
      permission_level{ _me, "active"_n},
      "marketplace"_n,
      "authorize"_n,
      std::make_tuple(username)
  ).send();
    
  decisions.modify(decision, executer, [&](auto &d){
    d.executed = true;
  });

};