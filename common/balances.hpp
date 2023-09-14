/**
\ingroup public_tables
\brief Структура таблицы баланса.

@details Структура, представляющая записи баланса в контрактах. Используется при отправке токенов в контракты _marketplace или _registrator.

@note Таблица хранится в области памяти пользователя (_registrator | _marketplace, username)
*/
struct balances_base {
  uint64_t id;          /*!< идентификатор баланса */
  eosio::name contract; /*!< имя контракта токена */
  eosio::asset quantity; /*!< количество токенов на балансе */

  uint64_t primary_key() const { return id; } /*!< return id - primary_key */

  uint128_t byconsym() const {
    return combine_ids(contract.value, quantity.symbol.code().raw());
  } /*!< возвращает уникальный индекс, сформированный из значения contract и символа токена */
};

typedef eosio::multi_index<"balances"_n, balances_base, eosio::indexed_by<"byconsym"_n, eosio::const_mem_fun<balances_base, uint128_t, &balances_base::byconsym>>> balances_index; /*!< Тип мультииндекса для таблицы балансов */



void add_balance(eosio::name source, eosio::name username, eosio::asset quantity,
                                  eosio::name contract) {
  // Если баланс не найден, создаем новую запись.
  // В противном случае, увеличиваем существующий баланс.

  
  eosio::check(username != ""_n, "В поле memo должен быть указан получатель баланса");
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
