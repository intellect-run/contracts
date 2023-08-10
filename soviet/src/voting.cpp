using namespace eosio;


void check_for_any_vote_exist(eosio::name member, uint64_t decision_id) {
  // Инициализация таблицы решений
  decision_index decisions(_me, _me.value);

  // Поиск решения по decision_id
  auto decision = decisions.find(decision_id);
  eosio::check(decision != decisions.end(), "Решение с данным ID не найдено.");

  // Проверяем, есть ли имя участника в голосах за
  eosio::check(std::find(decision->votes_for.begin(), decision->votes_for.end(), member) == decision->votes_for.end(), "Участник уже голосовал за данное решение.");

  // Проверяем, есть ли имя участника в голосах против
  eosio::check(std::find(decision->votes_against.begin(), decision->votes_against.end(), member) == decision->votes_against.end(), "Участник уже голосовал против данного решения.");
};


std::pair<uint64_t, uint64_t> get_votes_count(uint64_t decision_id) {
  // Инициализация таблицы решений
  decision_index decisions(_me, _me.value);

  // Поиск решения по decision_id
  auto decision_it = decisions.find(decision_id);
  eosio::check(decision_it != decisions.end(), "Решение с данным ID не найдено.");

  // Возврат количества голосов за и против
  return std::make_pair(decision_it->votes_for.size(), decision_it->votes_against.size());

};


void add_vote_for(eosio::name member, uint64_t decision_id, bool approved) {
  // Инициализация таблицы решений
  decision_index decisions(_me, _me.value);

  // Поиск решения по decision_id
  auto decision_it = decisions.find(decision_id);
  eosio::check(decision_it != decisions.end(), "Решение с данным ID не найдено.");

  // Модифицируем запись в таблице
  decisions.modify(decision_it, _me, [&](auto& row) {
    row.votes_for.push_back(member); // Добавляем участника в голоса за
    row.approved = approved;
  });
}


void add_vote_against(eosio::name member, uint64_t decision_id) {
  // Инициализация таблицы решений
  decision_index decisions(_me, _me.value);

  // Поиск решения по decision_id
  auto decision_it = decisions.find(decision_id);
  eosio::check(decision_it != decisions.end(), "Решение с данным ID не найдено.");

  // Модифицируем запись в таблице
  decisions.modify(decision_it, _me, [&](auto& row) {
    row.votes_against.push_back(member); // Добавляем участника в голоса против
  });
}


void soviet::votefor(eosio::name member, uint64_t decision_id) { 
  require_auth(member);

  is_valid_member(member);
  check_for_any_vote_exist(member, decision_id);

  auto [votes_for_count, votes_against_count] = get_votes_count(decision_id);

  votes_for_count++;

  uint64_t total_members = get_members_count(0);
  uint64_t consensus_percent = get_consensus_percent(0);
  
  // Рассчитываем, больше ли количество голосов "за" заданного процента консенсуса от общего количества участников
  bool approved = votes_for_count * 100 > total_members * consensus_percent;

  add_vote_for(member, decision_id, approved);

};


void soviet::voteagainst(eosio::name member, uint64_t decision_id) { 
  require_auth(member);
  is_valid_member(member);
  check_for_any_vote_exist(member, decision_id);
  add_vote_against(member, decision_id);
};


void soviet::cancelvote(eosio::name member, uint64_t decision_id) {
  require_auth(member);

  decision_index decisions(_me, _me.value); 
  auto decision_it = decisions.find(decision_id);
  eosio::check(decision_it != decisions.end(), "Решение не найдено.");

  // Удаление голоса "за", если он существует
  auto vote_for_it = std::find(decision_it->votes_for.begin(), decision_it->votes_for.end(), member);
  if (vote_for_it != decision_it->votes_for.end()) {
    uint64_t total_members = get_members_count(0);
    uint64_t consensus_percent = get_consensus_percent(0);

    decisions.modify(decision_it, _me, [&](auto& row) {
      row.votes_for.erase(vote_for_it);
      uint64_t votes_for_count = row.votes_for.size();
      row.approved = (votes_for_count * 100 / total_members) > consensus_percent;
    });
  }

  // Удаление голоса "против", если он существует
  auto vote_against_it = std::find(decision_it->votes_against.begin(), decision_it->votes_against.end(), member);
  if (vote_against_it != decision_it->votes_against.end()) {
    decisions.modify(decision_it, _me, [&](auto& row) {
      row.votes_against.erase(vote_against_it);
    });
  }
}
