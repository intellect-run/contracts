/**
 * @file marketplace.hpp
 * @brief Основной заголовочный файл для контракта "marketplace"
 *
 * Этот файл содержит определение класса "marketplace" и связанных с ним структур и функций.
 * Контракт реализует функциональность рынка, включая создание, обновление и управление заявками, а также управление балансами.
 *
 * Дополнительно в этом файле определяются константы и методы, которые используются в контракте.
 */

#include <eosio/asset.hpp>
#include <eosio/contract.hpp>
#include <eosio/crypto.hpp>
#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/system.hpp>
#include <eosio/time.hpp>

#include "include/utils.hpp"  
#include "include/admins.hpp"
#include "include/change.hpp"
#include "include/balances.hpp"


static constexpr eosio::name _me = "marketplace"_n; /*!< имя контракта */
static constexpr eosio::name _soviet = "soviet"_n; /*!< дополнительная константа */
static constexpr eosio::symbol _SYMBOL = eosio::symbol(eosio::symbol_code("AXON"),4); /*!< системный токен */
static constexpr eosio::name _CONTRACT = "eosio.token"_n; /*!< системный контракт */
       
/**
 * @class marketplace
 * @brief Основной класс контракта "marketplace"
 *
 * Включает в себя методы для работы с заявками на обмен, управления балансами и административные действия.
 */        
class [[eosio::contract]] marketplace : public eosio::contract {

public:
  /**
   * @brief Конструктор контракта "marketplace"
   */
  marketplace(eosio::name receiver, eosio::name code,
              eosio::datastream<const char *> ds)
      : eosio::contract(receiver, code, ds) {}

  void apply(uint64_t receiver, uint64_t code, uint64_t action);

  // ... определение методов контракта ...
  
  //marketplace.cpp
  [[eosio::action]] void newid(uint64_t id, eosio::name type);

  //soviet.cpp
  [[eosio::action]] void authorize(uint64_t exchange_id);
  
  //change.cpp
  /**
   * @struct exchange_params
   * @brief Параметры заявки на обмен
   *
   * Эта структура содержит информацию, необходимую для создания или обновления заявки на обмен в контракте "marketplace".
   *
   * @param username Имя пользователя, создающего или обновляющего заявку
   * @param parent_id Идентификатор родительской заявки (если применимо)
   * @param contract Имя контракта токена, участвующего в обмене
   * @param pieces Количество частей (штук) для обмена
   * @param price_for_piece Цена за единицу (штуку) товара в формате eosio::asset
   * @param data Дополнительные данные, специфичные для заявки (например, условия обмена)
   * @param meta Метаданные, содержащие дополнительную информацию о заявке (например, описание товара)
   */
  struct exchange_params {
    eosio::name username; /*!< имя пользователя */
    uint64_t parent_id; /*!< идентификатор родительской заявки */
    eosio::name contract; /*!< имя контракта токена */
    uint64_t pieces; /*!< количество частей (штук) */
    eosio::asset price_for_piece; /*!< цена за единицу (штуку) товара */
    std::string data; /*!< дополнительные данные */
    std::string meta; /*!< метаданные */
  };

  [[eosio::action]] void offer(const exchange_params& params);
  [[eosio::action]] void order(const exchange_params& params);

  static void create(eosio::name type, const exchange_params& params);
  static void create_parent_order(eosio::name type, const exchange_params& params);
  static void create_child_order(eosio::name type, const exchange_params& params);
  static void cancel_parent_order(eosio::name username, uint64_t exchange_id);
  static void cancel_child_order(eosio::name username, uint64_t exchange_id);

  [[eosio::action]] void accept(eosio::name username, uint64_t exchange_id);
  [[eosio::action]] void decline(eosio::name username, uint64_t exchange_id,
                                 std::string meta);
  
  [[eosio::action]] void complete(eosio::name username, uint64_t exchange_id);

  [[eosio::action]] void cancel(eosio::name username, uint64_t exchange_id);
  
  [[eosio::action]] void update(eosio::name username, uint64_t exchange_id, eosio::asset price_for_piece, std::string data, std::string meta);
  [[eosio::action]] void addpieces(eosio::name username, uint64_t exchange_id, uint64_t new_pieces);

  //admins.cpp
  [[eosio::action]] void moderate(eosio::name username, uint64_t exchange_id);
  [[eosio::action]] void prohibit(eosio::name username, uint64_t exchange_id, std::string meta);
  [[eosio::action]] void unpublish(eosio::name username, uint64_t exchange_id);
  [[eosio::action]] void publish(eosio::name username, uint64_t exchange_id);




  //balances.cpp
  static void add_balance(eosio::name username, eosio::asset quantity,
                          eosio::name contract);
  static void sub_balance(eosio::name username, eosio::asset quantity,
                          eosio::name contract);

  
  static uint64_t get_global_id(eosio::name key) {
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

  /**
   * @struct counts
   * @brief Структура для учета глобальных идентификаторов
   */
  struct [[eosio::table, eosio::contract("marketplace")]] counts {
    eosio::name key;
    eosio::name secondary_key;
    uint64_t value;

    uint64_t primary_key() const { return key.value; } /*!< return id - primary_key */
    uint128_t keyskey() const { return combine_ids(key.value, secondary_key.value); } /*!< комбинированный secondary_key для получения курса */
    uint128_t keyvalue() const { return combine_ids(key.value, value); } /*!< комбинированный secondary_key для получения курса */
  };

  typedef eosio::multi_index<
      "counts"_n, counts,
      eosio::indexed_by<"keyskey"_n, eosio::const_mem_fun<counts, uint128_t,
                                                          &counts::keyskey>>>
      counts_index;

};
