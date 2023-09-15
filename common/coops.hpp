#pragma once

/**
 * @ingroup public_tables
 * @brief Структура, представляющая членов доски.
 * @details Эта структура содержит информацию о членах доски, включая их уникальные имена, статус участия в голосовании,
 * название должности и позицию в доске.
 */
struct board_member {
  eosio::name username; ///< Уникальное имя члена доски.
  bool is_voting; ///< Флаг, указывающий, имеет ли член доски право голоса.
  std::string position_title; ///< Название должности члена доски.
  eosio::name position; ///< Позиция члена в доске:
  // (CHAIRMAN, _('chairman')),
  // (CHAIRMAN_VP, _('vpchairman')),
  // (SECRETARY, _('secretary')),
  // (ACCOUNTING, _('accounting')),
  // (MEMBER, _('member')),
  // (INVITED, _(‘invited')),
};
/**
 * @ingroup public_tables
 * @brief Структура советов кооперативов
 * @details Эта структура содержит информацию о досках кооператива, их типе, названии, описании и членах.
 */
struct [[eosio::table, eosio::contract(SOVIET)]] boards {
  uint64_t id; ///< Уникальный идентификатор доски.
  eosio::name type; ///< Тип доски:
  // (soviet, _('Board of Members')),   # Совет кооператива
  // (executive, _('Executive Board')), # Правление
  // (audit, _('Audit and Revision Board')),  # Ревизионный
  // (other, _('Other committee')),   # Другая комиссия
  std::string name; ///< Название доски.
  std::string description; ///< Описание доски.
  std::vector<board_member> members; ///< Список членов доски.

  eosio::time_point_sec created_at; ///< Время создания доски.
  eosio::time_point_sec last_update; ///< Время последнего обновления информации о доске.


  /**
   * @brief Возвращает первичный ключ доски.
   * @return uint64_t - первичный ключ, равный уникальному идентификатору доски.
   */
  uint64_t primary_key() const { return id; }

  /**
   * @brief Возвращает ключ для индексации по типу доски.
   * @return uint64_t - ключ, равный значению типа доски.
   */
  uint64_t by_type() const { return type.value; }

  bool is_valid_member(eosio::name member) const {
    for (const auto& m : members) {
      if (m.username == member)
        return true;
    }
    return false;
  }
 
  bool is_voting_member(eosio::name member) const {
    for (const auto& m : members) {
      if (m.username == member && m.is_voting == true)
        return true;
    }
    return false;
  }


  bool is_valid_chairman(eosio::name chairman) const {
    for (const auto& m : members) {
      if (m.username == chairman && (m.position == "chairman"_n || m.position == "vpchairman"_n))
        return true;
    }
    return false;
  }

  bool has_voting_right(eosio::name member) const {
    for (const auto& m : members) {
        if (m.username == member && m.is_voting)
            return true;
    }
    return false;
  }


  uint64_t get_members_count() const {
    return members.size();
  };

};

typedef eosio::multi_index< "boards"_n, boards,
eosio::indexed_by<"bytype"_n, eosio::const_mem_fun<boards, uint64_t,
                                                       &boards::by_type>>> boards_index;


/**
 * @ingroup public_structs
 * @brief Структура, представляющая права доступа.
 * @details Эта структура содержит информацию о правах доступа, связанных с конкретным контрактом и действием.
 */
struct right {
  eosio::name contract; ///< Имя контракта, к которому применяется право доступа.
  eosio::name action_name; ///< Имя действия, к которому применяется право доступа.
};

/**
 * @ingroup public_tables
 * @brief Структура, представляющая администраторов кооператива.
 * @details Эта структура содержит информацию об администраторах, их уникальных именах, должностях и правах.
 */
struct [[eosio::table, eosio::contract(SOVIET)]] staff {
  eosio::name username; ///< Уникальное имя администратора.
  std::string position_title; ///< Название должности администратора.
  std::vector<right> rights; ///< Список прав администратора.

  eosio::time_point_sec created_at; ///< Время создания записи об администраторе.
  eosio::time_point_sec updated_at; ///< Время последнего обновления информации об администраторе.

  uint64_t primary_key() const { return username.value; } ///< Первичный ключ для индексации по имени администратора

  bool has_right(eosio::name contract, eosio::name action_name) const {
    for (const auto& r : rights) {
        if (r.contract == contract && r.action_name == action_name) {
            return true;
        }
    }
    return false;
  }
};

typedef eosio::multi_index<"staff"_n, staff> staff_index; ///< Тип мультииндекса для таблицы администраторов



/**
 * @ingroup public_tables
 * @brief Структура, представляющая членов кооператива.
 * @details Эта структура содержит информацию о членах кооператива, включая их уникальные имена, дату создания, дату последнего обновления,
 * дату последнего минимального платежа, должность, позицию, флаги их статуса и участия.
 */
struct [[eosio::table, eosio::contract(REGISTRATOR)]] members {
  eosio::name username; ///< Уникальное имя члена кооператива.
  eosio::time_point_sec created_at; ///< Время создания записи о члене.
  eosio::time_point_sec last_update; ///< Время последнего обновления информации о члене.
  eosio::time_point_sec last_min_pay; ///< Время последнего минимального платежа.
  std::string position_title; ///< Название должности члена.
  eosio::name position; ///< Позиция члена в кооперативе:
  // (('chairman')),
  // (('vpchairman')),
  // (('director')),
  // (('vpdirector')),
  // (('boardmember')),
  // (('execmember')),
  // (('votingmember')),
  // (('assocmember')),
  bool is_accepted; ///< Флаг, указывающий, принят ли член в кооператив.
  bool is_initial; ///< Флаг, указывающий, является ли член начальным.
  bool is_minimum; ///< Флаг, указывающий, является ли член членом с минимальными взносами.
  bool is_voting; ///< Флаг, указывающий, имеет ли член право голоса.

  /**
   * @brief Возвращает первичный ключ учетной записи члена кооператива.
   * @return uint64_t - первичный ключ, равный значению имени члена кооператива.
   */
  uint64_t primary_key() const {
    return username.value;
  } /*!< return username - primary_key */

  /**
   * @brief Возвращает ключ для индексации по времени последнего минимального платежа.
   * @return uint64_t - ключ, равный количеству секунд с начала эпохи Unix.
   */
  uint64_t bylastpay() const {
    return last_min_pay.sec_since_epoch();
  }
};

typedef eosio::multi_index< "members"_n, members,
  eosio::indexed_by<"bylastpay"_n, eosio::const_mem_fun<members, uint64_t, &members::bylastpay>>
> members_index;


/**
 * @ingroup public_tables
 * @brief Структура, представляющая решения кооператива.
 * @details Эта структура содержит информацию о решениях, включая уникальный идентификатор, имя кооператива, тип решения,
 * идентификатор карточки, списки голосов "за" и "против", а также различные флаги состояния решения.
 */
struct [[eosio::table, eosio::contract(SOVIET)]] decisions {
  uint64_t id; ///< Уникальный идентификатор решения.
  eosio::name coop_username; ///< Имя кооператива, связанного с решением.
  eosio::name type; ///< Тип решения:
  // openproposal | regaccount | change | contribute | withdraw
  uint64_t card_id; ///< Идентификатор карточки, связанной с решением.

  std::vector<eosio::name> votes_for; ///< Список имен, голосовавших "за" решение.
  std::vector<eosio::name> votes_against; ///< Список имен, голосовавших "против" решения.
  
  bool approved = false; ///< Сигнальный флаг, указывающий, что решение советом принято.
  bool validated = false; ///< Сигнальный флаг, указывающий, что администратор подтверждает валидность решения.
  bool authorized = false; ///< Флаг, указывающий, что получена авторизация председателя после голосования и валидации до исполнения.
  bool certified = false; ///< Флаг, указывающий, что получено сертификация секретаря.
  bool executed = false; ///< Сигнальный флаг, указывающий, что решение будет исполнено.

  /**
   * @brief Возвращает первичный ключ решения.
   * @return uint64_t - первичный ключ, равный уникальному идентификатору решения.
   */
  uint64_t primary_key() const { return id; }

  /**
   * @brief Возвращает ключ для индексации по имени кооператива.
   * @return uint64_t - ключ, равный значению имени кооператива.
   */
  uint64_t by_coop() const { return coop_username.value; } 

  /**
   * @brief Возвращает ключ для индексации по идентификатору карточки.
   * @return uint64_t - ключ, равный идентификатору карточки.
   */
  uint64_t by_card() const { return card_id; }

  /**
   * @brief Возвращает ключ для индексации по типу решения.
   * @return uint64_t - ключ, равный значению типа решения.
   */
  uint64_t bytype() const { return type.value; }

  /**
   * @brief Возвращает ключ для индексации по статусу "принято".
   * @return uint64_t - ключ, равный статусу "принято" (1, если решение принято, иначе 0).
   */
  uint64_t byapproved() const { return approved; }

  /**
   * @brief Возвращает ключ для индексации по статусу "подтверждено".
   * @return uint64_t - ключ, равный статусу "подтверждено" (1, если решение подтверждено, иначе 0).
   */
  uint64_t byvalidated() const { return validated; }

  /**
   * @brief Возвращает ключ для индексации по статусу "авторизовано".
   * @return uint64_t - ключ, равный статусу "авторизовано" (1, если решение авторизовано, иначе 0).
   */
  uint64_t byauthorized() const { return authorized; }

  /**
   * @brief Возвращает ключ для индексации по статусу "сертифицировано".
   * @return uint64_t - ключ, равный статусу "сертифицировано" (1, если решение сертифицировано, иначе 0).
   */
  uint64_t bycertified() const { return certified; }

  /**
   * @brief Возвращает ключ для индексации по статусу "исполнено".
   * @return uint64_t - ключ, равный статусу "исполнено" (1, если решение исполнено, иначе 0).
   */
  uint64_t byexecuted() const { return executed; }

  void check_for_any_vote_exist(eosio::name member) const {
    // Проверяем, есть ли имя участника в голосах за
    eosio::check(std::find(votes_for.begin(), votes_for.end(), member) == votes_for.end(), "Участник уже голосовал за данное решение.");

    // Проверяем, есть ли имя участника в голосах против
    eosio::check(std::find(votes_against.begin(), votes_against.end(), member) == votes_against.end(), "Участник уже голосовал против данного решения.");
  };

  std::pair<uint64_t, uint64_t> get_votes_count() const {
    return std::make_pair(votes_for.size(), votes_against.size());
  };
};

typedef eosio::multi_index< "decisions"_n, decisions,
  eosio::indexed_by<"bycoop"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::by_coop>>,
  eosio::indexed_by<"bycard"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::by_card>>,
  eosio::indexed_by<"bytype"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::bytype>>,
  eosio::indexed_by<"byapproved"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::byapproved>>,
  eosio::indexed_by<"byvalidated"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::byvalidated>>,
  eosio::indexed_by<"byauthorized"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::byauthorized>>,
  eosio::indexed_by<"bycertified"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::bycertified>>,
  eosio::indexed_by<"byexecuted"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::byexecuted>>

> decisions_index;


boards get_board_by_id(eosio::name coop_username, uint64_t board_id){
  boards_index boards(_soviet, coop_username.value);
  auto board = boards.find(board_id);
  
  eosio::check(board != boards.end(), "Совет не найден");

  return *board; 

};


boards get_board_by_type_or_fail(eosio::name coop_username, eosio::name type){
  boards_index boards(_soviet, coop_username.value);
  auto boards_by_type_index = boards.template get_index<"bytype"_n>();
  auto exist = boards_by_type_index.find(type.value);
  
  eosio::check(exist != boards_by_type_index.end(), "Совет не найден");

  return *exist;

};

bool check_for_exist_board_by_type(eosio::name coop_username, eosio::name type){
  boards_index boards(_soviet, coop_username.value);

  auto boards_by_type_index = boards.template get_index<"bytype"_n>();

  auto exist = boards_by_type_index.find(type.value);
  
  if (exist != boards_by_type_index.end())
    return true;
  else return false;
}

