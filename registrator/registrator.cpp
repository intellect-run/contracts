#include "registrator.hpp"
using namespace eosio;

/*
 * 1. Регистрация аккаунта в каталог через АНО с данными в хранилище АНО (Фио и
 * что что еще, наверное)
 * 2. Регистрация индивидуального лица через контракт регистратора с хранением
 * приватных данных где-то
 * 3. Оповещение АНО о изменении статуса аккаунта?
 */

[[eosio::action]] void registrator::newaccount(
    uint64_t coop_id, eosio::name registrator, eosio::name referer,
    eosio::name username, std::string nickname, eosio::public_key public_key,
    eosio::asset cpu, eosio::asset net, uint64_t ram_bytes, std::string meta) {
  require_auth(registrator);

  coops_index coops(_ano, _ano.value);
  auto coop = coops.find(coop_id);
  eosio::check(coop != coops.end(), "Кооператив не обнаружен");

  //активные разрешения
  authority active_auth;
  active_auth.threshold = 1;
  key_weight keypermission{public_key, 1};
  active_auth.keys.emplace_back(keypermission);

  authority owner_auth;
  auto ram_price = eosiosystem::determine_ram_price(ram_bytes);

  eosio::asset total_pay = cpu + net + ram_price;
  sub_balance(_registrator, registrator, total_pay, _root_contract);
  owner_auth.threshold = 1;
  eosio::permission_level permission(_registrator, eosio::name("eosio.code"));
  permission_level_weight accountpermission{permission, 1};
  owner_auth.accounts.emplace_back(accountpermission);

  action(permission_level(_registrator, "active"_n), "eosio"_n, "newaccount"_n,
         std::tuple(_registrator, username, owner_auth, active_auth))
      .send();

  action(permission_level{_registrator, "active"_n}, "eosio"_n, "buyram"_n,
         std::make_tuple(_registrator, username, ram_price))
      .send();

  action(permission_level{_registrator, "active"_n}, "eosio"_n, "delegatebw"_n,
         std::make_tuple(_registrator, username, net, cpu, true))
      .send();

  catalog_index catalog(_registrator, _registrator.value);
  auto card = catalog.find(username.value);

  eosio::check(card == catalog.end(), "account has been already registered");

  catalog.emplace(registrator, [&](auto &n) {
    n.username = username;
    n.coop_id = coop_id;
    n.registrator = registrator;
    n.payed = total_pay;
    n.referer = referer;
    n.nickname = nickname;
    n.nickhash = hashit(nickname);
    n.registered_at =
        eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
    n.meta = meta;
  });
}

/**
 * @brief      Метод регистрации индивидуального лица
 * @auth    registrator
 * @ingroup public_actions
 * @param[in]  registrator        имя аккаунта регистратора
 * @param[in]  referer      имя аккаунта реферера нового аккаунта (не
 обязательно, если set_referer = false)
 * @param[in]  newaccount   имя нового аккаунта
 * @param[in]  public_key   публичный ключ нового аккаунта
 * @param[in]  cpu          количество системного токена в CPU
 * @param[in]  net          количество системного токена в NET
 * @param[in]  ram_bytes
 *
 *   количество оперативной памяти нового аккаунта
 * @param[in]  is_guest     флаг регистрации в качестве гостя
 * @param[in]  set_referer  флаг автоматической установки реферера в контракт
 партнёров

 * @details Метод производит регистрацию нового аккаунта в системе. Если
 is_guest = true, то аккаунт регистрируется
 * в качестве гостя, что означает, что контракт регистратора устанавливает права
 владельца нового аккаунта на себя.
 * Если is_guest = false, то регистратор создаёт новый аккаунт с передачей прав
 владельца на него.
 * Флаг set_referer используется для автоматической установки партнёра в
 реферальную структуру, что не обязательно.
 */
[[eosio::action]] void registrator::regindivid(
    uint64_t coop_id, eosio::name registrator, eosio::name username,
    std::string first_name, std::string second_name, std::string middle_name,
    std::string birthdate, std::string country, std::string city,
    std::string address, std::string phone, std::string meta) {
  require_auth(registrator);

  coops_index coops(_ano, _ano.value);
  auto coop = coops.find(coop_id);
  eosio::check(coop != coops.end(), "Кооператив не обнаружен");
  eosio::check(coop->registrator == registrator,
               "У вас нет прав на регистрацию пайщиков в кооперативе");

  catalog_index catalog(_registrator, _registrator.value);
  auto card = catalog.find(username.value);

  eosio::check(card != catalog.end(), "Участник не найден в картотеке");

  catalog.modify(card, registrator, [&](auto &c) {
    c.type = "individual"_n;
    c.meta = meta;
  });

  individuals_index individuals(_registrator, _registrator.value);
  auto individ = individuals.find(username.value);

  eosio::check(individ == individuals.end(), "account already registered");

  action(permission_level{_registrator, "active"_n}, _soviet, "regaccount"_n,
         std::make_tuple(username))
      .send();

  individuals.emplace(registrator, [&](auto &acc) {
    acc.username = username;
    acc.coop_id = coop_id;
    acc.registrator = registrator;
    acc.first_name = first_name;
    acc.second_name = second_name;
    acc.middle_name = middle_name;
    acc.birthdate = birthdate;
    acc.country = country;
    acc.city = city;
    acc.address = address;
    acc.phone = phone;
  });
}

/**
 * @brief      Метод обновления профиля
 * @auth    username
 * @ingroup public_actions

 * @details Метод производит поиск аккаунтов гостей с истекшим сроком давности
 * и заменяет им активные права доступа. Отозванные аккаунты помещаются в
 таблицу reserved для дальнейшего использования или полного удаления.
 */
[[eosio::action]] void registrator::update(eosio::name username,
                                           std::string nickname,
                                           std::string meta) {
  require_auth(username);

  catalog_index catalog(_registrator, _registrator.value);

  auto card = catalog.find(username.value);

  eosio::check(card != catalog.end(), "account is not registered");

  catalog.modify(card, username, [&](auto &acc) {
    acc.nickname = nickname;
    acc.nickhash = hashit(nickname);
    acc.meta = meta;
  });
}

/**
 * @brief      Метод восстановления ключа
 * @auth    любой аккаунт
 * @ingroup public_actions

 * @details Метод производит поиск аккаунтов гостей с истекшим сроком давности
 * и заменяет им активные права доступа. Отозванные аккаунты помещаются в
 таблицу reserved для дальнейшего использования или полного удаления.
 */
[[eosio::action]] void registrator::changekey(eosio::name username,
                                              eosio::public_key public_key) {
  require_auth(_soviet);

  catalog_index catalog(_registrator, _registrator.value);

  auto card = catalog.find(username.value);

  if (card != catalog.end()) {
    authority active_auth;
    active_auth.threshold = 1;
    key_weight keypermission{public_key, 1};
    active_auth.keys.emplace_back(keypermission);

    // Change active authority of caard to a new key
    eosio::action(eosio::permission_level(card->username, eosio::name("owner")),
                  eosio::name("eosio"), eosio::name("updateauth"),
                  std::tuple(card->username, eosio::name("active"),
                             eosio::name("owner"), active_auth))
        .send();
  }
}
/**
 * @brief      Метод подтверждения регистрации
 * @auth payer
 * @ingroup public_actions
 * @param[in]  payer
 * @param[in]  username  The username
 * @param[in]  quantity  The quantity
 * @details Метод оплаты вызывается гостем после пополнения своего баланса как
 * регистратора. Оплата списывается с баланса регистратора, а права владельца
 * заменяются на публичный ключ, указанный в объекте гостя.
 */
[[eosio::action]] void registrator::confirmreg(eosio::name username) {
  require_auth(_soviet);

  catalog_index catalog(_registrator, _registrator.value);
  auto card = catalog.find(username.value);
  eosio::check(card != catalog.end(), "account is not found");

  catalog.modify(card, _soviet, [&](auto &g) { g.status = "member"_n; });
}

extern "C" {

/// The apply method implements the dispatch of events to this contract
void apply(uint64_t receiver, uint64_t code, uint64_t action) {
  if (code == ::_registrator.value) {
    if (action == "update"_n.value) {
      execute_action(name(receiver), name(code), &registrator::update);
    } else if (action == "confirmreg"_n.value) {
      execute_action(name(receiver), name(code), &registrator::confirmreg);
    } else if (action == "newaccount"_n.value) {
      execute_action(name(receiver), name(code), &registrator::newaccount);
    } else if (action == "regindivid"_n.value) {
      execute_action(name(receiver), name(code), &registrator::regindivid);
    } else if (action == "changekey"_n.value) {
      execute_action(name(receiver), name(code), &registrator::changekey);
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
      if (op.to == _registrator) {

        eosio::name username = eosio::name(op.memo.c_str());
        registrator::add_balance(_registrator, username, op.quantity, code);
      }
    }
  }
};
};
