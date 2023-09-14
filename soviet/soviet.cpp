#include <eosio/action.hpp>
#include <eosio/crypto.hpp>
#include <eosio/permission.hpp>
#include "soviet.hpp"
#include "src/admin.cpp"
#include "src/chairman.cpp"
#include "src/joincoop.cpp"
#include "src/voting.cpp"
#include "src/automator.cpp"
#include "src/marketplace.cpp"

using namespace eosio;

[[eosio::action]] void soviet::newid(uint64_t decision_id) {
  require_auth(_soviet);
};

/**
\ingroup public_actions
\brief Исполнение решения совета
*
* Этот метод позволяет исполнить решение совета. Исполнение решения включает в себя проверку, что решение существует, что оно было авторизовано, и что оно еще не было выполнено. В зависимости от типа решения, вызывается соответствующая функция для его реализации.
*
* @param executer Имя аккаунта, который исполняет решение
* @param coop_username Имя кооператива
* @param decision_id Идентификатор решения для исполнения
* 
* @note Авторизация требуется от аккаунта: @p executer
*/
void soviet::exec(eosio::name executer, eosio::name coop_username, uint64_t decision_id) { 
  require_auth(executer);

  decisions_index decisions(_soviet, _soviet.value);
  auto decision = decisions.find(decision_id);
  eosio::check(decision != decisions.end(),"Решение не найдено в оперативной памяти");
  eosio::check(decision -> authorized == true, "Только авторизованное решение может быть выполнено");
  eosio::check(decision -> executed == false, "Решение уже исполнено");

  if (decision -> type == _regaccount_action) {
    soviet::joincoop_effect(executer, coop_username, decision->id, decision->card_id);
  } else if (decision -> type == _change_action){
    soviet::change_effect(executer, coop_username, decision->id, decision->card_id);
  }
}

extern "C" {

  /// The apply method implements the dispatch of events to this contract
  void apply(uint64_t receiver, uint64_t code, uint64_t action) {

    if (code == _soviet.value) {
      switch (action) {

        EOSIO_DISPATCH_HELPER (
            soviet, 
            //main
            (exec)(newid)
            //ADMIN
            (addstaff)(rmstaff)(setrights)(validate)
            //CHAIRMAN
            (authorize)(createboard)
            //VOTING
            (votefor)(voteagainst)(cancelvote)
            //REGACCOUNT
            (joincoop)
            //MARKETPLACE
            (change)
            //AUTOMATOR
            (automate)(disautomate)
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
        if (op.to == _soviet) {
          eosio::check(false, "Совет не принимает взятки (входящие переводы) :))");
        }
      }
    }
  };

};
