using namespace eosio;

void soviet::check_and_sign_by_chairman(eosio::name action_type, uint64_t decision_id) {
  board_index boards(_me, _me.value);
  auto board = boards.find(0);
  eosio::check(board != boards.end(), "Совет не найден");
  
  autochair_index autochair(_me, _me.value);
  auto chair_action = autochair.find(action_type.value);

  if (chair_action != autochair.end()){

    eosio::name chairman = board -> chairman;

    // Отправка действия authorize
    action(
      permission_level{chairman, "active"_n},    // Разрешение на действие от лица аккаунта chairman
      _me,                                       // Контракт, в котором определен метод authorize
      "authorize"_n,                             // Имя метода, который нужно вызвать
      std::make_tuple(chairman, decision_id)     // Параметры для метода authorize
    ).send();

    // Отправка действия exec
    action(
      permission_level{chairman, "active"_n},    // Разрешение на действие от лица аккаунта chairman
      _me,                                       // Контракт, в котором определен метод exec
      "exec"_n,                                  // Имя метода, который нужно вызвать
      std::make_tuple(chairman, decision_id)     // Параметры для метода exec
    ).send();
  }
}


void soviet::check_and_sign_by_members(eosio::name action_type, uint64_t decision_id) {
  
  board_index boards(_me, _me.value);
  auto board = boards.find(0);
  eosio::check(board != boards.end(), "Совет не найден");

  automator_index automator(_me, _me.value);
  auto by_action_index = automator.template get_index<"byaction"_n>();

  decision_index decisions(_me, _me.value);
  auto decision = decisions.find(decision_id);
  eosio::check(decision != decisions.end(), "Решение не найдено");

  for (const auto& member : board->members) {
    auto autom = by_action_index.find(action_type.value);
    if (autom != by_action_index.end() && autom->member == member) {
      
      // Проверяем, голосовал ли участник ранее
      if (std::find(decision->votes_for.begin(), decision->votes_for.end(), member) != decision->votes_for.end() ||
          std::find(decision->votes_against.begin(), decision->votes_against.end(), member) != decision->votes_against.end()) {
        continue; // Если голосовал, пропускаем этого участника
      }

      action(
        permission_level{member, "active"_n},
        _me,
        "votefor"_n,
        std::make_tuple(member, decision_id)
      ).send();
    }
  }

}


void soviet::is_valid_action(eosio::name action_type) {
  std::vector<eosio::name> valid_types = {"regaccount"_n, "authorize"_n};

  eosio::check(std::find(valid_types.begin(), valid_types.end(), action_type) != valid_types.end(), "Действие не найдено среди допустимых типов.");
  
}

void soviet::automate(eosio::name member, eosio::name action_type) {

  require_auth(member);
  soviet::is_valid_member(member);
  
  is_valid_action(action_type);
  
  board_index boards(_me, _me.value);
  auto board = boards.find(0);
  eosio::check(board != boards.end(), "Совет не найден");

  automator_index automator(_me, _me.value);
  auto by_action_index = automator.template get_index<"byaction"_n>();
            
  auto autom = by_action_index.find(action_type.value);
  
  eosio::check(autom == by_action_index.end(), "Автоматизация по данному действию уже установлена");

  automator.emplace(member, [&](auto &a){
    a.id = automator.available_primary_key();
    a.member = member;
    a.action_type = action_type;
  });

}


void soviet::disautomate(eosio::name member, uint64_t automation_id ) {
  require_auth(member);

  soviet::is_valid_member(member);

  automator_index automator(_me, _me.value);
  auto autom = automator.find(automation_id);

  eosio::check(autom -> member == member, "Это не ваша автоматизация для удаления");

  automator.erase(autom);
}


void soviet::autochair(eosio::name chairman, eosio::name action_type) {
  require_auth(chairman);
  soviet::is_valid_chairman(chairman);
  is_valid_action(action_type);

  autochair_index autochair(_me, _me.value);
  auto ac = autochair.find(action_type);
  eosio::check(ac == autochair.end(), "Действие уже автоматизировано");

  autochair.emplace(chairman, [&](auto &a){
    a.action_type = action_type;
  });
}

void soviet::disautochair(eosio::name chairman, eosio::name action_type) {
  require_auth(chairman);
  soviet::is_valid_chairman(chairman);

  autochair_index autochair(_me, _me.value);
  auto ac = autochair.find(action_type);
  eosio::check(ac != autochair.end(), "Действие не найдено");

  autochair.erase(ac);
}
