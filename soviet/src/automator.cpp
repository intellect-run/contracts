using namespace eosio;

void soviet::is_valid_action(eosio::name action_type) {
  std::vector<eosio::name> valid_types = {"regaccount"_n, "authorize"_n};

  eosio::check(std::find(valid_types.begin(), valid_types.end(), action_type) != valid_types.end(), "Действие не найдено среди допустимых типов.");
  
}

void soviet::automate(eosio::name member, eosio::name action_type, eosio::name provider, std::string private_key) {

  require_auth(member);
  
  automator_index automator(_soviet, _soviet.value);
  auto by_member_action_index = automator.template get_index<"bymembaction"_n>();

  if (action_type == "authorize"_n){
    is_valid_chairman(member);  
  } else {
    is_valid_action(action_type);  
  };
  
  auto idx = combine_ids(member.value, action_type.value);
            
  auto autom = by_member_action_index.find(idx);
  
  eosio::check(autom == by_member_action_index.end(), "Автоматизация по данному действию уже установлена");

  automator.emplace(member, [&](auto &a){
    a.id = automator.available_primary_key();
    a.member = member;
    a.action_type = action_type;
    a.provider = provider;
    a.private_key = private_key;
  });

}


void soviet::disautomate(eosio::name member, uint64_t automation_id ) {
  require_auth(member);

  soviet::is_valid_member(member);

  automator_index automator(_soviet, _soviet.value);
  auto autom = automator.find(automation_id);

  eosio::check(autom -> member == member, "Это не ваша автоматизация для удаления");

  automator.erase(autom);
}

