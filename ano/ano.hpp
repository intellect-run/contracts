#include <eosio/asset.hpp>
#include <eosio/contract.hpp>
#include <eosio/crypto.hpp>
#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/system.hpp>
#include <eosio/time.hpp>

static constexpr eosio::name _me = "ano"_n;

static constexpr eosio::symbol _root_symbol =
    eosio::symbol(eosio::symbol_code("AXON"), 4); /*!< системный токен */

class [[eosio::contract]] ano : public eosio::contract {

public:
  ano(eosio::name receiver, eosio::name code,
              eosio::datastream<const char *> ds)
      : eosio::contract(receiver, code, ds) {}


  [[eosio::action]] void startcoop(eosio::name chairman, eosio::name registrator, std::string data);
  [[eosio::action]] void stopcoop(uint64_t id, std::string reason);
  [[eosio::action]] void newid(uint64_t coop_id);

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

  std::string generate_random_name() {
    const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";
    const int ALPHABET_SIZE = sizeof(ALPHABET) - 1;
    const int NAME_LENGTH = 12;

    uint64_t current_time = eosio::current_time_point().sec_since_epoch(); // Получаем текущее время
    std::string random_name;

    for(int i = 0; i < NAME_LENGTH; ++i) {
      current_time = (current_time * 1103515245 + 12345) % 0x100000000;  // Линейный конгруэнтный метод
      int random_index = (current_time % ALPHABET_SIZE);
      random_name += ALPHABET[random_index];
    }

    return random_name;
  
  }


  struct [[eosio::table, eosio::contract("ano")]] counts {
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

  struct [[eosio::table, eosio::contract("ano")]] coops {
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


};
