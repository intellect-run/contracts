using namespace eosio;

void soviet::addadmin(uint64_t board_id, eosio::name chairman, eosio::name username, std::vector<eosio::name> rights, std::string meta) {
  require_auth(chairman);

  admins_index admins(_soviet, _soviet.value);
  boards_index boards(_soviet, _soviet.value);

  auto board = boards.find(board_id);
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


void soviet::rmadmin(uint64_t board_id, eosio::name chairman, eosio::name username) {
  require_auth(chairman);

  admins_index admins(_soviet, _soviet.value);
  boards_index boards(_soviet, _soviet.value);

  auto board = boards.find(board_id);
  eosio::check(board != boards.end(), "Совет еще не создан");
  eosio::check(board -> chairman == chairman, "Вы не председатель, чтобы удалять админов!");
  
  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "Администратор не найден");

  admins.erase(admin);

};


void soviet::setadmrights(uint64_t board_id, eosio::name chairman, eosio::name username, std::vector<eosio::name> rights) {
  require_auth(chairman);

  admins_index admins(_soviet, _soviet.value);
  boards_index boards(_soviet, _soviet.value);

  auto board = boards.find(board_id);
  eosio::check(board != boards.end(), "Совет еще не создан");
  eosio::check(board -> chairman == chairman, "Только председатель может изменять права администраторов");

  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "Администратор не найден");

  admins.modify(admin, chairman, [&](auto &a){
    a.rights = rights;
  });  
};
  

void soviet::validate(uint64_t board_id, eosio::name username, uint64_t document_id) { 
  require_auth(username);

  boards_index boards(_soviet, _soviet.value);
  auto board = boards.find(board_id);
  eosio::check(board != boards.end(), "Совет еще не создан");

  admins_index admins(_soviet, _soviet.value);

  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "У вас нет прав администратора");

  documents_index documents(_soviet, _soviet.value);
  auto document = documents.find(document_id);
  eosio::check(document != documents.end(), "Решение не найдено");

  documents.modify(document, username, [&](auto &d){
    d.validated = true;
  });
  
  oracle_index oracle(_soviet, _soviet.value);  
  auto ora = oracle.find(document -> id);
  
  if (ora == oracle.end())
    oracle.emplace(_soviet, [&](auto &o) {
      o.id = document -> id;
    });
}
