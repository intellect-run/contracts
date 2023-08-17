#include <eosio/action.hpp>
#include <eosio/crypto.hpp>
#include <eosio/permission.hpp>

#include "soviet.hpp"

#include "src/admin.cpp"
#include "src/chairman.cpp"
#include "src/regaccount.cpp"
#include "src/voting.cpp"
#include "src/automator.cpp"
#include "src/marketplace.cpp"

using namespace eosio;


void soviet::exec(eosio::name executer, uint64_t decision_id) { 
  require_auth(executer);

  decision_index decisions(_me, _me.value);
  auto decision = decisions.find(decision_id);
  eosio::check(decision != decisions.end(),"Решение не найдено в оперативной памяти");
  eosio::check(decision -> authorized == true, "Только авторизованное решение может быть выполнено");
  eosio::check(decision -> executed == false, "Решение уже исполнено");

  if (decision -> type == _REGACCOUNT) {
    soviet::regaccount_effect(executer, decision->id, name(decision->secondary_id));
  } else if (decision -> type == _CHANGE){
    soviet::change_effect(executer, decision->id, name(decision->secondary_id));
  }
}



extern "C" {

  /// The apply method implements the dispatch of events to this contract
  void apply(uint64_t receiver, uint64_t code, uint64_t action) {

    if (code == _me.value) {
      
      switch (action) {

        EOSIO_DISPATCH_HELPER (
            soviet, 
            //main
            (exec)
            //ADMIN
            (addadmin)(rmadmin)(setadmrights)(validate)
            //CHAIRMAN
            (authorize)(createboard)
            //VOTING
            (votefor)(voteagainst)(cancelvote)
            //REGACCOUNT
            (regaccount)
            //MARKETPLACE
            (change)
            //AUTOMATOR
            (automate)(disautomate)(autochair)(disautochair)
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
        
        if (op.to == _me) {
        
          eosio::check(false, "Совет не принимает взятки (входящие переводы) :))");
          
        }
      }
    }
  };

};
