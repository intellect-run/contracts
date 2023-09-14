#pragma once


struct board_member {
  eosio::name username;
  bool is_voting;
  std::string position_title;
  eosio::name position;
    // (CHAIRMAN, _('chairman')),
		// (CHAIRMAN_VP, _('vpchairman')),
		// (SECRETARY, _('secretary')),	
		// (ACCOUNTING, _('accounting')),
		// (MEMBER, _('member')),
		// (INVITED, _(‘invited')),
};

struct [[eosio::table, eosio::contract(SOVIET)]] boards {
  uint64_t id;
  eosio::name type;
//    (soviet, _('Board of Members')),		# Совет кооператива / участка
// 		(executive, _('Executive Board')),		# Правление
// 		(audit, _('Audit and Revision Board')),	# Ревизионный
// 		(other, _('Other committee')),		# Другая комиссия
  std::string name;
  std::string description;
  std::vector <board_member> members;
  
  eosio::time_point_sec created_at;
  eosio::time_point_sec last_update;

  uint64_t primary_key() const { return id; }
  uint64_t by_type() const {return type.value;}

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
 * @brief Таблица администраторов для контракта "soviet"
 * 
 * Эта таблица используется для хранения информации об администраторах и их правах в системе.
 * 
 * @param username Имя администратора, используемое как первичный ключ
 * @param rights Вектор прав, которыми обладает администратор
 * @param meta Дополнительная метаинформация, связанная с администратором
 * 
 * Пример использования:
 * @code
 * admins_index admins(_me, _me.value);
 * auto admin = admins.find(username.value);
 * @endcode
 */

struct right {
  eosio::name contract;
  eosio::name action_name;
};

struct [[eosio::table, eosio::contract(SOVIET)]] staff {
  eosio::name username; ///< Уникальное имя администратора
  std::string position_title;
  std::vector<right> rights; ///< Список прав администратора
 
  eosio::time_point_sec created_at;
  eosio::time_point_sec updated_at;

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


struct [[eosio::table, eosio::contract(REGISTRATOR)]] members {
  eosio::name username;
  eosio::time_point_sec created_at;
  eosio::time_point_sec last_update;
  eosio::time_point_sec last_min_pay;
  std::string position_title;
  eosio::name position;
  // (7, _('chairman')),
  // (6, _('vpchairman')),
  // (5, _('director')),
  // (4, _('vpdirector')),
  // (3, _('boardmember')),
  // (2, _('execmember')),
  // (1, _('votingmember')),
  // (0, _('assocmember')),
  bool is_accepted;
  bool is_initial;
  bool is_minimum;
  bool is_voting;

 uint64_t primary_key() const {
    return username.value;
 } /*!< return username - primary_key */

  uint64_t bylastpay() const {
    return last_min_pay.sec_since_epoch();
  }

};

typedef eosio::multi_index< "members"_n, members,
  eosio::indexed_by<"bylastpay"_n, eosio::const_mem_fun<members, uint64_t, &members::bylastpay>>
> members_index;


struct [[eosio::table, eosio::contract(SOVIET)]] decisions {
  uint64_t id;
  eosio::name coop_username;
  eosio::name type; // openproposal | +regaccount | change | contribute | withdraw
  uint64_t card_id;

  std::vector<eosio::name> votes_for;
  std::vector<eosio::name> votes_against;
  
  bool approved = false;   //сигнальный флаг, что решение советом принято
  bool validated = false;   //сигнальный флаг, что администратор подтверждает валидность
  bool authorized = false; //получена авторизация председателя после голосования и валидации до исполнения
  bool certified = false; //получено сертификация секретаря;
  bool executed = false;   //исполнять будем отдельным действием для торжественности момента

  uint64_t primary_key() const { return id; }
  uint64_t by_coop() const {return coop_username.value;} 
  uint64_t by_card() const { return card_id; }
  uint64_t bytype() const { return type.value; }

  uint64_t byapproved() const { return approved; }
  uint64_t byvalidated() const { return validated; }
  uint64_t byauthorized() const { return authorized; }
  uint64_t bycertified() const { return certified;}
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

