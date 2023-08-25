using namespace eosio;
/**
 * @brief Добавление баланса пользователю.
 *
 * Этот метод вызывается при прямом входящем переводе токенов на контракт. Добавляет указанное количество токенов к балансу пользователя.
 *
 * @param username Имя пользователя, чей баланс нужно увеличить.
 * @param quantity Количество токенов, которое нужно добавить.
 * @param contract Учетная запись контракта токена.
 */
void marketplace::add_balance(eosio::name username, eosio::asset quantity,
                              eosio::name contract) {
  // Если баланс не найден, создаем новую запись.
  // В противном случае, увеличиваем существующий баланс.
  
  require_auth(username);

  balances_index balances(_me, username.value);

  auto balances_by_contract_and_symbol =
      balances.template get_index<"byconsym"_n>();
  auto contract_and_symbol_index =
      combine_ids(contract.value, quantity.symbol.code().raw());

  auto balance =
      balances_by_contract_and_symbol.find(contract_and_symbol_index);

  if (balance == balances_by_contract_and_symbol.end()) {
    balances.emplace(_me, [&](auto &b) {
      b.id = balances.available_primary_key();
      b.contract = contract;
      b.quantity = quantity;
    });
  } else {
    balances_by_contract_and_symbol.modify(
        balance, _me, [&](auto &b) { b.quantity += quantity; });
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
void marketplace::sub_balance(eosio::name username, eosio::asset quantity,
                              eosio::name contract) {
  // Если после вычитания баланс равен нулю, удаляем запись.
  // В противном случае, уменьшаем существующий баланс.
  
  balances_index balances(_me, username.value);

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
        balance, _me, [&](auto &b) { b.quantity -= quantity; });
  }
}
