using namespace eosio;


void soviet::is_valid_member(eosio::name member) {
  boards_index boards(_soviet, _soviet.value);
  auto board = boards.find(0);
  
  // Проверяем, является ли участник членом совета
  eosio::check(std::find(board->members.begin(), board->members.end(), member) != board->members.end(), "Вы не являетесь членом совета");
};


void soviet::is_valid_chairman(eosio::name chairman) {
  boards_index boards(_soviet, _soviet.value);
  auto board = boards.find(0);
  
  eosio::check(board -> chairman == chairman, "Вы не председатель");
  
};


void soviet::authorize(eosio::name chairman, uint64_t document_id) { 
  require_auth(chairman);

  boards_index boards(_soviet, _soviet.value);
  oracle_index oracle(_soviet, _soviet.value);

  auto board = boards.find(0);

  eosio::check(board != boards.end(), "Совет не найден");
  eosio::check(board -> chairman == chairman, "Только председатель совета может авторизовать решение");
  
  documents_index documents(_soviet, _soviet.value);
  auto document = documents.find(document_id);

  documents.modify(document, chairman, [&](auto &d){
    d.authorized = true;
  });

  auto ora = oracle.find(document -> id);
  
  if (ora != oracle.end())
    oracle.erase(ora);

}


void soviet::createboard(uint64_t coop_username, uint64_t parent_id, eosio::name chairman, std::vector<eosio::name> members){
  require_auth(chairman); 


  accounts_index accunts()
  coops_index coops(_ano, _ano.value);
  auto coop = coops.find(coop_id);

  eosio::check(coop != coops.end(), "Кооператив не найден");
  print("coop -> status: ", coop -> status);

  eosio::check(coop -> status == "run"_n, "Кооператив отключен");
  eosio::check(coop -> chairman == chairman, "Только председатель кооператива может создать совет | участок");

  boards_index boards(_soviet, _soviet.value);
  auto board = boards.find(coop_id);
  eosio::check(board == boards.end(), "Совет уже создан");

  if (parent_id > 0) {
    auto parent_board = boards.find(parent_id);
    eosio::check(parent_board != boards.end(), "Родительский совет не найден");
    eosio::check(parent_board -> parent_id == 0, "Только совет кооператива может создавать кооперативные участки");
    eosio::check(parent_board -> chairman == chairman, "Только председатель совета кооператива может создавать кооперативные участки");
  };

  // Проверка на наличие председателя в списке членов совета
  eosio::check(std::find(members.begin(), members.end(), chairman) != members.end(), "Председатель должен быть в списке членов совета");

  boards.emplace(chairman, [&](auto &b) {
    b.id = boards.available_primary_key();
    b.parent_id = parent_id; //если кооперативный участок >= 0
    b.members = members;
    b.chairman = chairman;
    b.created_at = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
  });

}


//TODO modify members, but cannot delete chairman


uint64_t soviet::get_members_count(uint64_t board_id) {
  boards_index boards(_soviet, _soviet.value);

  auto board = boards.find(board_id);
  eosio::check(board != boards.end(), "Совет не найден");

  return board->members.size();

};

