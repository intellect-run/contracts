#pragma once

struct [[eosio::table, eosio::contract(REGISTRATOR)]] members {
  eosio::name username;
  eosio::time_point_sec created_at;
  eosio::time_point_sec last_update;
  bool is_accepted;
  bool is_initial;
  bool is_minimum;
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

 uint64_t primary_key() const {
    return username.value;
 } /*!< return username - primary_key */

};

typedef eosio::multi_index< "members"_n, members> members_index;


struct [[eosio::table, eosio::contract(SOVIET)]] documents {
  uint64_t id;
  uint64_t board_id;
  eosio::name type; // openproposal | +regaccount | change | contribute | withdraw
  uint64_t secondary_id;

  std::vector<eosio::name> votes_for;
  std::vector<eosio::name> votes_against;
  
  bool approved = false;   //сигнальный флаг, что решение советом принято
  bool validated = false;   //сигнальный флаг, что администратор подтверждает валидность
  bool authorized = false; //получена авторизация председателя после голосования и валидации до исполнения
  bool executed = false;   //исполнять будем отдельным действием для торжественности момента

  uint64_t primary_key() const { return id; }
  
  uint64_t bysecondary() const { return secondary_id; }
  uint64_t bytype() const { return type.value; }

  uint64_t byapproved() const { return approved; }
  uint64_t byvalidated() const { return validated; }
  uint64_t byauthorized() const { return authorized; }
  uint64_t byexecuted() const { return executed; }
};

typedef eosio::multi_index< "documents"_n, documents,
  eosio::indexed_by<"bysecondary"_n, eosio::const_mem_fun<documents, uint64_t, &documents::bysecondary>>,
  eosio::indexed_by<"bytype"_n, eosio::const_mem_fun<documents, uint64_t, &documents::bytype>>,
  eosio::indexed_by<"byapproved"_n, eosio::const_mem_fun<documents, uint64_t, &documents::byapproved>>,
  eosio::indexed_by<"byvalidated"_n, eosio::const_mem_fun<documents, uint64_t, &documents::byvalidated>>,
  eosio::indexed_by<"byauthorized"_n, eosio::const_mem_fun<documents, uint64_t, &documents::byauthorized>>,
  eosio::indexed_by<"byexecuted"_n, eosio::const_mem_fun<documents, uint64_t, &documents::byexecuted>>
> documents_index;
 
struct [[eosio::table, eosio::contract(SOVIET)]] boards {
  uint64_t id;
  uint64_t parent_id;
  eosio::name chairman;
  std::vector<eosio::name> members;
  eosio::time_point_sec created_at;
  
  uint64_t primary_key() const { return id; }
  uint64_t bychairman() const { return chairman.value; }
      
};

typedef eosio::multi_index< "boards"_n, boards,
  eosio::indexed_by< "bychairman"_n, eosio::const_mem_fun<boards, uint64_t, &boards::bychairman>>
 > boards_index;


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

struct [[eosio::table, eosio::contract(SOVIET)]] staff {
  eosio::name username; ///< Уникальное имя администратора
  std::vector<eosio::name> rights; ///< Список прав администратора
  std::string meta; ///< Дополнительная информация об администраторе
  
  uint64_t primary_key() const { return username.value; } ///< Первичный ключ для индексации по имени администратора
};

typedef eosio::multi_index<"staff"_n, staff> staff_index; ///< Тип мультииндекса для таблицы администраторов
///
///
// struct [[eosio::table, eosio::contract(SOVIET)]] managers {
//   
// }; 
//
