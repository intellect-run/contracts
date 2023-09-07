#include <eosio/asset.hpp>
#include <eosio/contract.hpp>
#include <eosio/crypto.hpp>
#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/system.hpp>
#include <eosio/time.hpp>

static constexpr eosio::name _me = "draft"_n;
static constexpr eosio::name _ano = "ano";
static constexpr eosio::symbol _root_symbol =
    eosio::symbol(eosio::symbol_code("AXON"), 4); /*!< системный токен */

class [[eosio::contract]] draft : public eosio::contract {

public:
  draft(eosio::name receiver, eosio::name code,
        eosio::datastream<const char *> ds)
      : eosio::contract(receiver, code, ds) {}

  [[eosio::action]] void hello(std::string message);
  [[eosio::action]] void create();  // used by ANO
  [[eosio::action]] void publish(); // used by ANO or coop after USE
  [[eosio::action]] void use();     // after publish can be used by COOP
  [[eosio::action]] void replace();
  // used by coop for replace doc with new version
  [[eosio::action]] void delete (); // can be used by ANO or coop before publish
  [[eosio::action]] void edit();
  // used by ANO and increase version, after COOP can use it by USE with
  // new version, if not - still use old version

  void apply(uint64_t receiver, uint64_t code, uint64_t action);

  static uint128_t combine_ids(const uint64_t &x, const uint64_t &y) {
    return (uint128_t{x} << 64) | y;
  };

  uint64_t get_global_id(eosio::name key) {
    counts_index counts(_me, _me.value);
    auto count = counts.find(key.value);
    uint64_t id = 1;

    if (count == counts.end()) {
      counts.emplace(_me, [&](auto &c) {
        c.key = key;
        c.value = id;
      });
    } else {
      id = count->value + 1;
      counts.modify(count, _me, [&](auto &c) { c.value = id; });
    }

    return id;
  };

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
    bool is_standard;
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

  struct [[eosio::table, eosio::contract("draft")]] counts {
    eosio::name key;
    eosio::name secondary_key;
    uint64_t value;

    uint64_t primary_key() const {
      return key.value;
    } /*!< return id - primary_key */
    uint128_t keyskey() const {
      return combine_ids(key.value, secondary_key.value);
    } /*!< (contract, blocked_now.symbol) - комбинированный secondary_key для
         получения курса по имени выходного контракта и символу */
    uint128_t keyvalue() const {
      return combine_ids(key.value, value);
    } /*!< (contract, blocked_now.symbol) - комбинированный secondary_key для
         получения курса по имени выходного контракта и символу */
  };

  typedef eosio::multi_index<
      "counts"_n, counts,
      eosio::indexed_by<"keyskey"_n, eosio::const_mem_fun<counts, uint128_t,
                                                          &counts::keyskey>>>
      counts_index;
};
