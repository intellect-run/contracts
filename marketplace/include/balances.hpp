using namespace eosio;

/**
 * @brief Таблица балансов для контракта "marketplace"
 *
 * Эта таблица используется для хранения информации о балансах пользователей в системе.
 *
 * @param id Идентификатор баланса, используемый как первичный ключ
 * @param contract Имя контракта токена
 * @param quantity Количество токенов на балансе
 *
 * Дополнительный индекс по комбинации contract и symbol позволяет искать баланс по этим двум полям.
 *
 * Пример использования:
 * @code
 * balances_index balances(_me, username.value);
 * auto balance = balances.find(id);
 * @endcode
 */
struct [[eosio::table, eosio::contract("marketplace")]] balance {
  uint64_t id;          /*!< идентификатор баланса */
  eosio::name contract; /*!< имя контракта токена */
  eosio::asset quantity; /*!< количество токенов на балансе */

  uint64_t primary_key() const { return id; } /*!< return id - primary_key */

  uint128_t byconsym() const {
    return combine_ids(contract.value, quantity.symbol.code().raw());
  } /*!< возвращает уникальный индекс, сформированный из значения contract и символа токена */
};

typedef eosio::multi_index<"balance"_n, balance, eosio::indexed_by<"byconsym"_n, eosio::const_mem_fun<balance, uint128_t, &balance::byconsym>>> balances_index; /*!< Тип мультииндекса для таблицы балансов */
