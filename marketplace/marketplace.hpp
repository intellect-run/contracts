#include <eosio/asset.hpp>
#include <eosio/contract.hpp>
#include <eosio/crypto.hpp>
#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/system.hpp>
#include <eosio/time.hpp>

static constexpr eosio::name _me = "marketplace"_n;
static constexpr eosio::name _soviet = "soviet"_n;

class [[eosio::contract]] marketplace : public eosio::contract {

public:
  marketplace(eosio::name receiver, eosio::name code,
              eosio::datastream<const char *> ds)
      : eosio::contract(receiver, code, ds) {}

  [[eosio::action]] void create(eosio::name creator,
                                   eosio::name category,
                                   eosio::name contract,
                                   eosio::asset price,
                                   std::string data);

  [[eosio::action]] void authorize(uint64_t order_id);
  [[eosio::action]] void order(eosio::name buyer, uint64_t item_id,
                               std::string meta);

  [[eosio::action]] void approve(eosio::name username, uint64_t order_id);
  [[eosio::action]] void decline(eosio::name username, uint64_t order_id, std::string meta);


  [[eosio::action]] void confirm(eosio::name username, uint64_t order_id);
  
  [[eosio::action]] void newitem(uint64_t id);

  void apply(uint64_t receiver, uint64_t code, uint64_t action);
  
  static void add_balance(eosio::name username, eosio::asset quantity,
                              eosio::name contract);

  static void sub_balance(eosio::name username, eosio::asset quantity,
                          eosio::name contract);

  static uint128_t combine_ids(const uint64_t &x, const uint64_t &y) {
    return (uint128_t{x} << 64) | y;
  };

  struct [[eosio::table, eosio::contract("marketplace")]] balance {
    uint64_t id;          /*!< идентификатор баланса */
    eosio::name contract; /*!< имя контракта токена */
    eosio::asset quantity; /*!< количество токенов на балансе */

    uint64_t primary_key() const { return id; } /*!< return id - primary_key */

    uint128_t byconsym() const {
      return combine_ids(contract.value, quantity.symbol.code().raw());
    }
  };

  typedef eosio::multi_index<
      "balance"_n, balance,
      eosio::indexed_by<"byconsym"_n, eosio::const_mem_fun<balance, uint128_t,
                                                           &balance::byconsym>>>
      ubalances_index;

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
  }

  struct [[eosio::table, eosio::contract("marketplace")]] counts {
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

  struct [[eosio::table, eosio::contract("marketplace")]] items {
    uint64_t id;
    eosio::name creator;
    eosio::name category;
    eosio::name status;
    eosio::name contract;
    eosio::asset price_for_pieces;
    uint64_t total_pieces;
    uint64_t blocked_pieces;
    uint64_t delireved_pieces;
    std::string data;

    uint64_t primary_key() const { return id; }
    uint64_t by_status() const { return status.value; }
    uint64_t by_category() const { return category.value; }
  };

  typedef eosio::multi_index<
      "items"_n, items,
      eosio::indexed_by<"bystatus"_n, eosio::const_mem_fun<items, uint64_t,
                                                           &items::by_status>>,
      eosio::indexed_by<"bycategory"_n,
                        eosio::const_mem_fun<items, uint64_t, &items::by_category>>>
      items_index;

  struct [[eosio::table, eosio::contract("marketplace")]] orders {
    uint64_t id;
    uint64_t item_id;
    eosio::name requester;
    eosio::asset price;
    eosio::name contract;
    eosio::name status;
    std::string meta;

    uint64_t primary_key() const { return id; }
    uint64_t by_item() const { return item_id; }
    uint64_t by_status() const { return status.value; }
    
  };

  typedef eosio::multi_index<
      "orders"_n, orders,
      eosio::indexed_by<"byitem"_n, eosio::const_mem_fun<orders, uint64_t,
                                                           &orders::by_item>>,
      eosio::indexed_by<"bystatus"_n,
                        eosio::const_mem_fun<orders, uint64_t, &orders::by_status>>>
      orders_index;



  struct [[eosio::table, eosio::contract("soviet")]] admins {
    eosio::name username;
    std::vector<eosio::name> rights;

    uint64_t primary_key() const { return username.value; }
      
  };

  typedef eosio::multi_index< "admins"_n, admins > admin_index;

};
