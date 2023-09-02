#include <eosio/asset.hpp>
#include <eosio/contract.hpp>
#include <eosio/crypto.hpp>
#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/system.hpp>
#include <eosio/time.hpp>

static constexpr eosio::name _me = "starter"_n;

static constexpr eosio::symbol _root_symbol =
    eosio::symbol(eosio::symbol_code("AXON"), 4); /*!< системный токен */

class [[eosio::contract]] starter : public eosio::contract {

public:
  starter(eosio::name receiver, eosio::name code,
              eosio::datastream<const char *> ds)
      : eosio::contract(receiver, code, ds) {}


  [[eosio::action]] void hello(std::string message);

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

  struct [[eosio::table, eosio::contract("starter")]] counts {
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
