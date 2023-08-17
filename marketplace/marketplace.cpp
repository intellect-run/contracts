#include "marketplace.hpp"
#include <eosio/transaction.hpp>

using namespace eosio;

void marketplace::add_balance(eosio::name username, eosio::asset quantity,
                              eosio::name contract) {
  require_auth(username);

  ubalances_index ubalances(_me, username.value);

  auto balances_by_contract_and_symbol =
      ubalances.template get_index<"byconsym"_n>();
  auto contract_and_symbol_index =
      combine_ids(contract.value, quantity.symbol.code().raw());

  auto balance =
      balances_by_contract_and_symbol.find(contract_and_symbol_index);

  if (balance == balances_by_contract_and_symbol.end()) {
    ubalances.emplace(_me, [&](auto &b) {
      b.id = ubalances.available_primary_key();
      b.contract = contract;
      b.quantity = quantity;
    });
  } else {
    balances_by_contract_and_symbol.modify(
        balance, _me, [&](auto &b) { b.quantity += quantity; });
  };
}

void marketplace::sub_balance(eosio::name username, eosio::asset quantity,
                              eosio::name contract) {
  ubalances_index ubalances(_me, username.value);

  auto balances_by_contract_and_symbol =
      ubalances.template get_index<"byconsym"_n>();
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

//метод вызывается поставщиком товара
[[eosio::action]] void marketplace::create(eosio::name creator,
                                           eosio::name category,
                                           eosio::name contract,
                                           uint64_t total_pieces,
                                           eosio::asset price_for_piece,
                                           std::string data) {
  require_auth(creator);
  items_index items(_me, _me.value);
  
  uint64_t id = marketplace::get_global_id("items"_n);

  items.emplace(creator, [&](auto &i) {
    i.id = id;
    i.creator = creator;
    i.category = category;
    i.status = "moderation"_n;
    i.contract = contract;
    i.total_pieces = total_pieces;
    i.blocked_pieces = 0;
    i.delivered_pieces = 0;
    i.price_for_piece = price_for_piece;
    i.data = data;
  });

  action(
    permission_level{ _me, "active"_n},
    _me,
    "newitem"_n,
    std::make_tuple(id)
  ).send();

};

//пустой метод регистрации нового идентификатора, используется для возврата информации
[[eosio::action]] void marketplace::newitem(uint64_t id) {};



//метод вызывается советом после авторизации обмена
[[eosio::action]] void marketplace::authorize(uint64_t order_id) {
  require_auth(_soviet);

  orders_index orders(_me, _me.value);
  auto order = orders.find(order_id);

  eosio::check(order != orders.end(), "Ордер не найден");
  
  orders.modify(order, _soviet, [&](auto &o) { 
    o.status = "authorized"_n; 
  });

};


//метод вызывается заказчиком товара
[[eosio::action]] void marketplace::order(eosio::name requester, uint64_t item_id,
                                          std::string meta) {
  require_auth(requester);

  items_index items(_me, _me.value);
  auto item = items.find(item_id);
  eosio::check(item != items.end(), "Объект не найден");

  marketplace::sub_balance(requester, item->price_for_piece, item->contract);
  
  orders_index orders(_me, _me.value);
  uint64_t order_id = marketplace::get_global_id("orders"_n);

  orders.emplace(requester, [&](auto &i){
    i.id = order_id;
    i.item_id = item_id;
    i.requester = requester;
    i.status = "waiting"_n;
    i.meta = meta;
    i.price_for_piece = item -> price_for_piece;
    i.contract = item -> contract;
  });

}


//метод вызывается поставщиков для подтверждения готовности поставить товар
[[eosio::action]] void marketplace::approve(eosio::name username, uint64_t order_id) { 
  require_auth(username);
  admin_index admins(_me, _soviet.value);
  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "У вас нет прав администратора");

  orders_index orders(_me, _me.value);
  auto order = orders.find(order_id);
  eosio::check(order != orders.end(), "Ордер не найден");
  eosio::check(order -> status == "waiting"_n, "Только ордер в статусе ожидания может быть одобрен");

  orders.modify(order, username, [&](auto &o){
    o.status = "approved"_n;
  });
  
  items_index items(_me, _me.value);
  auto item = items.find(order -> item_id);
  eosio::check(item != items.end(), "Объект поставки не найден");
  
  items.modify(item, username, [&](auto &i){
    i.blocked_pieces += 1;
  });

  action(
    permission_level{ _me, "active"_n},
    _soviet,
    "change"_n,
    std::make_tuple(order_id)
  ).send();
}


//метод вызывается администратором для отказа готовности поставщика совершить поставку
[[eosio::action]] void marketplace::decline(eosio::name username, uint64_t order_id, std::string meta) { 
  require_auth(username);

  admin_index admins(_me, _soviet.value);
  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "У вас нет прав администратора");

  orders_index orders(_me, _me.value);
  auto order = orders.find(order_id);

  eosio::check(order != orders.end(), "Ордер не найден");
  eosio::check(order -> status == "waiting"_n, "Только ордер в статусе ожидания может быть отменен");

  orders.modify(order, username, [&](auto &o){
    o.status = "declined"_n;
    o.meta = meta;
  });

  //TODO перевод токенов на аккаунт поставщика
  action(
      permission_level{ _me, "active"_n },
      order -> contract, "transfer"_n,
      std::make_tuple( _me, order -> requester, order -> price_for_piece, std::string("Возврат по ордеру: ", order_id)) 
  ).send();
  
}





//Метод вызывается заказчиком при получении товара
[[eosio::action]] void marketplace::confirm(eosio::name username, uint64_t order_id) { 
  require_auth(username);
  
  orders_index orders(_me, _me.value);
  auto order = orders.find(order_id);
  eosio::check(order != orders.end(), "Ордер не найден");
  eosio::check(order -> requester == username, "Вы не можете подтвердить получение товара по ордеру, так как не вы являетесь заказчиком");
  eosio::check(order -> status == "authorized"_n, "Ордер находится в неверном статусе: или уже выдан, или обмен еще не одобрен советом");

  orders.modify(order, username, [&](auto &o){
    o.status = "confirmed"_n;
  });

  items_index items(_me, _me.value);
  auto item = items.find(order -> item_id);

  eosio::check(item != items.end(), "Объект не найден");
  
  items.modify(item, username, [&](auto &i){
    i.total_pieces -= 1;
    i.blocked_pieces -= 1;
  });

  //TODO перевод токенов на аккаунт поставщика
  action(
      permission_level{ _me, "active"_n },
      order -> contract, "transfer"_n,
      std::make_tuple( _me, item -> creator, order -> price_for_piece, std::string("Возврат по ордеру: ", order_id)) 
  ).send();
  
}


extern "C" {

/// The apply method implements the dispatch of events to this contract
void apply(uint64_t receiver, uint64_t code, uint64_t action) {
  if (code == _me.value) {
    switch (action) {
      EOSIO_DISPATCH_HELPER(marketplace, (create)(order)(authorize)(confirm)(decline)(approve)(newitem))
    }
  } else {
    if (action == "transfer"_n.value) {
      struct transfer {
        eosio::name from;
        eosio::name to;
        eosio::asset quantity;
        std::string memo;
      };

      auto op = eosio::unpack_action_data<transfer>();

      if (op.to == _me) {
        marketplace::add_balance(op.from, op.quantity, eosio::name(code));
      }
    }
  }
};
};
