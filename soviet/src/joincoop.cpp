using namespace eosio;

void soviet::joincoop(eosio::name coop_username, eosio::name username, std::string position_title, eosio::name position) { 
  require_auth(_registrator);

  joincoops_index joincoops(_soviet, coop_username.value); 
  auto card_id = get_global_id(_soviet, "joincoops"_n);

  joincoops.emplace(_registrator, [&](auto &a){
    a.id = card_id;
    a.username = username;
    a.is_paid = false;
  });

  decisions_index decisions(_soviet, coop_username.value);
  auto id = get_global_id(_soviet, "decisions"_n);
  decisions.emplace(_soviet, [&](auto &d){
    d.id = id;
    d.type = _regaccount_action;
    d.card_id = card_id;
  });

  action(
    permission_level{ _soviet, "active"_n},
    _soviet,
    "newid"_n,
    std::make_tuple(id)
  ).send();
};


void soviet::joincoop_effect(eosio::name executer, eosio::name coop_username, uint64_t decision_id, uint64_t card_id) { 

  decisions_index decisions(_soviet, _soviet.value);
  auto decision = decisions.find(decision_id);

  joincoops_index joincoops(_soviet, coop_username.value); 
  auto joincoop_action = joincoops.find(decision->card_id);
 
  action(
      permission_level{ _soviet, "active"_n},
      "registrator"_n,
      "confirmreg"_n,
      std::make_tuple(joincoop_action -> username)
  ).send();

  decisions.modify(decision, executer, [&](auto &d){
    d.executed = true;
  });

 joincoops.erase(joincoop_action);
};
