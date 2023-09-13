using namespace eosio;

void soviet::addstaff(eosio::name coop_username, uint64_t board_id, eosio::name chairman, eosio::name username, std::vector<right> rights, std::string position_title) {
  require_auth(chairman);

  staff_index staff(_soviet, coop_username.value);
  boards_index boards(_soviet, coop_username.value);

  auto board = boards.find(board_id);
  eosio::check(board != boards.end(), "Совет не найден");
  eosio::check(board -> is_valid_chairman(chairman), "Только председатель кооператива может добавлять персонал");

  auto persona = staff.find(username.value);

  if (persona == staff.end())
    staff.emplace(chairman, [&](auto &a){
      a.username = username;
      a.position_title = position_title;
      a.rights = rights;
    });

};


void soviet::rmstaff(eosio::name coop_username, uint64_t board_id, eosio::name chairman, eosio::name username) {
  require_auth(chairman);

  staff_index staff(_soviet, coop_username.value);
  boards_index boards(_soviet, coop_username.value);

  auto board = boards.find(board_id);
  eosio::check(board != boards.end(), "Совет не найден");
  eosio::check(board -> is_valid_chairman(chairman), "Только председатель кооператива может удалять персонал");

  auto persona = staff.find(username.value);
  eosio::check(persona != staff.end(), "Персона не найдена");

  staff.erase(persona);

};


void soviet::setrights(eosio::name coop_username, uint64_t board_id, eosio::name chairman, eosio::name username, std::vector<right> rights) {
  require_auth(chairman);

  staff_index staff(_soviet, coop_username.value);
  boards_index boards(_soviet, coop_username.value);

  auto board = boards.find(board_id);
  eosio::check(board != boards.end(), "Совет не найден");
  eosio::check(board -> is_valid_chairman(chairman), "Только председатель кооператива может удалять персонал");

  auto persona = staff.find(username.value);
  eosio::check(persona != staff.end(), "Персона не найдена");

  staff.modify(persona, chairman, [&](auto &a){
    a.rights = rights;
  });  
};
  

void soviet::validate(eosio::name coop_username, uint64_t board_id, eosio::name username, uint64_t decision_id) { 
  require_auth(username);

  boards_index boards(_soviet, coop_username.value);
  auto board = boards.find(board_id);
  eosio::check(board != boards.end(), "Совет не найден");

  staff_index staff(_soviet, coop_username.value);
  auto persona = staff.find(username.value);
  
  eosio::check(persona -> has_right(_soviet, "validate"_n), "Недостаточно прав доступа");

  decisions_index decisions(_soviet, coop_username.value);
  auto decision = decisions.find(decision_id);
  eosio::check(decision != decisions.end(), "Документ не найден");

  decisions.modify(decision, username, [&](auto &d){
    d.validated = true;
  });

  autosigner_index autosigner(_soviet, coop_username.value);  
  auto signer = autosigner.find(decision -> id);

  if (signer == autosigner.end())
    autosigner.emplace(_soviet, [&](auto &o) {
      o.decision_id = decision -> id;
    });
}
