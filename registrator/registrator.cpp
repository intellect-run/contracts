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
    eosio::name registrator, eosio::name referer,
    eosio::name username, std::string uid, eosio::public_key public_key,
    eosio::asset cpu, eosio::asset net, uint64_t ram_bytes, std::string meta) {
  require_auth(registrator);
  
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

  accounts_index accounts(_registrator, _registrator.value);
  auto card = accounts.find(username.value);

  eosio::check(card == accounts.end(), "account has been already registered");

  accounts.emplace(registrator, [&](auto &n) {
    n.username = username;
    n.status = "pending"_n;
    n.registrator = registrator;
    n.registration_amount = total_pay;
    n.referer = referer;
    n.uid = uid;
    n.uid_hash = hashit(uid);
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
[[eosio::action]] void registrator::reguser(
  eosio::name registrator, eosio::name username,
      std::string profile, std::string meta){  

  require_auth(registrator);

  accounts_index accounts(_registrator, _registrator.value);
  auto account = accounts.find(registrator.value);
  eosio::check(account != accounts.end(), "Регистратор не найден");

  orgs_index orgs(_registrator, _registrator.value);
  auto registrator_org = orgs.find(registrator.value);
  eosio::check(registrator_org != orgs.end(), "Регистратор не найден");
  eosio::check(registrator_org -> is_cooperative == true && account -> verification.is_verified == true,"Регистрация пользователей доступна только для кооперативов");

  auto new_user = accounts.find(username.value);
  eosio::check(new_user!= accounts.end(), "Участник не найден в картотеке");

  accounts.modify(new_user, registrator, [&](auto &c) {
    c.type = "user"_n;
    c.meta = meta;
  });

  users_index users(_registrator, _registrator.value);
  auto user = users.find(username.value);

  eosio::check(user == users.end(), "Участник уже зарегистрирован");

   users.emplace(registrator, [&](auto &acc) {
    acc.username = username;
    acc.profile = profile;
  });
}

[[eosio::action]] void registrator::verificate(eosio::name username){
  require_auth(_ano);

  accounts_index accounts(_registrator, _registrator.value);
  auto account = accounts.find(username.value);
  eosio::check(account != accounts.end(), "Аккаунт не найден");
  
  accounts.modify(account, _ano, [&](auto &a){
    a.verification.verificator = _ano;
    a.verification.is_verified = true;
    a.verification.created_at = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
    a.verification.last_update = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
  });

  }



[[eosio::action]] void registrator::regorg(new_org_struct new_org) {
    require_auth(new_org.username);  

    orgs_index orgs(_registrator, _registrator.value);

    orgs.emplace(_ano, [&](auto& org) {
      org.username = new_org.username;
      org.name = new_org.name;
      org.short_name = new_org.short_name;
      org.address = new_org.address;
      org.ogrn = new_org.ogrn;
      org.inn = new_org.inn;
      org.logo = new_org.logo;
      org.phone = new_org.phone;
      org.email = new_org.email;
      org.registration = new_org.registration;
      org.website = new_org.website;
      org.accounts = new_org.accounts;
      org.is_cooperative = new_org.is_cooperative;
      org.coop_type = new_org.coop_type;
      org.token_contract = new_org.token_contract;
      org.slug = new_org.slug;
      org.announce = new_org.announce;
      org.description = new_org.description;
      org.initial = new_org.initial;
      org.minimum = new_org.minimum;
      org.membership = new_org.membership;
      org.period = new_org.period;
    });   

}


[[eosio::action]] void registrator::joincoop(eosio::name coop_username, eosio::name username, std::string position_title, uint64_t position){
  require_auth(username);

  members_index members(_registrator, coop_username.value);
  auto member = members.find(username.value);
  eosio::check(member == members.end(), "Участник уже является членом кооператива"); 

  action(permission_level{_registrator, "active"_n}, _soviet, "regaccount"_n,
         std::make_tuple(coop_username, username, position_title, position))
  .send();
};

/**
 * @brief      Метод обновления профиля
 * @auth    username
 * @ingroup public_actions

 * @details Метод производит поиск аккаунтов гостей с истекшим сроком давности
 * и заменяет им активные права доступа. Отозванные аккаунты помещаются в
 таблицу reserved для дальнейшего использования или полного удаления.
 */
[[eosio::action]] void registrator::update(eosio::name username,
                                           std::string uid,
                                           std::string meta) {
  require_auth(username);

  accounts_index accounts(_registrator, _registrator.value);

  auto account = accounts.find(username.value);

  eosio::check(account != accounts.end(), "account is not registered");

  accounts.modify(account, username, [&](auto &acc) {
    acc.uid = uid;
    acc.uid_hash = hashit(uid);
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

  accounts_index accounts(_registrator, _registrator.value);

  auto card = accounts.find(username.value);

  if (card != accounts.end()) {
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
[[eosio::action]] void registrator::confirmreg(eosio::name coop_username, eosio::name member, std::string position_title, eosio::name position) {
  require_auth(_soviet);

  accounts_index accounts(_registrator, _registrator.value);
  auto account = accounts.find(member.value);
  eosio::check(account != accounts.end(), "account is not found");

  accounts.modify(account, _soviet, [&](auto &g) { g.status = "active"_n; });

  members_index members(_registrator, coop_username.value);
  members.emplace(_soviet, [&](auto &m){
    m.username = member;
    m.created_at = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
    m.last_update = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
    m.is_accepted = true;
    m.is_initial = true;
    m.is_minimum = true;
    m.position_title = position_title;
    m.position = position;
  });
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
    } else if (action == "reguser"_n.value) {
      execute_action(name(receiver), name(code), &registrator::reguser);
    } else if (action == "changekey"_n.value) {
      execute_action(name(receiver), name(code), &registrator::changekey);
    } else if (action == "joincoop"_n.value) {
      execute_action(name(receiver), name(code), &registrator::joincoop);
    }
} else { if (action == "transfer"_n.value) { struct transfer { eosio::name from; eosio::name to; eosio::asset quantity; std::string memo; };
      auto op = eosio::unpack_action_data<transfer>();
      if (op.to == _registrator) {

        eosio::name username = eosio::name(op.memo.c_str());
        
        add_balance(_registrator, username, op.quantity, eosio::name(code));
      }
    }
  }
};
};
