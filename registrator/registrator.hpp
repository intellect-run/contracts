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
 * @brief      Начните ознакомление здесь.
 */

class [[eosio::contract(REGISTRATOR)]] registrator : public eosio::contract {

public:
  registrator(eosio::name receiver, eosio::name code,
              eosio::datastream<const char *> ds)
      : eosio::contract(receiver, code, ds) {}

  [[eosio::action]] void update(eosio::name username, std::string meta);
  [[eosio::action]] void confirmreg(eosio::name coop_username, eosio::name member, std::string position_title, eosio::name position);

  [[eosio::action]] void reguser(eosio::name username, std::string profile_hash);

  [[eosio::action]] void regorg(new_org_struct new_org);

  [[eosio::action]] void joincoop(eosio::name coop_username, eosio::name username, std::string position_title, eosio::name position, std::string ricardian_data, std::string statement_hash);

  [[eosio::action]] void verificate(eosio::name username);

  [[eosio::action]] void newaccount(
      eosio::name registrator, eosio::name referer,
      eosio::name username, eosio::public_key public_key,
      eosio::asset cpu, eosio::asset net, uint64_t ram_bytes, std::string meta);

  [[eosio::action]] void changekey(eosio::name username,
                                   eosio::public_key public_key);

  void apply(uint64_t receiver, uint64_t code, uint64_t action);
  
  /**
     * @brief      Таблица хранения глобальной сети партнёров
     * @ingroup public_tables
     * @contract _me
     * @scope _me
     * @table partners
     * @details Таблица хранит реферальные связи партнёров, их профили и глобальные статусы.
  */
  struct [[eosio::table, eosio::contract(REGISTRATOR)]] balances : balances_base {};
  
};
