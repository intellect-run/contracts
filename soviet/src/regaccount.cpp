using namespace eosio;

void soviet::regaccount(eosio::name username) { 
  require_auth(_registrator);

  documents_index documents(_soviet, _soviet.value);
  auto id = get_global_id(_soviet, "documents"_n);
  documents.emplace(_soviet, [&](auto &d){
    d.id = id;
    d.type = _regaccount_action;
    d.secondary_id = username.value;
  });

  action(
    permission_level{ _soviet, "active"_n},
    _soviet,
    "newid"_n,
    std::make_tuple(id)
  ).send();
};


void soviet::regaccount_effect(eosio::name executer, uint64_t document_id, eosio::name username) { 
  documents_index documents(_soviet, _soviet.value);
  auto document = documents.find(document_id);
  
  action(
      permission_level{ _soviet, "active"_n},
      "registrator"_n,
      "confirmreg"_n,
      std::make_tuple(username)
  ).send();
    
  documents.modify(document, executer, [&](auto &d){
    d.executed = true;
  });

};
