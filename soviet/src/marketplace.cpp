using namespace eosio;

void soviet::change(uint64_t order_id) { 
  require_auth(_marketplace);

  documents_index documents(_soviet, _soviet.value);
  auto id = get_global_id(_soviet, "documents"_n);
  
  documents.emplace(_soviet, [&](auto &d){
    d.id = id;
    d.type = _change_action;
    d.secondary_id = order_id;
  });

  action(
    permission_level{ _soviet, "active"_n},
    _soviet,
    "newid"_n,
    std::make_tuple(id)
  ).send();
  
};


void soviet::change_effect(eosio::name executer, uint64_t document_id, eosio::name username) { 
  documents_index documents(_soviet, _soviet.value);
  auto document = documents.find(document_id);
  
  action(
      permission_level{ _soviet, "active"_n},
      "marketplace"_n,
      "authorize"_n,
      std::make_tuple(username)
  ).send();
    
  documents.modify(document, executer, [&](auto &d){
    d.executed = true;
  });

};
