#include "registrator.hpp"
#include "exchange_state.cpp"
using namespace eosio;

  /**
   * @brief      Метод регистрации нового аккаунта
   * @auth    registrator
   * @ingroup public_actions
   * @param[in]  registrator        имя аккаунта регистратора
   * @param[in]  referer      имя аккаунта реферера нового аккаунта (не обязательно, если set_referer = false)
   * @param[in]  newaccount   имя нового аккаунта
   * @param[in]  public_key   публичный ключ нового аккаунта
   * @param[in]  cpu          количество системного токена в CPU
   * @param[in]  net          количество системного токена в NET
   * @param[in]  ram_bytes  
   * 
   *   количество оперативной памяти нового аккаунта
   * @param[in]  is_guest     флаг регистрации в качестве гостя
   * @param[in]  set_referer  флаг автоматической установки реферера в контракт партнёров
   
   * @details Метод производит регистрацию нового аккаунта в системе. Если is_guest = true, то аккаунт регистрируется
   * в качестве гостя, что означает, что контракт регистратора устанавливает права владельца нового аккаунта на себя. 
   * Если is_guest = false, то регистратор создаёт новый аккаунт с передачей прав владельца на него. 
   * Флаг set_referer используется для автоматической установки партнёра в реферальную структуру, что не обязательно. 
   */
  [[eosio::action]] void registrator::regaccount(eosio::name registrator, eosio::name referer, eosio::name username, std::string nickname, eosio::public_key public_key, eosio::asset cpu, eosio::asset net, uint64_t ram_bytes, std::string fullname, std::string birthdate, std::string country, std::string city, std::string address, std::string phone, std::string meta){
    require_auth(registrator);

    accounts_index accounts(_me, _me.value);    
    auto account = accounts.find(username.value);

    eosio::check(account == accounts.end(), "account already registered");
    eosio::asset total_pay = asset(0, _SYMBOL);

    if (registrator != username) {

      //активные разрешения
      authority active_auth;
      active_auth.threshold = 1;
      key_weight keypermission{public_key, 1};
      active_auth.keys.emplace_back(keypermission);

      authority owner_auth;
      auto ram_price = determine_ram_price(ram_bytes);
      
      eosio::asset total_pay = cpu + net + ram_price;

      balances_index balances(_me, _me.value);
      auto balance = balances.find(registrator.value);
      
      eosio::check(balance != balances.end(), "Balance of registrator is not found");
      eosio::check(balance -> quantity >= total_pay, "Not enought balance of registrator to pay");

      balances.modify(balance, registrator, [&](auto &b){
        b.quantity -= total_pay;
      });

      owner_auth.threshold = 1;
      eosio::permission_level permission(_me, eosio::name("eosio.code"));
      permission_level_weight accountpermission{permission, 1};
      owner_auth.accounts.emplace_back(accountpermission);

      reserved_index reserve(_me, _me.value);
      auto raccount = reserve.find(username.value);
      
      eosio::check(raccount == reserve.end(), "account has been already registered throw registrator community");
      
      action(permission_level(_me, "active"_n), 
        "eosio"_n, "newaccount"_n, std::tuple(_me, 
        username, owner_auth, active_auth) 
      ).send();

      action(
        permission_level{ _me, "active"_n},
        "eosio"_n,
        "buyram"_n,
        std::make_tuple(_me, username, ram_price)
      ).send();
      
      action(
        permission_level{ _me, "active"_n},
        "eosio"_n,
        "delegatebw"_n,
       std::make_tuple(_me, username, net, cpu, true)
      ).send();

    } 
  

    accounts.emplace(registrator, [&](auto &acc){
      acc.username = username;
      acc.status = ""_n;
      acc.registrator = registrator;
      acc.referer = referer;
      acc.nickname = nickname;
      acc.nickhash = registrator::hashit(nickname);
      acc.registered_at = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
      acc.to_pay = registrator == username ? asset(_MIN_AMOUNT, _SYMBOL) : total_pay + eosio::asset(_MIN_AMOUNT, _SYMBOL);
      acc.fullname = fullname;
      acc.birthdate = birthdate;
      acc.country = country;
      acc.city = city;
      acc.address = address;
      acc.phone = phone;
      acc.meta = meta;
    });
  
    
  }


  /**
   * @brief      Метод обновления профиля
   * @auth    username
   * @ingroup public_actions
   
   * @details Метод производит поиск аккаунтов гостей с истекшим сроком давности
   * и заменяет им активные права доступа. Отозванные аккаунты помещаются в таблицу reserved для дальнейшего использования или полного удаления.
   */
  [[eosio::action]] void registrator::update(eosio::name username, std::string nickname, std::string meta){
    require_auth(username);

    accounts_index accounts(_me, _me.value);

    auto account = accounts.find(username.value);

    eosio::check(account != accounts.end(), "account is not registered");

    accounts.modify(account, username, [&](auto &acc){
        acc.nickname = nickname;
        acc.nickhash = registrator::hashit(nickname);
        acc.meta = meta;
    });

  }




  /**
   * @brief      Метод восстановления ключа
   * @auth    любой аккаунт
   * @ingroup public_actions
   
   * @details Метод производит поиск аккаунтов гостей с истекшим сроком давности
   * и заменяет им активные права доступа. Отозванные аккаунты помещаются в таблицу reserved для дальнейшего использования или полного удаления.
   */
  [[eosio::action]] void registrator::changekey(eosio::name username, eosio::public_key public_key){
    require_auth(_me);

    accounts_index accounts(_me, _me.value);

    auto account = accounts.find(username.value);

    if (account != accounts.end()) {
      authority active_auth;
      active_auth.threshold = 1;
      key_weight keypermission{public_key, 1};
      active_auth.keys.emplace_back(keypermission);


      //Change active authority of account to a new key
      eosio::action(eosio::permission_level(account->username, eosio::name("owner")), 
        eosio::name("eosio"), eosio::name("updateauth"), std::tuple(account->username, 
          eosio::name("active"), eosio::name("owner"), active_auth) 
      ).send();
        
    } 

  }

  
  void registrator::add_balance(eosio::name payer, eosio::name username, eosio::asset quantity, uint64_t code){
    require_auth(payer);

    balances_index balances(_me, _me.value);
    auto balance = balances.find(username.value);
    
    if (code == "eosio.token"_n.value && quantity.symbol == _SYMBOL){
      if (username == ""_n)
        username = payer;

      if (balance  == balances.end()) {
        balances.emplace(_me, [&](auto &b){
          b.username = username;
          b.quantity = quantity;
        }); 
      } else {
        balances.modify(balance, _me, [&](auto &b){
          b.quantity += quantity;
        });
      };
    }
  }


  /**
   * @brief      Метод оплаты аккаунта гостя
   * @auth payer
   * @ingroup public_actions
   * @param[in]  payer     
   * @param[in]  username  The username
   * @param[in]  quantity  The quantity
   * @details Метод оплаты вызывается гостем после пополнения своего баланса как регистратора. 
   * Оплата списывается с баланса регистратора, а права владельца заменяются на публичный ключ, указанный в объекте гостя.
   */
  [[eosio::action]] void registrator::confirmreg(eosio::name username) {
    require_auth(_soviet);

    accounts_index accounts(_me, _me.value);
    auto account = accounts.find(username.value);
    eosio::check(account != accounts.end(), "account is not found");

    balances_index balances(_me, _me.value);
    auto balance = balances.find(payer.value);

    //CHECK and mofidy balance
    eosio::check(balance -> quantity >= account -> to_pay, "Not enought balance for pay");
    
    if (balance -> quantity == quantity) {

      balances.erase(balance);

    } else {
      
      balances.modify(balance, payer, [&](auto &b){
        b.quantity -= account -> to_pay;
      });

    }
 
    eosio::check((account->to_pay).amount <= quantity.amount, "Wrong amount");
    eosio::check((account->to_pay).symbol == quantity.symbol, "Wrong symbol");
       
    accounts.modify(account, payer, [&](auto &g){
      g.status = "member"_n;
    });
   
  }




  


extern "C" {
   
   /// The apply method implements the dispatch of events to this contract
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
        if (code == registrator::_me.value) {
          if (action == "update"_n.value){
            execute_action(name(receiver), name(code), &registrator::update);
          } else if (action == "pay"_n.value){
            execute_action(name(receiver), name(code), &registrator::pay);
          } else if (action == "regaccount"_n.value){
            execute_action(name(receiver), name(code), &registrator::regaccount);
          } else if (action == "changekey"_n.value){
            execute_action(name(receiver), name(code), &registrator::changekey);
          } 

        } else {
          if (action == "transfer"_n.value){
            
            struct transfer {
                eosio::name from;
                eosio::name to;
                eosio::asset quantity;
                std::string memo;
            };

            auto op = eosio::unpack_action_data<transfer>();
            if (op.to == registrator::_me){

              eosio::name username = eosio::name(op.memo.c_str());
              registrator::add_balance(op.from, username, op.quantity, code);
            }
          }
        }
  };
};
