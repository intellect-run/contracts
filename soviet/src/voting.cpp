using namespace eosio;

void check_for_any_vote_exist(eosio::name member, uint64_t document_id) {
  // Инициализация таблицы решений
  documents_index documents(_soviet, _soviet.value);

  // Поиск решения по document_id
  auto document = documents.find(document_id);
  eosio::check(document != documents.end(), "Решение с данным ID не найдено.");

  // Проверяем, есть ли имя участника в голосах за
  eosio::check(std::find(document->votes_for.begin(), document->votes_for.end(), member) == document->votes_for.end(), "Участник уже голосовал за данное решение.");

  // Проверяем, есть ли имя участника в голосах против
  eosio::check(std::find(document->votes_against.begin(), document->votes_against.end(), member) == document->votes_against.end(), "Участник уже голосовал против данного решения.");
};


std::pair<uint64_t, uint64_t> get_votes_count(uint64_t document_id) {
  // Инициализация таблицы решений
  documents_index documents(_soviet, _soviet.value);

  // Поиск решения по document_id
  auto document_it = documents.find(document_id);
  eosio::check(document_it != documents.end(), "Решение с данным ID не найдено.");

  // Возврат количества голосов за и против
  return std::make_pair(document_it->votes_for.size(), document_it->votes_against.size());

};


void add_vote_for(eosio::name member, uint64_t document_id, bool approved) {
  // Инициализация таблицы решений
  documents_index documents(_soviet, _soviet.value);

  // Поиск решения по document_id
  auto document_it = documents.find(document_id);
  eosio::check(document_it != documents.end(), "Решение с данным ID не найдено.");

  // Модифицируем запись в таблице
  documents.modify(document_it, _soviet, [&](auto& row) {
    row.votes_for.push_back(member); // Добавляем участника в голоса за
    row.approved = approved;
  });
}


void add_vote_against(eosio::name member, uint64_t document_id) {
  // Инициализация таблицы решений
  documents_index documents(_soviet, _soviet.value);

  // Поиск решения по document_id
  auto document_it = documents.find(document_id);
  eosio::check(document_it != documents.end(), "Решение с данным ID не найдено.");

  // Модифицируем запись в таблице
  documents.modify(document_it, _soviet, [&](auto& row) {
    row.votes_against.push_back(member); // Добавляем участника в голоса против
  });
}

void soviet::votefor(eosio::name member, uint64_t document_id) { 
  
  if (!has_auth(member)) {
    require_auth(permission_level{member, "oracle"_n});
  } else {
    require_auth(member);
  }
  
  is_valid_member(member);
  check_for_any_vote_exist(member, document_id);

  auto [votes_for_count, votes_against_count] = get_votes_count(document_id);

  votes_for_count++;

  uint64_t total_members = get_members_count(0);
  uint64_t consensus_percent = 50;
  
  // Рассчитываем, больше ли количество голосов "за" заданного процента консенсуса от общего количества участников
  bool approved = votes_for_count * 100 > total_members * consensus_percent;

  add_vote_for(member, document_id, approved);

};


void soviet::voteagainst(eosio::name member, uint64_t document_id) { 
  
  if (!has_auth(member)) {
    require_auth(permission_level{member, "provide"_n});
  } else {
    require_auth(member);
  }
  
  is_valid_member(member);
  check_for_any_vote_exist(member, document_id);
  add_vote_against(member, document_id);
};


void soviet::cancelvote(eosio::name member, uint64_t document_id) {
  
  if (!has_auth(member)) {
    require_auth(permission_level{member, "provide"_n});
  } else {
    require_auth(member);
  }

  documents_index documents(_soviet, _soviet.value); 
  auto document_it = documents.find(document_id);
  eosio::check(document_it != documents.end(), "Решение не найдено.");

  // Удаление голоса "за", если он существует
  auto vote_for_it = std::find(document_it->votes_for.begin(), document_it->votes_for.end(), member);
  if (vote_for_it != document_it->votes_for.end()) {
    uint64_t total_members = get_members_count(0);
    uint64_t consensus_percent = 50;

    documents.modify(document_it, _soviet, [&](auto& row) {
      row.votes_for.erase(vote_for_it);
      uint64_t votes_for_count = row.votes_for.size();
      row.approved = (votes_for_count * 100 / total_members) > consensus_percent;
    });
  }

  // Удаление голоса "против", если он существует
  auto vote_against_it = std::find(document_it->votes_against.begin(), document_it->votes_against.end(), member);
  if (vote_against_it != document_it->votes_against.end()) {
    documents.modify(document_it, _soviet, [&](auto& row) {
      row.votes_against.erase(vote_against_it);
    });
  }
}
