using namespace eosio;

//Метод вызывается администратором для принятия модерации заявки
[[eosio::action]] void marketplace::moderate(eosio::name username, uint64_t exchange_id) { 
  require_auth(username);
  
  exchange_index exchange(_marketplace, _marketplace.value);
  
  auto change = exchange.find(exchange_id);
  eosio::check(change != exchange.end(), "Ордер не найден");

  if (change -> status == "moderation"_n) {
    admins_index admins(_soviet, _soviet.value);
    auto admin = admins.find(username.value);
    eosio::check(admin != admins.end(), "У вас нет прав администратора");

    exchange.modify(change, username, [&](auto &o){
      o.status = "published"_n;
    });
  }
};


//Метод вызывается администратором для отказа в прохождении модерации заявки
[[eosio::action]] void marketplace::prohibit(eosio::name username, uint64_t exchange_id, std::string meta) { 
  require_auth(username);
  
  exchange_index exchange(_marketplace, _marketplace.value);
  auto change = exchange.find(exchange_id);
  eosio::check(change != exchange.end(), "Ордер не найден");

  admins_index admins(_soviet, _soviet.value);
  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "У вас нет прав администратора");

  exchange.modify(change, username, [&](auto &o){
    o.status = "prohibit"_n;
    o.meta = meta;
  });
  
};


/**
 * @brief Снять заявку с публикации
 * @param username Имя пользователя, являющегося владельцем заявки
 * @param exchange_id Идентификатор заявки, которую следует снять с публикации
 * 
 * Этот метод может быть вызван только владельцем заявки. Он изменяет статус заявки на "unpublished".
 */
[[eosio::action]] void marketplace::unpublish(eosio::name username, uint64_t exchange_id) { 
  require_auth(username);
  
  exchange_index exchange(_marketplace, _marketplace.value);
  auto change = exchange.find(exchange_id);
  eosio::check(change != exchange.end(), "Ордер не найден");
  eosio::check(change->username == username, "У вас нет права на снятие данной заявки");

  exchange.modify(change, username, [&](auto &o){
    o.status = "unpublished"_n;
  });
};


/**
 * @brief Опубликовать заявку
 * @param username Имя пользователя, являющегося владельцем заявки
 * @param exchange_id Идентификатор заявки, которую следует опубликовать
 * 
 * Этот метод может быть вызван только владельцем заявки и только в случае, если заявка находится в статусе "unpublished".
 * Он изменяет статус заявки на "published".
 */
[[eosio::action]] void marketplace::publish(eosio::name username, uint64_t exchange_id) { 
  require_auth(username);
  
  exchange_index exchange(_marketplace, _marketplace.value);
  auto change = exchange.find(exchange_id);
  eosio::check(change != exchange.end(), "Ордер не найден");
  eosio::check(change->username == username, "У вас нет права на публикацию данной заявки");
  eosio::check(change->status == "unpublished"_n, "Неверный статус для публикации");

  exchange.modify(change, username, [&](auto &o){
    o.status = "published"_n;
  });
}