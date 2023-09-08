#include <eosio/asset.hpp>
#include <eosio/contract.hpp>
#include <eosio/crypto.hpp>
#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/system.hpp>
#include <eosio/time.hpp>

#include "../common/consts.hpp"
#include "../common/coops.hpp"
#include "../common/permissions.hpp"
#include "../common/rammarket.hpp"
#include "../common/utils.hpp"
#include "../common/balances.hpp"

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
  registrator(eosio::name receiver, eosio::name code,
              eosio::datastream<const char *> ds)
      : eosio::contract(receiver, code, ds) {}

  [[eosio::action]] void update(eosio::name username, std::string nickname,
                                std::string meta);
  static void add_balance(eosio::name payer, eosio::name username,
                          eosio::asset quantity, uint64_t code);

  [[eosio::action]] void confirmreg(eosio::name username);

  [[eosio::action]] void regindivid(
      uint64_t coop_id, eosio::name registrator, eosio::name username,
      std::string first_name, std::string second_name, std::string middle_name,
      std::string birthdate, std::string country, std::string city,
      std::string address, std::string phone, std::string meta);
  [[eosio::action]] void newaccount(
      uint64_t coop_id, eosio::name registrator, eosio::name referer,
      eosio::name username, std::string nickname, eosio::public_key public_key,
      eosio::asset cpu, eosio::asset net, uint64_t ram_bytes, std::string meta);

  [[eosio::action]] void changekey(eosio::name username,
                                   eosio::public_key public_key);

  void apply(uint64_t receiver, uint64_t code, uint64_t action);

  /**
   * @ingroup public_consts
   * @{
   */

  /**
   * @}
   */

  /**
   * @brief      Таблица хранения объектов гостей
   * @ingroup public_tables
   * @table individuals
   * @contract _me
   * @scope _me
   * @details
   */
  struct [[eosio::table]] individuals {
    eosio::name username; /*!< имя аккаунта */
    uint64_t coop_id;
    eosio::name registrator; /*!< имя аккаунта регистратора */
    std::string first_name;
    std::string second_name;
    std::string middle_name;
    std::string birthdate;
    std::string country;
    std::string city;
    std::string address;
    std::string phone;

    std::string meta;

    uint64_t primary_key() const {
      return username.value;
    } /*!< return username - primary_key */
    uint64_t by_coop() const { return coop_id; }
    uint64_t byregistr() const {
      return registrator.value;
    } /*!< return registrator - secondary_key 3 */
  };

  typedef eosio::multi_index<
      "individuals"_n, individuals,
      eosio::indexed_by<
          "bycoop"_n,
          eosio::const_mem_fun<individuals, uint64_t, &individuals::by_coop>>,
      eosio::indexed_by<
          "byregistr"_n,
          eosio::const_mem_fun<individuals, uint64_t, &individuals::byregistr>>>
      individuals_index;

  /**
   * @brief      Таблица хранения отозванных аккаунтов гостей
   * @ingroup public_tables
   * @table newaccounts
   * @contract _me
   * @scope _me
   * @details Хранит аккаунты, отозванные у гостей путём замены их активного
   * ключа на ключ регистратора за истечением срока давности без поступления
   * оплаты.
   */
  struct [[eosio::table]] catalog {
    eosio::name username; /*!< имя аккаунта гостя */
    uint64_t coop_id;
    eosio::name status; /*!< статус аккаунта "" - никто, "member" */
    std::string nickname;
    eosio::checksum256 nickhash;
    eosio::name type;        // invidual | coorparate
    eosio::name registrator; /*!< имя аккаунта регистратора */
    eosio::name referer;
    eosio::asset payed; /*!< количество токенов к оплате */
    std::string meta;
    eosio::time_point_sec registered_at;

    uint64_t primary_key() const {
      return username.value;
    } /*!< return username - primary_key */
    uint64_t by_coop() const { return coop_id; }
    uint64_t by_referer() const { return referer.value; }
    uint64_t by_amount() const { return payed.amount; }
    uint64_t by_type() const { return type.value; }
    uint64_t by_status() const { return status.value; }
    uint64_t by_registr() const { return registrator.value; }

    eosio::checksum256 bynickhash() const { return nickhash; }
  };

  typedef eosio::multi_index<
      "catalog"_n, catalog,
      eosio::indexed_by<"bycoop"_n, eosio::const_mem_fun<catalog, uint64_t,
                                                         &catalog::by_coop>>,
      eosio::indexed_by<
          "byreferer"_n,
          eosio::const_mem_fun<catalog, uint64_t, &catalog::by_referer>>,
      eosio::indexed_by<"bytype"_n, eosio::const_mem_fun<catalog, uint64_t,
                                                         &catalog::by_type>>,
      eosio::indexed_by<
          "bystatus"_n,
          eosio::const_mem_fun<catalog, uint64_t, &catalog::by_status>>,
      eosio::indexed_by<
          "byregistr"_n,
          eosio::const_mem_fun<catalog, uint64_t, &catalog::by_registr>>,
      eosio::indexed_by<
          "byamount"_n,
          eosio::const_mem_fun<catalog, uint64_t, &catalog::by_amount>>,
      eosio::indexed_by<"bynickhash"_n,
                        eosio::const_mem_fun<catalog, eosio::checksum256,
                                             &catalog::bynickhash>>

      >
      catalog_index;

 struct [[eosio::table, eosio::contract("registrator")]] balances : balances_base {};
  
};
