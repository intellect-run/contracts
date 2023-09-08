#include <eosio/asset.hpp>
#include <eosio/contract.hpp>
#include <eosio/crypto.hpp>
#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/system.hpp>
#include <eosio/time.hpp>

#include "../common/consts.hpp"
#include "../common/utils.hpp"
#include "../common/counts.hpp"

class [[eosio::contract]] draft : public eosio::contract {

public:
  draft(eosio::name receiver, eosio::name code,
        eosio::datastream<const char *> ds)
      : eosio::contract(receiver, code, ds) {}

  [[eosio::action]] void newid(uint64_t id);

  [[eosio::action]] void create(eosio::name lang, eosio::name action_name,
                                std::string name, std::string description,
                                std::string context,
                                std::string data); // used by ANO
  
  [[eosio::action]] void publish(uint64_t draft_id); // used by ANO or coop after USE
  [[eosio::action]] void use(uint64_t coop_id, uint64_t draft_id);     // after publish can be used by COOP
  [[eosio::action]] void replace();
  // used by coop for replace doc with new version
  [[eosio::action]] void del (); // can be used by ANO or coop before publish
  [[eosio::action]] void edit();
  // used by ANO and increase version, after COOP can use it by USE with
  // new version, if not - still use old version

  void apply(uint64_t receiver, uint64_t code, uint64_t action);

  struct [[eosio::table, eosio::contract("draft")]] drafts {
    uint64_t id;
    eosio::name lang;
    eosio::name action_name;
    std::string name;
    std::string description;
    std::string context;
    std::string data;
    bool is_active;
    bool is_approved;
    bool is_standart;
    eosio::time_point_sec created_at;
    eosio::time_point_sec last_update;
    uint64_t doc_version;

    uint64_t primary_key() const { return id; };

    uint64_t by_action() const { return action_name.value; };

    uint128_t by_action_lang() const {
      return combine_ids(action_name.value, lang.value);
    };
  };

  typedef eosio::multi_index<
      "drafts"_n, drafts,
      eosio::indexed_by<"byaction"_n, eosio::const_mem_fun<drafts, uint64_t,
                                                           &drafts::by_action>>,
      eosio::indexed_by<
          "byactionlang"_n,
          eosio::const_mem_fun<drafts, uint128_t, &drafts::by_action_lang>>>
      drafts_index;

  struct [[eosio::table, eosio::contract("draft")]] counts : counts_base {};
};
