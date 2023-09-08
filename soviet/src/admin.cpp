#pragma once

void soviet::addadmin(uint64_t union_id, eosio::name chairman, eosio::name username, std::vector<eosio::name> rights, std::string meta) {
  require_auth(chairman);

  admins_index admins(_soviet, _soviet.value);
  union_index unions(_soviet, _soviet.value);

  auto uni = unions.find(union_id);
  eosio::check(uni != unions.end(), "Совет еще не создан");
  eosio::check(uni -> chairman == chairman, "Вы не председатель, чтобы добавлять админов!");

  auto admin = admins.find(username.value);

  if (admin == admins.end())
    admins.emplace(chairman, [&](auto &a){
      a.username = username;
      a.rights = rights;
      a.meta = meta;
    });

};


void soviet::rmadmin(uint64_t union_id, eosio::name chairman, eosio::name username) {
  require_auth(chairman);

  admins_index admins(_soviet, _soviet.value);
  union_index unions(_soviet, _soviet.value);

  auto uni = unions.find(union_id);
  eosio::check(uni != unions.end(), "Совет еще не создан");
  eosio::check(uni -> chairman == chairman, "Вы не председатель, чтобы удалять админов!");
  
  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "Администратор не найден");

  admins.erase(admin);

};


void soviet::setadmrights(uint64_t union_id, eosio::name chairman, eosio::name username, std::vector<eosio::name> rights) {
  require_auth(chairman);

  admins_index admins(_soviet, _soviet.value);
  union_index unions(_soviet, _soviet.value);

  auto uni = unions.find(union_id);
  eosio::check(uni != unions.end(), "Совет еще не создан");
  eosio::check(uni -> chairman == chairman, "Только председатель может изменять права администраторов");

  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "Администратор не найден");

  admins.modify(admin, chairman, [&](auto &a){
    a.rights = rights;
  });  
};
  

void soviet::validate(uint64_t union_id, eosio::name username, uint64_t decision_id) { 
  require_auth(username);

  union_index unions(_soviet, _soviet.value);
  auto uni = unions.find(union_id);
  eosio::check(uni != unions.end(), "Совет еще не создан");

  admins_index admins(_soviet, _soviet.value);

  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "У вас нет прав администратора");

  decision_index decisions(_soviet, _soviet.value);
  auto decision = decisions.find(decision_id);
  eosio::check(decision != decisions.end(), "Решение не найдено");

  decisions.modify(decision, username, [&](auto &d){
    d.validated = true;
  });
  
  oracle_index oracle(_soviet, _soviet.value);  
  auto ora = oracle.find(decision -> id);
  
  if (ora == oracle.end())
    oracle.emplace(_soviet, [&](auto &o) {
      o.id = decision -> id;
    });
    
}
