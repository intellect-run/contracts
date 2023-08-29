/**
 * @file marketplace.cpp
 * @brief Основной файл реализации контракта "marketplace"
 *
 * Этот файл включает в себя основную реализацию контракта "marketplace", включая обработку событий и логику управления токенами.
 * Здесь загружаются все необходимые файлы и определяются действия, которые контракт может выполнять.
 *
 * @include "marketplace.hpp"
 * @include "src/soviet.cpp"
 * @include "src/balances.cpp"
 * @include "src/admins.cpp"
 * @include "src/change.cpp"
 */


#include "marketplace.hpp"
#include <eosio/transaction.hpp>

#include "src/soviet.cpp"
#include "src/balances.cpp"
#include "src/admins.cpp"
#include "src/change.cpp"

using namespace eosio;

/*!
  \mainpage Контракт "marketplace"

  \section Описание

  Контракт "marketplace" представляет собой платформу обмена в кооперативной среде. Обмен производится в соответствии с требованиями законодательства ФЗ-3085-1 "О Потребительской Кооперации".

  \section Структура Контракта

  Контракт состоит из следующих компонентов:

  \subsection Структуры

  - `balance`: Описывает баланс пользователя.
  - `exchange`: Описывает информацию об обмене.
  - `exchange_params`: Параметры обмена, включая имя пользователя, контракт, количество единиц, цену за штуку и дополнительные данные и метаданные.

  \subsection Действия

  Контракт включает в себя следующие действия:

  - **Действия обмена**: `offer`, `order`, `complete`, `decline`, `accept`.
  - **Административные действия**: `moderate`, `prohibit`, `unpublish`, `publish`.
  - **Действия авторизации**: `authorize`.
  - **Действия управления балансом**: `add_balance`, `sub_balance`.
  - **Прочие действия**: `newid` (используется для возврата информации из контракта), `update`, `addpieces`.

  \section Использование

  \subsection Установка

  Для развертывания контракта следуйте стандартной процедуре развертывания контрактов EOSIO.

  \subsection Интеграция

  Взаимодействие с контрактом осуществляется через стандартный интерфейс EOSIO, с использованием соответствующих действий.

  \section Лицензия

  MIT

  \section Поддержка

  Для получения поддержки, пожалуйста, обращайтесь к [ссылка на контактные данные].
*/


/**
 * @brief Пустой метод регистрации нового идентификатора
 *
 * Этот метод используется для возврата информации из контракта.
 *
 * @param id идентификатор
 * @param type тип идентификатора
 */
[[eosio::action]] void marketplace::newid(uint64_t id, eosio::name type) {
  require_auth(_me);
};


extern "C" {

/// Метод apply реализует диспетчеризацию событий для этого контракта
void apply(uint64_t receiver, uint64_t code, uint64_t action) {
  if (code == _me.value) {
    switch (action) {
      EOSIO_DISPATCH_HELPER(marketplace, (newid)
        //change
        (offer)(order)(complete)(decline)(accept)
        //admin
        (moderate)(prohibit)(unpublish)(publish)
        //soviet
        (authorize)

      )
    }
  } else {
    if (action == "transfer"_n.value) {
      struct transfer {
        eosio::name from;
        eosio::name to;
        eosio::asset quantity;
        std::string memo;
      };

      auto op = eosio::unpack_action_data<transfer>();
      // Если перевод направлен на аккаунт контракта, обновляем баланс
      if (op.to == _me) {
        marketplace::add_balance(op.from, op.quantity, eosio::name(code));
      }
    }
  }
};
};
