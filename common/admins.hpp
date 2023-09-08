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

struct [[eosio::table, eosio::contract("soviet")]] admins {
  eosio::name username; ///< Уникальное имя администратора
  std::vector<eosio::name> rights; ///< Список прав администратора
  std::string meta; ///< Дополнительная информация об администраторе
  
  uint64_t primary_key() const { return username.value; } ///< Первичный ключ для индексации по имени администратора
};

typedef eosio::multi_index<"admins"_n, admins> admins_index; ///< Тип мультииндекса для таблицы администраторов
