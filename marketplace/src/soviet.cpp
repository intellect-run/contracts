using namespace eosio;

/**
 * @brief Авторизация обмена советом.
 *
 * Этот метод позволяет совету изменить статус заявки на обмен на "авторизованный".
 * Выполняются следующие проверки:
 * - Заявка с указанным ID существует.
 *
 * Этот метод вызывается советом и может быть использован только им. Авторизация необходима
 * для завершения обмена.
 *
 * @param exchange_id ID заявки, которую нужно авторизовать.
 */

[[eosio::action]] void marketplace::authorize(uint64_t exchange_id) {
  require_auth(_soviet);

  exchange_index exchange(_marketplace, _marketplace.value);
  auto change = exchange.find(exchange_id);

  eosio::check(change != exchange.end(), "Ордер не найден");
  
  exchange.modify(change, _soviet, [&](auto &o) { 
    o.status = "authorized"_n; 
  });

};