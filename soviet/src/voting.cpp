using namespace eosio;

void add_vote_for(eosio::name coop_username, eosio::name member, uint64_t decision_id, bool approved) {
  // Инициализация таблицы решений
  decisions_index decisions(_soviet, coop_username.value);

  // Поиск решения по decision_id
  auto decision = decisions.find(decision_id);
  eosio::check(decision != decisions.end(), "Решение с данным ID не найдено.");

  // Модифицируем запись в таблице
  decisions.modify(decision, _soviet, [&](auto& row) {
    row.votes_for.push_back(member); // Добавляем участника в голоса за
    row.approved = approved;
  });
}


void add_vote_against(eosio::name coop_username, eosio::name member, uint64_t decision_id) {
  // Инициализация таблицы решений
  decisions_index decisions(_soviet, coop_username.value);

  auto decision = decisions.find(decision_id);
  // Модифицируем запись в таблице
  decisions.modify(decision, _soviet, [&](auto& row) {
    row.votes_against.push_back(member); // Добавляем участника в голоса против
  });
}

void soviet::votefor(eosio::name coop_username, eosio::name member, uint64_t decision_id) { 
  if (!has_auth(member)) {
    require_auth(permission_level{member, "oracle"_n});
  } else {
    require_auth(member);
  }
  
  decisions_index decisions(_soviet, coop_username.value);
  auto decision = decisions.find(decision_id);
  eosio::check(decision != decisions.end(), "Документ не найден");
  
  auto board = get_board_by_type_or_fail(coop_username, "soviet"_n);
  eosio::check(board.is_voting_member(member), "У вас нет права голоса");
  
  decision -> check_for_any_vote_exist(member); 

  auto [votes_for_count, votes_against_count] = decision->get_votes_count();

  votes_for_count++;

  uint64_t total_members = board.get_members_count();
  uint64_t consensus_percent = 50;
  
  // Рассчитываем, больше ли количество голосов "за" заданного процента консенсуса от общего количества участников
  bool approved = votes_for_count * 100 > total_members * consensus_percent;

  add_vote_for(coop_username, member, decision_id, approved);

};


void soviet::voteagainst(eosio::name coop_username, eosio::name member, uint64_t decision_id) { 
  
  if (!has_auth(member)) {
    require_auth(permission_level{member, "provide"_n});
  } else {
    require_auth(member);
  }
  
  decisions_index decisions(_soviet, coop_username.value);
  auto decision = decisions.find(decision_id);
  eosio::check(decision != decisions.end(), "Документ не найден");

  auto board = get_board_by_type_or_fail(coop_username, "soviet"_n);

  eosio::check(board.is_voting_member(member), "У вас нет права голоса");
  
  decision -> check_for_any_vote_exist(member); 

  add_vote_against(coop_username, member, decision_id);
};


void soviet::cancelvote(eosio::name coop_username, eosio::name member, uint64_t decision_id) {
  
  if (!has_auth(member)) {
    require_auth(permission_level{member, "provide"_n});
  } else {
    require_auth(member);
  }

  decisions_index decisions(_soviet, coop_username.value); 
  auto decision = decisions.find(decision_id);
  eosio::check(decision != decisions.end(), "Документ не найден");
  
  // Удаление голоса "за", если он существует
  auto board = get_board_by_type_or_fail(coop_username, "soviet"_n);

  auto vote_for_it = std::find(decision->votes_for.begin(), decision->votes_for.end(), member);
  if (vote_for_it != decision->votes_for.end()) {
    uint64_t total_members = board.get_members_count();
    uint64_t consensus_percent = 50;

    decisions.modify(decision, _soviet, [&](auto& row) {
      row.votes_for.erase(vote_for_it);
      uint64_t votes_for_count = row.votes_for.size();
      row.approved = (votes_for_count * 100 / total_members) > consensus_percent;
    });
  }

  // Удаление голоса "против", если он существует
  auto vote_against_it = std::find(decision->votes_against.begin(), decision->votes_against.end(), member);
  if (vote_against_it != decision->votes_against.end()) {
    decisions.modify(decision, _soviet, [&](auto& row) {
      row.votes_against.erase(vote_against_it);
    });
  }
}
