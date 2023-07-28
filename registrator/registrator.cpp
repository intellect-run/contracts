#include "registrator.hpp"
#include "exchange_state.cpp"
using namespace eosio;



  /**
   * @brief      Метод регистрации нового аккаунта
   * @auth    payer
   * @ingroup public_actions
   * @param[in]  payer        имя аккаунта регистратора
   * @param[in]  referer      имя аккаунта реферера нового аккаунта (не обязательно, если set_referer = false)
   * @param[in]  newaccount   имя нового аккаунта
   * @param[in]  public_key   публичный ключ нового аккаунта
   * @param[in]  cpu          количество системного токена в CPU
   * @param[in]  net          количество системного токена в NET
   * @param[in]  ram_bytes    количество оперативной памяти нового аккаунта
   * @param[in]  is_guest     флаг регистрации в качестве гостя
   * @param[in]  set_referer  флаг автоматической установки реферера в контракт партнёров
   
   * @details Метод производит регистрацию нового аккаунта в системе. Если is_guest = true, то аккаунт регистрируется
   * в качестве гостя, что означает, что контракт регистратора устанавливает права владельца нового аккаунта на себя. 
   * Если is_guest = false, то регистратор создаёт новый аккаунт с передачей прав владельца на него. 
   * Флаг set_referer используется для автоматической установки партнёра в реферальную структуру, что не обязательно. 
   */
  [[eosio::action]] void reg::regaccount(eosio::name payer, eosio::name referer, eosio::name newaccount, eosio::public_key public_key, eosio::asset cpu, eosio::asset net, uint64_t ram_bytes, bool is_guest, bool set_referer){
    require_auth(payer);

    //активные разрешения
    authority active_auth;
    active_auth.threshold = 1;
    key_weight keypermission{public_key, 1};
    active_auth.keys.emplace_back(keypermission);

    authority owner_auth;
    auto ram_price = determine_ram_price(ram_bytes);
    
    print("price", ram_price);
    eosio::asset total_pay = cpu + net + ram_price;

    balances_index balances(_me, _me.value);
    auto balance = balances.find(payer.value);
    
    eosio::check(balance != balances.end(), "Balance of registrator is not found");
    eosio::check(balance -> quantity >= total_pay, "Not enought balance of registrator to pay");

    balances.modify(balance, payer, [&](auto &b){
      b.quantity -= total_pay;
    });


    
    std::string newaccount_string = newaccount.to_string();
    
    //TODO check newaccount length and point
    // eosio::check(newaccount_string.size() == 12, "Length of a account name is should be 12 symbols");


    if (is_guest == true) {
      
      owner_auth.threshold = 1;
      eosio::permission_level permission(_me, eosio::name("eosio.code"));
      permission_level_weight accountpermission{permission, 1};
      owner_auth.accounts.emplace_back(accountpermission);

      guests_index guests(_me, _me.value);    
      auto guest = guests.find(newaccount.value);

      eosio::check(guest == guests.end(), "account already registered");

      reserved_index reserve(_me, _me.value);
      auto raccount = reserve.find(newaccount.value);
      
      eosio::check(raccount == reserve.end(), "account has been already registered throw registrator community");
      
      guests.emplace(payer, [&](auto &a){
        a.username = newaccount;
        a.registrator = payer;
        a.expiration = eosio::time_point_sec(now() + _GUEST_EXPIRATION);
        a.to_pay = total_pay + eosio::asset(_MIN_AMOUNT, _SYMBOL);
        a.public_key = public_key;
        a.cpu = cpu;
        // a.set_referer = set_referer;
        a.net = net;
      });
      
    } else {

      owner_auth = active_auth;
    
    }
    
    action(permission_level(_me, "active"_n), 
      "eosio"_n, "newaccount"_n, std::tuple(_me, 
      newaccount, owner_auth, active_auth) 
    ).send();

    action(
      permission_level{ _me, "active"_n},
      "eosio"_n,
      "buyram"_n,
      std::make_tuple(_me, newaccount, ram_price)
    ).send();
    
    action(
      permission_level{ _me, "active"_n},
      "eosio"_n,
      "delegatebw"_n,
     std::make_tuple(_me, newaccount, net, cpu, !is_guest)
    ).send();

    if (set_referer){
      action(
        permission_level{ _me, "active"_n},
        _partners,
        "reg"_n,
       std::make_tuple(newaccount, referer, std::string(""))
      ).send();
    }
    
  }


  /**
   * @brief      Метод отзыва аккаунтов гостей
   * @auth    любой аккаунт
   * @ingroup public_actions
   
   * @details Метод производит поиск аккаунтов гостей с истекшим сроком давности
   * и заменяет им активные права доступа. Отозванные аккаунты помещаются в таблицу reserved для дальнейшего использования или полного удаления.
   */
  [[eosio::action]] void reg::update(){
    
    guests_index guests(_me, _me.value);

    auto guests_by_exp = guests.template get_index<"byexpr"_n>();

    auto guest = guests_by_exp.begin();

    uint64_t count = 0;
    std::vector<eosio::name> list_for_delete;
    bool not_expired = false;

    while (guest != guests_by_exp.end() && (count < _BASKET) && (!not_expired) ){
      if (guest->expiration < eosio::time_point_sec(now())){
        authority newauth;
        newauth.threshold = 1;
        eosio::permission_level permission(_me, eosio::name("eosio.code"));
        permission_level_weight accountpermission{permission, 1};
        newauth.accounts.emplace_back(accountpermission);

        //Change active authority of guest to registrator@eosio.code
        eosio::action(eosio::permission_level(guest->username, eosio::name("owner")), 
          eosio::name("eosio"), eosio::name("updateauth"), std::tuple(guest->username, 
            eosio::name("active"), eosio::name("owner"), newauth) 
        ).send();
        

        list_for_delete.push_back(guest->username);
        
             
      } else {
        not_expired = true;
      }

      count++;
      guest++;   
    }

    for (auto username : list_for_delete){
      auto guest_for_delete = guests.find(username.value);
      

      reserved_index reserve(_me, _me.value);
      
      reserve.emplace(_me, [&](auto &r){
        r.username = username;
        r.registrator = guest_for_delete->registrator;
      });

      guests.erase(guest_for_delete);

    }
  }




  /**
   * @brief      Метод восстановления ключа
   * @auth    любой аккаунт
   * @ingroup public_actions
   
   * @details Метод производит поиск аккаунтов гостей с истекшим сроком давности
   * и заменяет им активные права доступа. Отозванные аккаунты помещаются в таблицу reserved для дальнейшего использования или полного удаления.
   */
  [[eosio::action]] void reg::changekey(eosio::name username, eosio::public_key public_key){
    require_auth(_me);

    guests_index guests(_me, _me.value);

    auto guest = guests.find(username.value);

    if (guest != guests.end()) {
      authority active_auth;
      active_auth.threshold = 1;
      key_weight keypermission{public_key, 1};
      active_auth.keys.emplace_back(keypermission);


      //Change active authority of guest to a new key
      eosio::action(eosio::permission_level(guest->username, eosio::name("owner")), 
        eosio::name("eosio"), eosio::name("updateauth"), std::tuple(guest->username, 
          eosio::name("active"), eosio::name("owner"), active_auth) 
      ).send();
        

      guests.modify(guest, _me, [&](auto &g){
        g.public_key = public_key; 
      });
    } 

  }

  
  void reg::add_balance(eosio::name payer, eosio::name username, eosio::asset quantity, uint64_t code){
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
  [[eosio::action]] void reg::payforguest(eosio::name payer, eosio::name username, eosio::asset quantity) {
    require_auth(payer);

    guests_index guests(_me, _me.value);
    auto guest = guests.find(username.value);
    eosio::check(guest != guests.end(), "Guest is not found");


    balances_index balances(_me, _me.value);
    auto balance = balances.find(payer.value);

    //CHECK and mofidy balance
    eosio::check(balance -> quantity >= guest ->to_pay, "Not enought balance for pay");
    eosio::asset remain = quantity - guest -> to_pay;
      
    if (remain.amount > 0) {
      reg::add_balance(payer, "eosio.saving"_n, remain, "eosio.token"_n.value);
    }
    
    if (balance -> quantity == quantity) {
      balances.erase(balance);
    } else {
      balances.modify(balance, payer, [&](auto &b){
        b.quantity -= guest -> to_pay;
      });
    }
 
    eosio::check((guest->to_pay).amount <= quantity.amount, "Wrong amount");
    eosio::check((guest->to_pay).symbol == quantity.symbol, "Wrong symbol");
        
    authority newauth;
    newauth.threshold = 1;
    
    key_weight k_weight{guest->public_key, 1};
    
    newauth.keys.emplace_back(k_weight);

    eosio::action(eosio::permission_level(guest->username, eosio::name("owner")), eosio::name("eosio"), eosio::name("updateauth"), std::tuple(eosio::name(guest->username), eosio::name("owner"), eosio::name(""), newauth) ).send();

    guests.erase(guest);
  }




  


extern "C" {
   
   /// The apply method implements the dispatch of events to this contract
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
        if (code == reg::_me.value) {
          if (action == "update"_n.value){
            execute_action(name(receiver), name(code), &reg::update);
          } else if (action == "payforguest"_n.value){
            execute_action(name(receiver), name(code), &reg::payforguest);
          } else if (action == "regaccount"_n.value){
            execute_action(name(receiver), name(code), &reg::regaccount);
          } else if (action == "changekey"_n.value){
            execute_action(name(receiver), name(code), &reg::changekey);
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
            if (op.to == reg::_me){

              eosio::name username = eosio::name(op.memo.c_str());
              reg::add_balance(op.from, username, op.quantity, code);
            }
          }
        }
  };
};
