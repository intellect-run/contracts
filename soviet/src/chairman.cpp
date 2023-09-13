using namespace eosio;


void soviet::authorize(eosio::name coop_username, eosio::name chairman, uint64_t decision_id) { 
  require_auth(chairman);

  boards_index boards(_soviet, coop_username.value);
  autosigner_index autosigner(_soviet, coop_username.value);
  
  decisions_index decisions(_soviet, coop_username.value);
  auto decision = decisions.find(decision_id);

  eosio::check(decision != decisions.end(), "Документ не найден");
  auto board = get_board_by_type_or_fail(coop_username, "soviet"_n);
  
  eosio::check(board.is_valid_chairman(chairman), "Только председатель совета может авторизовать решение");
  
  decisions.modify(decision, chairman, [&](auto &d){
    d.authorized = true;
  });

  auto signer = autosigner.find(decision -> id);
  
  if (signer != autosigner.end())
    autosigner.erase(signer);

}


void soviet::createboard(eosio::name coop_username, eosio::name chairman, eosio::name type, std::vector<board_member> members, std::string name, std::string description){

  require_auth(chairman);
  orgs_index orgs(_registrator, _registrator.value);
  auto org = orgs.find(coop_username.value);
  eosio::check(org != orgs.end(), "Организация не найдена");
  eosio::check(org -> is_coop(), "Организация - не кооператив");
  
  if (type == "soviet"_n) {
    bool is_exist = check_for_exist_board_by_type(coop_username, "soviet"_n);
    eosio::check(is_exist == false, "Совет кооператива уже создан");
    
    bool has_chairman = false;
    // Проверка на наличие председателя в списке членов совета
    for (const auto& m : members) {
        if (m.position == "chairman"_n) {
            eosio::check(m.username == chairman, "Только председатель может создать совет кооператива");
            has_chairman = true;
        };
    };

    eosio::check(has_chairman, "Председатель кооператива должен быть указан в членах совета");

  } else {
    auto soviet = get_board_by_type_or_fail(coop_username, "soviet"_n);
    eosio::check(soviet.is_valid_chairman(chairman), "Только председатель кооператива может создать совет");
  }

  boards_index boards(_soviet, coop_username.value);

  boards.emplace(chairman, [&](auto &b) {
    b.id = boards.available_primary_key();
    b.type = type;
    b.members = members;
    b.name = name;
    b.description = description;
    b.created_at = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
    b.last_update = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
  });

}
