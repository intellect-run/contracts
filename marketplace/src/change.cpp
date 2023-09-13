using namespace eosio;

/**
 * @mainpage Описание системы заявок
 *
 * В системе имеются два типа заявок: order (заказ) и offer (предложение), а также два уровня заявок: родительская (base) и встречная (quote).
 * Используется одна таблица заявок: exchange(_marketplace, _marketplace). Встречная заявка всегда должна быть противополжного типа к родительской.
 *
 * <b>Группы заявок:</b>
 * 
 * <b>1. Группа предложений от родителя:</b>
 * - Parent: type == 'offer' && (parent_id == 0) => имущественный паевый взнос
 * - Child: type == 'order' && (parent_id > 0) => денежный паевый взнос
 *
 * <b>2. Группа заказа от родителя:</b>
 * - Parent: type == "order" && (parent_id == 0) => денежный паевый взнос
 * - Child: type == "offer" && (parent_id > 0) => имущественный паевый взнос
 *
 * <b>Обозначения:</b>
 * - order => денежный паевый взнос
 * - offer => имущественный паевый взнос
 */


/**
 * @brief Совершение денежного паевого взноса
 * 
 * @param params Параметры заказа
 * 
 * Данная функция используется для создания заявки на денежный паевой взнос.
 */
[[eosio::action]] void marketplace::order (const exchange_params& params) {
  require_auth(params.username);

  marketplace::create("order"_n, params);

};


/**
 * @brief Совершение имущественного паевого взноса
 * 
 * @param params Параметры предложения
 * 
 * Данная функция используется для создания заявки на имущественный паевой взнос.
 */
[[eosio::action]] void marketplace::offer (const exchange_params& params) {
  require_auth(params.username);

  marketplace::create("offer"_n, params);
  
};



/**
 * @brief Создание заявки на обмен
 * 
 * @param type Тип заявки
 * @param params Параметры заявки
 * 
 * Общая функция для создания как родительских, так и дочерних заявок.
 */
void marketplace::create (eosio::name type, const exchange_params& params) {
  orgs_index orgs(_registrator, _registrator.value);
  auto org = orgs.find(params.coop_username.value);
  eosio::check(org != orgs.end() && org -> is_coop(), "Кооператив не найден");

  eosio::check(params.contract == _root_contract, "Неверный тип контракта");
  eosio::check(params.price_for_piece.symbol == _root_symbol, "Неверный символ токен");
  eosio::check(params.pieces > 0, "Количество единиц в заявке должно быть больше нуля");
  eosio::check(params.price_for_piece.amount >= 0, "Цена не может быть отрицательной");

  if (params.parent_id == 0) {
    marketplace::create_parent_order(type, params);
  } else {
    marketplace::create_child_order(type, params);
  };
};


/**
 * @brief Создание родительской заявки
 * 
 * @param type Тип заявки
 * @param params Параметры заявки
 * 
 * Специализированная функция для создания родительской заявки.
 */
void marketplace::create_parent_order(eosio::name type, const exchange_params& params) {
  exchange_index exchange(_marketplace, _marketplace.value);
  
  uint64_t id = get_global_id(_marketplace, "exchange"_n);
  
  eosio::check(params.parent_id == 0, "Родительская заявка создаётся без указания родителя");

  //Специальные проверки
  if (type == "offer"_n) {

  } else if(type == "order"_n) {
    eosio::asset quantity = params.price_for_piece * params.pieces;
    sub_balance(_marketplace, params.username, quantity, params.contract);
  }

  exchange.emplace(params.username, [&](auto &i) {
    i.id = id;
    i.type = type; 
    i.username = params.username;
    i.status = "moderation"_n;
    i.contract = params.contract;
    i.remain_pieces = params.pieces;
    i.price_for_piece = params.price_for_piece;
    i.data = params.data;
    i.meta = params.meta;
  });

  action(
    permission_level{ _marketplace, "active"_n},
    _marketplace,
    "newid"_n,
    std::make_tuple(id, type)
  ).send();

};



/**
 * @brief Создание дочерней заявки
 * 
 * @param type Тип заявки
 * @param params Параметры заявки
 * 
 * Специализированная функция для создания дочерних заявок, связанных с родительской заявкой.
 */
void marketplace::create_child_order(eosio::name type, const exchange_params& params) {
  exchange_index exchange(_marketplace, _marketplace.value);
  auto parent_change = exchange.find(params.parent_id);
  eosio::check(parent_change != exchange.end(), "Заявка не обнаружена");
  eosio::check(parent_change -> status == "published"_n, "Заявка не опубликована");

  eosio::check(parent_change -> contract == params.contract, "Неверный контракт");
  eosio::check(parent_change -> price_for_piece.amount == params.price_for_piece.amount, "Торги запрещены");
  eosio::check(params.parent_id > 0, "Встречная заявка создаётся с указанием родителя");
  
  //Специальные проверки
  if (type == "offer"_n) {
    //родительская заявка должна быть противоположного типа
    eosio::check(parent_change -> type == "order"_n, "Неверный тип родительской заявки");

  } else if(type == "order"_n) {
    //родительская заявка должна быть противоположного типа
    eosio::check(parent_change -> type == "offer"_n, "Неверный тип родительской заявки");
    eosio::asset quantity = params.price_for_piece * params.pieces;
    sub_balance(_marketplace, params.username, quantity, parent_change -> contract);
  }

  uint64_t id = get_global_id(_marketplace, "exchange"_n);
  exchange.emplace(params.username, [&](auto &i) {
    i.id = id;
    i.parent_id = params.parent_id;
    i.type = type; 
    i.username = params.username;
    i.parent_id = params.parent_id;
    i.status = "published"_n;
    i.contract = params.contract;
    i.remain_pieces = params.pieces;
    i.price_for_piece = params.price_for_piece;
    i.data = params.data;
  });

  action(
    permission_level{ _marketplace, "active"_n},
    _marketplace,
    "newid"_n,
    std::make_tuple(id, type)
  ).send();

};



/**
 * @brief Принятие дочерней заявки родительским пользователем.
 * 
 * Этот метод вызывается владельцем родительской заявки для подтверждения готовности выполнить дочернюю заявку.
 * Выполняются следующие проверки:
 * - Наличие заявки с указанным ID.
 * - Заявка находится в статусе "опубликовано".
 * - Наличие родительской заявки и соответствие ее владельцу.
 * - Наличие достаточного количества объектов для поставки.
 * 
 * @param username Имя пользователя-владельца родительской заявки.
 * @param exchange_id ID дочерней заявки, которую нужно принять.
 */
[[eosio::action]] void marketplace::accept(eosio::name username, uint64_t exchange_id) { 
  require_auth(username);
 
  //TODO проверка на членство
  exchange_index exchange(_marketplace, _marketplace.value);
  auto change = exchange.find(exchange_id);
  eosio::check(change != exchange.end(), "Заявка не найдена");
  eosio::check(change -> status == "published"_n, "Только заявка в статусе ожидания может быть принята");

  auto parent_change = exchange.find(change -> parent_id);
  eosio::check(parent_change != exchange.end(), "Родительская заявка не найдена");
  eosio::check(parent_change -> username == username, "Недостаточно прав доступа");
  eosio::check(parent_change -> remain_pieces >= change -> remain_pieces, "Недостаточно объектов для поставки");
  
  exchange.modify(parent_change, username, [&](auto &i) {
    i.remain_pieces -= change -> remain_pieces;
    i.blocked_pieces += change -> remain_pieces;
  });

  exchange.modify(change, username, [&](auto &o){
    o.status = "accepted"_n;
    o.blocked_pieces += change -> remain_pieces;
    o.remain_pieces = 0;
  });
    
  action(
    permission_level{ _marketplace, "active"_n},
    _soviet,
    "change"_n,
    std::make_tuple(change -> coop_username, exchange_id)
  ).send();

}


/**
 * @brief Отказ в готовности исполнить дочернюю заявку.
 * 
 * Этот метод вызывается владельцем родительской заявки для отказа в готовности выполнить дочернюю заявку.
 * Выполняются следующие проверки:
 * - Наличие заявки с указанным ID.
 * - Наличие родительской заявки.
 * - Заявка находится в статусе "ожидание".
 * 
 * В случае отказа в выполнении заявки типа "order", производится возврат токенов поставщику заказа, 
 * которому ранее была выполнена блокировка токенов.
 * 
 * @param username Имя пользователя-владельца родительской заявки.
 * @param exchange_id ID дочерней заявки, которую нужно отклонить.
 * @param meta Дополнительные метаданные, ассоциированные с отклонением.
 */
[[eosio::action]] void marketplace::decline(eosio::name username, uint64_t exchange_id, std::string meta) { 
  require_auth(username);

  exchange_index exchange(_marketplace, _marketplace.value);
  auto change = exchange.find(exchange_id);
  auto parent_change = exchange.find(change -> parent_id);

  eosio::check(change != exchange.end(), "Заявка не найдена");
  eosio::check(parent_change != exchange.end(), "Родительская заявка не найдена");
  eosio::check(change -> status == "waiting"_n, "Только заявка в статусе ожидания может быть отклонена");

  exchange.modify(change, username, [&](auto &o){
    o.status = "declined"_n;
    o.meta = meta;
  });

  if (change -> type == "order"_n) {
    //возврат токенов производится только поставщику заказа, которому ранее сделали блокировку токенов
    action(
      permission_level{ _marketplace, "active"_n },
      change -> contract, "transfer"_n,
      std::make_tuple( _marketplace, change -> username, change -> price_for_piece, std::string("Возврат по заявке: " + std::to_string(exchange_id))) 
    ).send();
  }; 
  
}


/**
 * @brief Завершение дочерней заявки получателем товара.
 *
 * Этот метод вызывается получателем при получении товара с указанием дочерней заявки, что обозначает успешное исполнение сделки.
 * Выполняются следующие проверки:
 * - Наличие заявки с указанным ID.
 * - Наличие родительской заявки.
 * - Пользователь является владельцем указанной заявки.
 * - Заявка находится в статусе "authorized".
 *
 * После успешных проверок обновляются статусы и количество блокированных и поставленных объектов в родительской и дочерней заявках.
 * В случае, если блокированные и оставшиеся объекты равны нулю, родительская заявка снимается с публикации.
 * Если есть необходимость в переводе токенов, он выполняется в зависимости от типа заявки.
 *
 * @note Акт может подписать только получатель товара, и подписание акта должно производиться всегда на дочерней заявке.
 *
 * @param username Имя пользователя-получателя товара.
 * @param exchange_id ID дочерней заявки, которую нужно завершить.
 */
[[eosio::action]] void marketplace::complete(eosio::name username, uint64_t exchange_id) { 
  require_auth(username);
  
  exchange_index exchange(_marketplace, _marketplace.value);
  auto change = exchange.find(exchange_id);
  eosio::check(change != exchange.end(), "Заявка не найдена");
  
  eosio::check(change -> parent_id > 0, "У указанной заявки нет встречной заявки");

  auto parent_change = exchange.find(change -> parent_id);
  eosio::check(parent_change != exchange.end(), "Родительская заявка не найдена");
  
  //TODO!! CHANGE IT! => 
  eosio::check(change -> username == username, "Вы не можете подтвердить исполнение заявки");
  eosio::check(change -> status == "authorized"_n, "Заявка находится в неверном статусе для утверждения обмена");
  
  eosio::asset quantity = change -> price_for_piece * change -> blocked_pieces;

  exchange.modify(parent_change, username, [&](auto &i) {
    i.delivered_pieces += change -> blocked_pieces;
    i.blocked_pieces -= change -> blocked_pieces; 
    
    //TODO надо тестировать
    if (i.blocked_pieces + parent_change -> remain_pieces == 0) {
      i.status = "unpublished"_n; //снимаем родительскую заявку с публикации, если она исполнена
    }; 
  });

  exchange.modify(change, username, [&](auto &o) {
    o.status = "completed"_n;
    o.delivered_pieces += change -> blocked_pieces;
    o.blocked_pieces = 0;
  });

  /*
   * Акт может подписать только получатель товара. Подписание акта должно производиться всегда
   * на дочерней заявке. Проверить и покрыть тестами в обе стороны.
   *
   */

  //TODO test it
  if (quantity.amount > 0) {
    //определяем направление перевода
    if (change -> type == "order"_n) { //дочерняя заявка на получение товара
      //значит родитель - это offer, который ожидает перевода токенов в счёт оплаты
      action(
          permission_level{ _marketplace, "active"_n },
          change -> contract, "transfer"_n,
          std::make_tuple( _marketplace, parent_change -> username, quantity, std::string("Возврат по заявке: " + std::to_string(exchange_id))) 
      ).send();

    } else if (change -> type == "offer"_n) { //дочерняя заявка на поставку товара
      //значит родитель - это order, а перевод ожидает владелец дочерней заявки
      action(
          permission_level{ _marketplace, "active"_n },
          change -> contract, "transfer"_n,
          std::make_tuple( _marketplace, change -> username, quantity, std::string("Возврат по заявке: " + std::to_string(exchange_id))) 
      ).send();
    }
  }
}


/**
 * @brief Отмена заявки получателем и возврат токенов владельцу.
 *
 * Этот метод отвечает за отмену дочерней или родительской заявки в зависимости от контекста.
 * Выполняются следующие проверки:
 * - Наличие заявки с указанным ID.
 * - Статус заявки не должен быть "accepted".
 *
 * В зависимости от наличия родительской заявки вызываются методы `cancel_parent_order` или `cancel_child_order`.
 *
 * @param username Имя пользователя, осуществляющего отмену заявки.
 * @param exchange_id ID заявки, которую нужно отменить.
 */
[[eosio::action]] void marketplace::cancel(eosio::name username, uint64_t exchange_id) { 
  require_auth(username);
  
  exchange_index exchange(_marketplace, _marketplace.value);
  auto change = exchange.find(exchange_id);
  eosio::check(change != exchange.end(), "Заявка не найдена");
  eosio::check(change -> status != "accepted"_n, "Заявка не может быть отменена сейчас");

  if (change -> parent_id == 0) {
    marketplace::cancel_parent_order(username, exchange_id);
  } else {
    marketplace::cancel_child_order(username, exchange_id);
  };
}

/**
 * @brief Отмена родительской заявки.
 *
 * Вызывается из `cancel`, если заявка является родительской.
 * Выполняется проверка, что заявка не имеет заблокированных единиц товара, и удаляется из хранилища.
 *
 * @param username Имя пользователя, осуществляющего отмену заявки.
 * @param exchange_id ID родительской заявки, которую нужно отменить.
 */
void marketplace::cancel_parent_order(eosio::name username, uint64_t exchange_id) {
  exchange_index exchange(_marketplace, _marketplace.value);
  auto change = exchange.find(exchange_id);

  //Удаление, если заблокированных объектов на поставке - нет.   
  eosio::check(change -> remain_pieces + change -> blocked_pieces == 0, "Заявка не может быть удалена из-за наличия заблокированных единиц товара");
  exchange.erase(change);
};

/**
 * @brief Отмена дочерней заявки.
 *
 * Вызывается из `cancel`, если заявка является дочерней.
 * Обновляет количество оставшихся и заблокированных единиц товара в родительской заявке и удаляет дочернюю заявку из хранилища.
 * В зависимости от статуса и типа заявки возможен возврат токенов "покупателю".
 *
 * @param username Имя пользователя, осуществляющего отмену заявки.
 * @param exchange_id ID дочерней заявки, которую нужно отменить.
 */
void marketplace::cancel_child_order(eosio::name username, uint64_t exchange_id) {
  exchange_index exchange(_marketplace, _marketplace.value);
  auto change = exchange.find(exchange_id);
  auto parent_change = exchange.find(change -> parent_id);
  eosio::asset quantity = change -> price_for_piece * change -> blocked_pieces;

  if (change -> status == "authorized"_n) {
    //возвращаем единицы товара в родительскую заявку
    exchange.modify(parent_change, username, [&](auto &e) {
      e.remain_pieces += change -> blocked_pieces;
      e.blocked_pieces -= change -> blocked_pieces;
    });

    //удаляем дочернюю заявку
    exchange.erase(change);

  } else if (change -> status == "published"_n) {
    
    //удаляем дочернюю заявку
    exchange.erase(change);

  } else {

    eosio::check(false, "Заявка находится в недопустимом статусе для отмены");

  }

  // возврат токенов "покупателю"
  if (change -> type == "order"_n && quantity.amount > 0) {
    action(
        permission_level{ _marketplace, "active"_n },
        change -> contract, "transfer"_n,
        std::make_tuple( _marketplace, change -> username, quantity, std::string("Возврат по заявке: " + std::to_string(exchange_id))) 
    ).send();
  }  
}

/**
 * @brief Обновление заявки.
 *
 * Этот метод позволяет владельцу заявки обновить некоторые свойства заявки на обмен.
 * Выполняются следующие проверки:
 * - Заявка с указанным ID существует.
 * - Валюта заявки соответствует ожидаемой.
 * - Заявка не является дочерней (встречной).
 * - Пользователь имеет право на изменение этой заявки.
 *
 * @param username Имя пользователя, обновляющего заявку.
 * @param exchange_id ID заявки, которую нужно обновить.
 * @param price_for_piece Новая цена за единицу товара.
 * @param data Новые данные заявки.
 * @param meta Новые метаданные заявки.
 */
[[eosio::action]] void marketplace::update(eosio::name username, uint64_t exchange_id, eosio::asset price_for_piece, std::string data, std::string meta) {
  require_auth(username);

  exchange_index exchange(_marketplace, _marketplace.value);
  auto change = exchange.find(exchange_id);
  eosio::check(change != exchange.end(), "Заявка на обмен не найдена");
  eosio::check(price_for_piece.symbol == _root_symbol, "Неверный символ токен");
  eosio::check(change -> parent_id == 0, "Встречные заявки можно только отменять");
  eosio::check(change -> username == username, "У вас нет права на отмену данной заявки");

  exchange.modify(change, username, [&](auto &i) {
    i.status = "moderation"_n;
    i.price_for_piece = price_for_piece;
    i.data = data;
    i.meta = meta;
  });
}


/**
 * @brief Добавление единиц товара к заявке на обмен.
 *
 * Этот метод позволяет владельцу заявки увеличить количество доступных для обмена единиц товара в заявке.
 * Выполняются следующие проверки:
 * - Пользователь имеет право на изменение этой заявки.
 * - Заявка не является дочерней (встречной).
 *
 * @param username Имя пользователя, добавляющего единицы товара.
 * @param exchange_id ID заявки, к которой нужно добавить единицы товара.
 * @param new_pieces Количество новых единиц товара для добавления.
 */
[[eosio::action]] void marketplace::addpieces(eosio::name username, uint64_t exchange_id, uint64_t new_pieces) {
  require_auth(username);
    
  exchange_index exchange(_marketplace, _marketplace.value);
  auto change = exchange.find(exchange_id);
  
  eosio::check(change -> username == username, "У вас нет прав на редактирование данной заявки");
  eosio::check(change -> parent_id == 0, "Нельзя отредактировать количество единиц во встречной заявке. Отмените её и пересоздайте");

  exchange.modify(change, username, [&](auto &c){
    c.remain_pieces += new_pieces;
  });
  
};


