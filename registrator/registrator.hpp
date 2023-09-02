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

    [[eosio::action]] void update(eosio::name username, std::string nickname, std::string meta);
    static void add_balance(eosio::name payer, eosio::name username, eosio::asset quantity, uint64_t code);

    [[eosio::action]] void confirmreg(eosio::name username);
    
    [[eosio::action]] void regindivid(uint64_t coop_id, eosio::name registrator, eosio::name username, std::string first_name, std::string second_name, std::string middle_name, std::string birthdate, std::string country, std::string city, std::string address, std::string phone, std::string meta);
    [[eosio::action]] void newaccount(uint64_t coop_id, eosio::name registrator, eosio::name referer, eosio::name username, std::string nickname, eosio::public_key public_key, eosio::asset cpu, eosio::asset net, uint64_t ram_bytes, std::string meta);

    [[eosio::action]] void changekey(eosio::name username, eosio::public_key public_key);

    void apply(uint64_t receiver, uint64_t code, uint64_t action);
    
    
    /**
    * @ingroup public_consts 
    * @{ 
    */
    
    static constexpr eosio::name _me = "registrator"_n;             /*!< собственное имя аккаунта контракта */
    static constexpr eosio::name _partners = "part"_n;              /*!< имя аккаунта контракта хранилища партнёров */
    static constexpr eosio::name _soviet = "soviet"_n;               /*!< имя аккаунта цифровой экономики ядра */
    static constexpr eosio::name _ano = "ano"_n;               /*!< имя аккаунта контракта АНО */
    static constexpr eosio::name _system_account = "eosio"_n;       /*!< имя аккаунта системного контракта */
    
    static constexpr eosio::symbol _SYMBOL = eosio::symbol(eosio::symbol_code("AXON"),4); /*!< системный токен */
    static constexpr eosio::symbol _ramcore_symbol = eosio::symbol(eosio::symbol_code("RAMCORE"), 4); /*!< идентификационный токен рынка оперативной памяти */

    static constexpr eosio::symbol RAM_symbol{"RAM", 0}; /*!< токен рынка оперативной памяти */

    static const uint64_t _MIN_AMOUNT = 10000;           /*!< комиссия, взымаемая регистратором за пользование гостевым аккаунтом */
    
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
     * @table individuals
     * @contract _me
     * @scope _me
     * @details 
    */
    struct [[eosio::table]] individuals {
        eosio::name username;             /*!< имя аккаунта */
        uint64_t coop_id;
        eosio::name status;
        eosio::name registrator;          /*!< имя аккаунта регистратора */
        std::string first_name;
        std::string second_name;
        std::string middle_name;
        std::string birthdate;
        std::string country;
        std::string city;
        std::string address;
        std::string phone;

        std::string meta;

        uint64_t primary_key() const {return username.value;}     /*!< return username - primary_key */
        uint64_t by_coop() const {return coop_id;}
        uint64_t by_status() const {return status.value;}
        uint64_t byregistr() const {return registrator.value;}            /*!< return registrator - secondary_key 3 */
        
    };

    typedef eosio::multi_index<"individuals"_n, individuals,
       eosio::indexed_by< "bycoop"_n, eosio::const_mem_fun<individuals, uint64_t, &individuals::by_coop>>,
       eosio::indexed_by< "bystatus"_n, eosio::const_mem_fun<individuals, uint64_t, &individuals::by_status>>,
       eosio::indexed_by< "byregistr"_n, eosio::const_mem_fun<individuals, uint64_t, &individuals::byregistr>>
    > individuals_index;


    /**
     * @brief      Таблица хранения отозванных аккаунтов гостей
     * @ingroup public_tables
     * @table newaccounts
     * @contract _me
     * @scope _me
     * @details Хранит аккаунты, отозванные у гостей путём замены их активного ключа на ключ регистратора за истечением срока давности без поступления оплаты.
    */
    struct [[eosio::table]] catalog {
        eosio::name username;         /*!< имя аккаунта гостя */
        uint64_t coop_id;
        eosio::name status;               /*!< статус аккаунта "" - никто, "member" */
        std::string nickname; 
        eosio::checksum256 nickhash; 
        
        eosio::name type;               //invidual | coorparate
        eosio::name registrator;      /*!< имя аккаунта регистратора */
        eosio::name referer;
        eosio::asset payed;           /*!< количество токенов к оплате */
        std::string meta;
        eosio::time_point_sec registered_at;

        uint64_t primary_key() const {return username.value;} /*!< return username - primary_key */
        uint64_t by_coop() const {return coop_id;}
        uint64_t by_referer() const {return referer.value;}
        uint64_t by_amount() const {return payed.amount;}
        uint64_t by_type() const {return type.value;}
        uint64_t by_status() const{return status.value;}
        uint64_t by_registr() const {return registrator.value;}

        eosio::checksum256 bynickhash() const { return nickhash; } 

    };

    typedef eosio::multi_index<"catalog"_n, catalog,
       eosio::indexed_by< "bycoop"_n, eosio::const_mem_fun<catalog, uint64_t, &catalog::by_coop>>,
       eosio::indexed_by< "byreferer"_n, eosio::const_mem_fun<catalog, uint64_t, &catalog::by_referer>>,
       eosio::indexed_by< "bytype"_n, eosio::const_mem_fun<catalog, uint64_t, &catalog::by_type>>,
       eosio::indexed_by< "bystatus"_n, eosio::const_mem_fun<catalog, uint64_t, &catalog::by_status>>,
       eosio::indexed_by< "byregistr"_n, eosio::const_mem_fun<catalog, uint64_t, &catalog::by_registr>>,
       eosio::indexed_by< "byamount"_n, eosio::const_mem_fun<catalog, uint64_t, &catalog::by_amount>>,
       eosio::indexed_by<"bynickhash"_n, eosio::const_mem_fun<catalog, eosio::checksum256, &catalog::bynickhash>>
    
    > catalog_index;
 

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
    


    struct [[eosio::table, eosio::contract("registrator")]] coops {
        uint64_t id;
        eosio::name system_name;
        eosio::name status;
        eosio::name chairman;
        eosio::name registrator;
        std::string data;
        std::string message;

        uint64_t primary_key() const {
          return id;
        };
    };

    typedef eosio::multi_index<"coops"_n, coops> coops_index;


};
