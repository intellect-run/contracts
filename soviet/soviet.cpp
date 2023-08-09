#include "soviet.hpp"
#include <eosio/action.hpp>
#include <eosio/crypto.hpp>
#include <eosio/permission.hpp>

using namespace eosio;

void soviet::propose() { 
  // require_auth(); 

}

void soviet::approve() { 
  // require_auth(); 

}

void soviet::unapprove() { 
  // require_auth(); 

}

void soviet::cancel() { 
  // require_auth(); 

}

void soviet::exec() { 
  // require_auth(); 

}

void soviet::invalidate() { 
  // require_auth(); 

}


void soviet::createboard(eosio::name chairman, std::vector<eosio::name> members, uint64_t expired_after_days){
  require_auth(chairman);

  board_index boards(_me, _me.value);

  auto begin = boards.begin();
  eosio::check(begin == boards.end(), "Совет еще не создан");

  boards.emplace(chairman, [&](auto &b){
    b.id = boards.available_primary_key();
    b.members = members;
    b.created_at = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
    b.expired_at = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch() + expired_after_days * 86400);
  });
}


void soviet::addadmin(eosio::name chairman, eosio::name username, std::vector<eosio::name> rights) {
  require_auth(chairman);

  admin_index admins(_me, _me.value);
  board_index boards(_me, _me.value);

  auto board = boards.find(0);
  eosio::check(board != boards.end(), "Совет еще не создан");
  eosio::check(board -> chairman == chairman, "Вы не председатель, чтобы добавлять админов!");

  admins.emplace(chairman, [&](auto &a){
    a.username = username;
    a.rights = rights;
  });

};

void soviet::rmadmin(eosio::name chairman, eosio::name username) {
  require_auth(chairman);

  admin_index admins(_me, _me.value);
  board_index boards(_me, _me.value);

  auto board = boards.find(0);
  eosio::check(board != boards.end(), "Совет еще не создан");
  eosio::check(board -> chairman == chairman, "Вы не председатель, чтобы удалять админов!");
  
  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "Администратор не найден");

  admins.erase(admin);

};

void soviet::setadmrights(eosio::name chairman, eosio::name username, std::vector<eosio::name> rights) {
  require_auth(chairman);

  admin_index admins(_me, _me.value);
  board_index boards(_me, _me.value);

  auto board = boards.find(0);
  eosio::check(board != boards.end(), "Совет еще не создан");
  eosio::check(board -> chairman == chairman, "Только председатель может изменять права администраторов");

  auto admin = admins.find(username.value);
  eosio::check(admin != admins.end(), "Администратор не найден");

  admins.modify(admin, chairman, [&](auto &a){
    a.rights = rights;
  });  
};
  



extern "C" {

  /// The apply method implements the dispatch of events to this contract
  void apply(uint64_t receiver, uint64_t code, uint64_t action) {

    if (code == _me.value) {
      switch (action) {

        EOSIO_DISPATCH_HELPER(
            soviet, (propose)(approve)(unapprove)(cancel)(exec)(invalidate)(createboard))
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
        
          eosio::check(false, "Совет не принимает взятки :))");
          
        }
      }
    }
  };

};
