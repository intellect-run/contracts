// В файле common_methods.hpp:
// using namespace eosio;


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
struct [[eosio::table, eosio::contract("marketplace")]] balances_base {
  uint64_t id;          /*!< идентификатор баланса */
  eosio::name contract; /*!< имя контракта токена */
  eosio::asset quantity; /*!< количество токенов на балансе */

  uint64_t primary_key() const { return id; } /*!< return id - primary_key */

  uint128_t byconsym() const {
    return combine_ids(contract.value, quantity.symbol.code().raw());
  } /*!< возвращает уникальный индекс, сформированный из значения contract и символа токена */
};

typedef eosio::multi_index<"balance"_n, balances_base, eosio::indexed_by<"byconsym"_n, eosio::const_mem_fun<balances_base, uint128_t, &balances_base::byconsym>>> balances_index; /*!< Тип мультииндекса для таблицы балансов */



void add_balance(eosio::name source, eosio::name username, eosio::asset quantity,
                                  eosio::name contract) {
  // Если баланс не найден, создаем новую запись.
  // В противном случае, увеличиваем существующий баланс.
  
  require_auth(username);

  balances_index balances(source, username.value);

  auto balances_by_contract_and_symbol =
      balances.template get_index<"byconsym"_n>();
  auto contract_and_symbol_index =
      combine_ids(contract.value, quantity.symbol.code().raw());

  auto balance =
      balances_by_contract_and_symbol.find(contract_and_symbol_index);

  if (balance == balances_by_contract_and_symbol.end()) {
    balances.emplace(source, [&](auto &b) {
      b.id = balances.available_primary_key();
      b.contract = contract;
      b.quantity = quantity;
    });
  } else {
    balances_by_contract_and_symbol.modify(
        balance, source, [&](auto &b) { b.quantity += quantity; });
  };
}


/**
 * @brief Вычитание баланса у пользователя.
 *
 * Этот метод вызывается в момент совершения order и вычитает указанное количество токенов из баланса пользователя.
 * Выполняются следующие проверки:
 * - Баланс с указанным контрактом и символом существует.
 * - Баланс достаточен для вычитания указанного количества.
 *
 * @param username Имя пользователя, чей баланс нужно уменьшить.
 * @param quantity Количество токенов, которое нужно вычесть.
 * @param contract Учетная запись контракта токена.
 */
void sub_balance(eosio::name source, eosio::name username, eosio::asset quantity,
                              eosio::name contract) {
  // Если после вычитания баланс равен нулю, удаляем запись.
  // В противном случае, уменьшаем существующий баланс.
  
  balances_index balances(source, username.value);

  auto balances_by_contract_and_symbol =
      balances.template get_index<"byconsym"_n>();
  auto contract_and_symbol_index =
      combine_ids(contract.value, quantity.symbol.code().raw());

  auto balance =
      balances_by_contract_and_symbol.find(contract_and_symbol_index);

  eosio::check(balance != balances_by_contract_and_symbol.end(),
               "Баланс не найден");

  eosio::check(balance->quantity >= quantity, "Недостаточный баланс");

  if (balance->quantity == quantity) {

    balances_by_contract_and_symbol.erase(balance);

  } else {

    balances_by_contract_and_symbol.modify(
        balance, source, [&](auto &b) { b.quantity -= quantity; });
  }
}
