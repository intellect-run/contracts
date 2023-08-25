#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/system.hpp>
#include <eosio/time.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/contract.hpp>
#include <eosio/crypto.hpp>

#include "exchange_state.hpp"

/**
\defgroup public_consts CONSTS
\brief Константы контракта
*/

/**
\defgroup public_actions ACTIONS
\brief Методы действий контракта
*/

/**
\defgroup public_tables TABLES
\brief Структуры таблиц контракта
*/

/**
 * @brief      Начните ознакомление здесь.
*/
class [[eosio::contract]] registrator : public eosio::contract {

public:
    registrator( eosio::name receiver, eosio::name code, eosio::datastream<const char*> ds ): eosio::contract(receiver, code, ds)
    {}

    // [[eosio::action]] void addguest(eosio::name username, eosio::name registrator, eosio::public_key public_key, eosio::asset d_cpu, eosio::asset d_net);
    [[eosio::action]] void update(eosio::name username, std::string nickname, std::string meta);
    static void add_balance(eosio::name payer, eosio::name username, eosio::asset quantity, uint64_t code);

    [[eosio::action]] void confirmreg(eosio::name username);
    
    [[eosio::action]] void regaccount(eosio::name registrator, eosio::name referer, eosio::name username, std::string nickname, eosio::public_key public_key, eosio::asset cpu, eosio::asset net, uint64_t ram_bytes, std::string fullname, std::string birthdate, std::string country, std::string city, std::string address, std::string phone, std::string meta);
    
    [[eosio::action]] void changekey(eosio::name username, eosio::public_key public_key);

    void apply(uint64_t receiver, uint64_t code, uint64_t action);
    
    
    /**
    * @ingroup public_consts 
    * @{ 
    */
    
    static constexpr eosio::name _me = "registrator"_n;             /*!< собственное имя аккаунта контракта */
    static constexpr eosio::name _partners = "part"_n;              /*!< имя аккаунта контракта хранилища партнёров */
    static constexpr eosio::name _soviet = "soviet"_n;               /*!< имя аккаунта цифровой экономики ядра */
    static constexpr eosio::name _system_account = "eosio"_n;       /*!< имя аккаунта системного контракта */
    
    static const uint64_t _GUEST_EXPIRATION = 1209600;              /*!< продолжительность гостевого периода, после которого, аккаунт может быть отозван */
    // static const uint64_t _GUEST_EXPIRATION = 10; //10 secs
    static constexpr eosio::symbol _SYMBOL = eosio::symbol(eosio::symbol_code("AXON"),4); /*!< системный токен */
    static constexpr eosio::symbol _ramcore_symbol = eosio::symbol(eosio::symbol_code("RAMCORE"), 4); /*!< идентификационный токен рынка оперативной памяти */

    static constexpr eosio::symbol RAM_symbol{"RAM", 0}; /*!< токен рынка оперативной памяти */

    static const uint64_t _MIN_AMOUNT = 10000;           /*!< комиссия, взымаемая регистратором за пользование гостевым аккаунтом */
        
    static const uint64_t _BASKET = 3;                  /*!< количество гостевых аккаунтов, которые могут быть отозваны за один вызов действия */
    
    /**
    * @}
    */
    

    eosio::checksum256 hashit(std::string str) const
    {
        return eosio::sha256(const_cast<char*>(str.c_str()), str.size());
    }


    static uint128_t combine_ids(const uint64_t &x, const uint64_t &y) {
        return (uint128_t{x} << 64) | y;
    };

   struct permission_level_weight {
      eosio::permission_level  permission;
      uint16_t          weight;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( permission_level_weight, (permission)(weight) )
   };

   struct key_weight {
      eosio::public_key  key;
      uint16_t           weight;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( key_weight, (key)(weight) )
   };

   struct wait_weight {
      uint32_t           wait_sec;
      uint16_t           weight;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( wait_weight, (wait_sec)(weight) )
   };

   struct authority {
      uint32_t                              threshold = 0;
      std::vector<key_weight>               keys;
      std::vector<permission_level_weight>  accounts;
      std::vector<wait_weight>              waits;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( authority, (threshold)(keys)(accounts)(waits) )
   };


    /**
     * @brief      Таблица хранения объектов гостей
     * @ingroup public_tables
     * @table accounts
     * @contract _me
     * @scope _me
     * @details Хранит аккаунты, зарегистрированные в системе в качестве гостей, чьи права владельца аккаунта принадлежат регистратору _me. 
    */


    struct [[eosio::table]] accounts {
        eosio::name username;             /*!< имя аккаунта */
        eosio::name status;               /*!< статус аккаунта */
        eosio::name registrator;          /*!< имя аккаунта регистратора */
        eosio::name referer; 

        std::string nickname; 
        eosio::checksum256 nickhash; 
        
        eosio::time_point_sec registered_at;
        eosio::asset to_pay;              /*!< количество токенов к оплате */
        
        std::string fullname;
        std::string birthdate;
        std::string country;
        std::string city;
        std::string address;
        std::string phone;

        std::string meta;

        uint64_t primary_key() const {return username.value;}     /*!< return username - primary_key */
        
        uint64_t byreg() const {return registrator.value;}            /*!< return registrator - secondary_key 3 */
        uint64_t bystatus() const {return status.value;}            /*!< return registrator - secondary_key 3 */

        EOSLIB_SERIALIZE(accounts, (username)(status)(registrator)(referer)(nickname)(nickhash)(registered_at)(to_pay)(fullname)(birthdate)(country)(city)(address)(phone)(meta))
    };

    typedef eosio::multi_index<"accounts"_n, accounts,
       eosio::indexed_by< "bystatus"_n, eosio::const_mem_fun<accounts, uint64_t, &accounts::bystatus>>,
       eosio::indexed_by< "byreg"_n, eosio::const_mem_fun<accounts, uint64_t, &accounts::byreg>>
    > accounts_index;



    /**
     * @brief      Таблица хранения отозванных аккаунтов гостей
     * @ingroup public_tables
     * @table reserved
     * @contract _me
     * @scope _me
     * @details Хранит аккаунты, отозванные у гостей путём замены их активного ключа на ключ регистратора за истечением срока давности без поступления оплаты.
    */
    struct [[eosio::table]] reserved {
        eosio::name username;         /*!< имя аккаунта гостя */
        eosio::name registrator;      /*!< имя аккаунта регистратора */

        uint64_t primary_key() const {return username.value;} /*!< return username - primary_key */

        EOSLIB_SERIALIZE(reserved, (username)(registrator))
    };

    typedef eosio::multi_index<"reserved"_n, reserved> reserved_index;
 

    /**
     * @brief      Таблица хранения балансов регистраторов
     * @ingroup public_tables
     * @table balance
     * @contract _me
     * @scope _me
     * @details Хранит балансы регистраторов аккаунтов в системных токенах для оплаты регистрации аккаунтов гостей в "долг". 
    */
    struct [[eosio::table]] balance {
        eosio::name username;     /*!< имя аккаунта гостя */
        eosio::asset quantity;    /*!< количество системных токенов */

        uint64_t primary_key() const {return username.value;} /*!< return username - primary_key */

        EOSLIB_SERIALIZE(balance, (username)(quantity))
    };

    typedef eosio::multi_index<"balance"_n, balance> balances_index;
 

    eosio::asset determine_ram_price(uint32_t bytes) {
      eosiosystem::rammarket rammarkettable(_system_account, _system_account.value);
      auto market = rammarkettable.get(_ramcore_symbol.raw());
      auto ram_price = market.convert(eosio::asset{bytes, RAM_symbol}, _SYMBOL);
      ram_price.amount = (ram_price.amount * 200 + 199) / 199; // add ram fee
      return ram_price;
    }
    


    /**
     * @brief      Таблица хранения кодекса и версий
     * @ingroup public_tables
     * @table codex
     * @contract _me
     * @scope _me
     * @details Хранит текущие версии кодекса для языковых кодов;
    */
    struct [[eosio::table]] codex {
        eosio::name lang;         /*!< языковой код кодекса */
        uint64_t version;      /*!< версия кодекса*/
        uint64_t subversion;   /*!< субверсия кодекса (устанавливается автоматически) */
        std::string data;      /*!< содержание кодекса*/

        uint64_t primary_key() const {return lang.value;} /*!< return lang - primary_key */
        uint128_t langandvers() const { return combine_ids(lang.value, version); }
    
        EOSLIB_SERIALIZE(codex, (lang)(version)(subversion)(data))
    };

    typedef eosio::multi_index<"codex"_n, codex,
      eosio::indexed_by<"langandvers"_n, eosio::const_mem_fun<codex, uint128_t, &codex::langandvers>>
    > codex_index;
 


    /**
     * @brief      Таблица хранения подписей кодекса
     * @ingroup public_tables
     * @table signs
     * @contract _me
     * @scope _me
     * @details Хранит аккаунты, отозванные у гостей путём замены их активного ключа на ключ регистратора за истечением срока давности без поступления оплаты.
    */
    struct [[eosio::table]] signs {
        eosio::name username;         /*!< имя подписанта */
        eosio::name lang;      /*!< версия кодекса*/
        uint64_t version;      /*!< подписанная версия кодекса*/
        eosio::time_point_sec signed_at;      /*!< дата подписания */

        uint64_t primary_key() const {return username.value;} /*!< return username - primary_key */

        EOSLIB_SERIALIZE(signs, (username)(lang)(version)(signed_at))
    };

    typedef eosio::multi_index<"signs"_n, signs> signs_index;
 
};
