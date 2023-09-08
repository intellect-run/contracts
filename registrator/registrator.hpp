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
#include "../common/users.hpp"
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
class [[eosio::contract(REGISTRATOR)]] registrator : public eosio::contract {

public:
  registrator(eosio::name receiver, eosio::name code,
              eosio::datastream<const char *> ds)
      : eosio::contract(receiver, code, ds) {}

  [[eosio::action]] void update(eosio::name username, std::string nickname,
                                std::string meta);
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

 struct [[eosio::table, eosio::contract("registrator")]] balances : balances_base {};
  
};
