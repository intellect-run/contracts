using namespace eosio;

void soviet::is_valid_action_for_automation(eosio::name action_type) {
  std::vector<eosio::name> valid_types = {"regaccount"_n, "authorize"_n};

  eosio::check(std::find(valid_types.begin(), valid_types.end(), action_type) != valid_types.end(), "Действие не найдено среди допустимых типов.");
  
}

void soviet::automate(eosio::name coop_username, uint64_t board_id, eosio::name member, eosio::name action_type, eosio::name permission_name, std::string encrypted_private_key) {

  require_auth(member);
 
  boards_index boards(_soviet, coop_username.value);
  auto board = boards.find(board_id);
  eosio::check(board != boards.end(), "Совет не найден");

  if (action_type == "authorize"_n){
    board -> is_valid_chairman(member);  
  } else {
    soviet::is_valid_action_for_automation(action_type);  
  };

  automator_index automator(_soviet, coop_username.value);
  auto by_member_action_index = automator.template get_index<"bymembaction"_n>();
  auto idx = combine_ids(member.value, action_type.value);
  auto autom = by_member_action_index.find(idx);
  
  eosio::check(autom == by_member_action_index.end(), "Автоматизация по данному действию уже установлена");

  automator.emplace(member, [&](auto &a){
    a.id = automator.available_primary_key();
    a.coop_username = coop_username;
    a.board_id = board_id;
    a.member = member;
    a.action_type = action_type;
    a.permission_name = permission_name;
    a.encrypted_private_key = encrypted_private_key;
  });

}


void soviet::disautomate(eosio::name coop_username, uint64_t board_id, eosio::name member, uint64_t automation_id ) {
  require_auth(member);

  automator_index automator(_soviet, coop_username.value);
  auto autom = automator.find(automation_id);
  eosio::check(autom -> board_id == board_id, "Указан неверный идентификатор совета");
  eosio::check(autom -> member == member, "Это не ваша автоматизация для удаления");

  automator.erase(autom);
}

