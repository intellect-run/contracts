using namespace eosio;


void soviet::is_valid_member(eosio::name member) {
  union_index unions(_soviet, _soviet.value);
  auto uni = unions.find(0);
  
  // Проверяем, является ли участник членом совета
  eosio::check(std::find(uni->members.begin(), uni->members.end(), member) != uni->members.end(), "Вы не являетесь членом совета");
};


void soviet::is_valid_chairman(eosio::name chairman) {
  union_index unions(_soviet, _soviet.value);
  auto uni = unions.find(0);
  
  eosio::check(uni -> chairman == chairman, "Вы не председатель");
  
};


void soviet::authorize(eosio::name chairman, uint64_t decision_id) { 
  require_auth(chairman);

  union_index unions(_soviet, _soviet.value);
  oracle_index oracle(_soviet, _soviet.value);

  auto uni = unions.find(0);

  eosio::check(uni != unions.end(), "Совет не найден");
  eosio::check(uni -> chairman == chairman, "Только председатель совета может авторизовать решение");
  
  decision_index decisions(_soviet, _soviet.value);
  auto decision = decisions.find(decision_id);

  decisions.modify(decision, chairman, [&](auto &d){
    d.authorized = true;
  });

  auto ora = oracle.find(decision -> id);
  
  if (ora != oracle.end())
    oracle.erase(ora);

}


void soviet::createunion(uint64_t coop_id, uint64_t parent_id, eosio::name chairman, std::vector<eosio::name> members){
  require_auth(chairman); 

  coops_index coops(_ano, _ano.value);
  auto coop = coops.find(coop_id);

  eosio::check(coop != coops.end(), "Кооператив не найден");
  print("coop -> status: ", coop -> status);

  eosio::check(coop -> status == "run"_n, "Кооператив отключен");
  eosio::check(coop -> chairman == chairman, "Только председатель кооператива может создать совет | участок");

  union_index unions(_soviet, _soviet.value);
  auto uni = unions.find(coop_id);
  eosio::check(uni == unions.end(), "Совет уже создан");

  if (parent_id > 0) {
    auto parent_board = unions.find(parent_id);
    eosio::check(parent_board != unions.end(), "Родительский совет не найден");
    eosio::check(parent_board -> parent_id == 0, "Только совет кооператива может создавать кооперативные участки");
    eosio::check(parent_board -> chairman == chairman, "Только председатель совета кооператива может создавать кооперативные участки");
  };

  // Проверка на наличие председателя в списке членов совета
  eosio::check(std::find(members.begin(), members.end(), chairman) != members.end(), "Председатель должен быть в списке членов совета");

  unions.emplace(chairman, [&](auto &b) {
    b.id = unions.available_primary_key();
    b.parent_id = parent_id; //если кооперативный участок >= 0
    b.members = members;
    b.chairman = chairman;
    b.created_at = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
  });

}


//TODO modify members, but cannot delete chairman


uint64_t soviet::get_members_count(uint64_t union_id) {
  union_index unions(_soviet, _soviet.value);

  auto uni = unions.find(union_id);
  eosio::check(uni != unions.end(), "Совет не найден");

  return uni->members.size();

};

