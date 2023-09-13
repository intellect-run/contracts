using namespace eosio;

void soviet::change(eosio::name coop_username, uint64_t exchange_id) { 
  require_auth(_marketplace);

  decisions_index decisions(_soviet, coop_username.value);
  auto id = get_global_id(_soviet, "decisions"_n);
 
  changes_index changes(_soviet, coop_username.value);
  auto change_id = get_global_id(_soviet, "change"_n);

  changes.emplace(_marketplace, [&](auto &c){
    c.exchange_id = exchange_id;
  });

  //TODO insert change card here 
  decisions.emplace(_soviet, [&](auto &d){
    d.id = id;
    d.type = _change_action;
    d.card_id = exchange_id;
  });

  action(
    permission_level{ _soviet, "active"_n},
    _soviet,
    "newid"_n,
    std::make_tuple(id)
  ).send();
  
};


void soviet::change_effect(eosio::name executer, eosio::name coop_username, uint64_t decision_id, uint64_t card_id) { 

  decisions_index decisions(_soviet, coop_username.value);
  auto decision = decisions.find(decision_id);
  
  action(
      permission_level{ _soviet, "active"_n},
      "marketplace"_n,
      "authorize"_n,
      std::make_tuple(card_id)
  ).send();
    
  decisions.modify(decision, executer, [&](auto &d){
    d.executed = true;
  });

};
