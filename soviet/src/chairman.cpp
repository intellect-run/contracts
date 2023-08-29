using namespace eosio;


void soviet::is_valid_member(eosio::name member) {
  board_index boards(_me, _me.value);
  auto board = boards.find(0);
  
  // Проверяем, является ли участник членом совета
  eosio::check(std::find(board->members.begin(), board->members.end(), member) != board->members.end(), "Вы не являетесь членом совета");
};


void soviet::is_valid_chairman(eosio::name chairman) {
  board_index boards(_me, _me.value);
  auto board = boards.find(0);
  
  eosio::check(board -> chairman == chairman, "Вы не председатель");
  
};


void soviet::authorize(eosio::name chairman, uint64_t decision_id) { 
  require_auth(chairman);

  board_index boards(_me, _me.value);
  oracle_index oracle(_me, _me.value);

  auto board = boards.find(0);

  eosio::check(board != boards.end(), "Совет не найден");
  eosio::check(board -> chairman == chairman, "Только председатель совета может авторизовать решение");
  
  decision_index decisions(_me, _me.value);
  auto decision = decisions.find(decision_id);

  decisions.modify(decision, chairman, [&](auto &d){
    d.authorized = true;
  });

  auto ora = oracle.find(decision -> id);
  
  if (ora != oracle.end())
    oracle.erase(ora);

}


void soviet::createboard(eosio::name chairman, std::vector<eosio::name> members, uint64_t expired_after_days){
  require_auth(_chairman); 

  board_index boards(_me, _me.value);

  auto board = boards.find(0);
  eosio::check(board == boards.end(), "Совет уже создан");

  // Проверка на наличие председателя в списке членов совета
  eosio::check(std::find(members.begin(), members.end(), chairman) != members.end(), "Председатель должен быть в списке членов совета");

  boards.emplace(chairman, [&](auto &b) {
    b.id = boards.available_primary_key();
    b.parent_id = 0; //если кооперативный участок >= 0
    b.members = members;
    b.chairman = chairman;
    b.created_at = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
    b.expired_at = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch() + expired_after_days * 86400);
  });

}


//TODO modify members, but cannot delete chairman


uint64_t soviet::get_members_count(uint64_t board_id) {
  board_index boards(_me, _me.value);

  auto board = boards.find(board_id);
  eosio::check(board != boards.end(), "Совет не найден");

  return board->members.size();

};


uint64_t soviet::get_consensus_percent(uint64_t board_id) {
  board_index boards(_me, _me.value);

  auto board = boards.find(board_id);
  eosio::check(board != boards.end(), "Совет не найден");

  return board -> consensus;

};
