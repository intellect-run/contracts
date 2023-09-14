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

  [[eosio::action]] void update(eosio::name username, std::string uid,
                                std::string meta);
  [[eosio::action]] void confirmreg(eosio::name coop_username, eosio::name member, std::string position_title, eosio::name position);

  [[eosio::action]] void reguser(eosio::name username, uint64_t storage_id, std::string internal_data_id);

  [[eosio::action]] void regorg(new_org_struct new_org);

  [[eosio::action]] void joincoop(eosio::name coop_username, eosio::name username, std::string position_title, eosio::name position, std::string ricardian_data, std::string statement_hash);

  [[eosio::action]] void verificate(eosio::name username);

  [[eosio::action]] void newaccount(
      eosio::name registrator, eosio::name referer,
      eosio::name username, std::string uid, eosio::public_key public_key,
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

  struct [[eosio::table, eosio::contract(REGISTRATOR)]] balances : balances_base {};
  
  struct bank {
    std::string account; //Номер расчётного счёта
    eosio::time_point_sec created_at;
    eosio::time_point_sec last_update;
    bool is_active;
  };
  
  struct new_org_struct {
      eosio::name username;
      std::string name; //Полное наименование
      std::string short_name; //Краткое наименование;
      std::string address; //юридический адрес;
      std::string ogrn;
      std::string inn;
      std::string logo;
      std::string phone;
      std::string email;
      std::string registration; //дата регистрации юрлица
      std::string website;
      std::vector <bank> accounts;
      bool is_cooperative = false;
      std::optional<eosio::name> coop_type;
      // (0, _('union')),
      // (1, _('conscoop')),
      // (2, _('prodcoop')),
      // (3, _('agricoop')),
      // (4, _('builderscoop')),
      // (5, _('nonprofitorg'))
      std::optional<eosio::name> token_contract;
      std::optional<std::string> slug; 
      std::optional<std::string> announce;
      std::optional<std::string> description;
      std::optional<eosio::asset> initial;//Вступительный взнос
      std::optional<eosio::asset> minimum;//Минимальный взнос
      std::optional<eosio::asset> membership;//Членский взнос
      std::optional<eosio::name> period;//Периодичность
      // (0, _('per case')),    - зависит от программы
      // (1, _('daily')),
      // (2, _('weekly')),
      // (3, _('monthly')),
      // (4, _('quarterly')),
      // (5, _('half a year')),
      // (6, _('annually')),
      // (7, _('onetime')),
    }; 

};
