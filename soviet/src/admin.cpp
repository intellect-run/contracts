using namespace eosio;


void soviet::addadmin(eosio::name chairman, eosio::name username, std::vector<eosio::name> rights, std::string meta) {
  require_auth(chairman);

  admin_index admins(_me, _me.value);
  board_index boards(_me, _me.value);

  auto board = boards.find(0);
  eosio::check(board != boards.end(), "Совет еще не создан");
  eosio::check(board -> chairman == chairman, "Вы не председатель, чтобы добавлять админов!");

  auto admin = admins.find(username.value);

  if (admin == admins.end())
    admins.emplace(chairman, [&](auto &a){
      a.username = username;
      a.rights = rights;
      a.meta = meta;
    });

};


void soviet::rmadmin(eosio::name chairman, eosio::name username) {
  require_auth(chairman);

  admin_index admins(_me, _me.value);
  board_index boards(_me, _me.value);

  auto board = boards.find(0);
  eosio::check(board != boards.end(), "Совет еще не создан");
  eosio::check(board -> chairman == chairman, "Вы не председатель, чтобы удалять админов!");
  
  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "Администратор не найден");

  admins.erase(admin);

};


void soviet::setadmrights(eosio::name chairman, eosio::name username, std::vector<eosio::name> rights) {
  require_auth(chairman);

  admin_index admins(_me, _me.value);
  board_index boards(_me, _me.value);

  auto board = boards.find(0);
  eosio::check(board != boards.end(), "Совет еще не создан");
  eosio::check(board -> chairman == chairman, "Только председатель может изменять права администраторов");

  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "Администратор не найден");

  admins.modify(admin, chairman, [&](auto &a){
    a.rights = rights;
  });  
};
  

void soviet::validate(eosio::name username, uint64_t decision_id) { 
  require_auth(username);
  admin_index admins(_me, _me.value);

  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "У вас нет прав администратора");

  decision_index decisions(_me, _me.value);
  auto decision = decisions.find(decision_id);
  eosio::check(decision != decisions.end(), "Решение не найдено");

  decisions.modify(decision, username, [&](auto &d){
    d.validated = true;
  });
  
  soviet::check_and_sign_by_members(decision -> type, decision_id);

  soviet::check_and_sign_by_chairman(decision -> type, decision_id);

}
