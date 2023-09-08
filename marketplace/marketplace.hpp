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

#include "../common/consts.hpp"
#include "../common/utils.hpp"
#include "../common/admins.hpp"
#include "../common/counts.hpp"
#include "../common/balances.hpp"
#include "../common/marketplace.hpp"

       
/**
 * @class marketplace
 * @brief Основной класс контракта "marketplace"
 *
 * Включает в себя методы для работы с заявками на обмен, управления балансами и административные действия.
 */        
class [[eosio::contract("MARKETPLACE")]] marketplace : public eosio::contract {

public:
  /**
   * @brief Конструктор контракта "marketplace"
   */
  marketplace(eosio::name receiver, eosio::name code,
              eosio::datastream<const char *> ds)
      : eosio::contract(receiver, code, ds){}

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

  struct [[eosio::table, eosio::contract("marketplace")]] balances : balances_base {};
  struct [[eosio::table, eosio::contract("marketplace")]] counts : counts_base {};

};
