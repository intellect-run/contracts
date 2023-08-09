#pragma once

#include <eosio/binary_extension.hpp>
#include <eosio/eosio.hpp>
#include <eosio/ignore.hpp>
#include <eosio/transaction.hpp>
#include <eosio/asset.hpp>
#include <eosio/singleton.hpp>

static constexpr eosio::name _me = "soviet"_n;             /*!< собственное имя аккаунта контракта */
  

namespace eosio {
class [[eosio::contract("soviet")]] soviet : public contract {
public:
  using contract::contract;
  
  [[eosio::action]] void createboard(eosio::name chairman, std::vector<eosio::name> members, uint64_t expired_after_days);
  [[eosio::action]] void addadmin(eosio::name chairman, eosio::name username, std::vector<eosio::name> rights);
  [[eosio::action]] void rmadmin(eosio::name chairman, eosio::name username);
  [[eosio::action]] void setadmrights(eosio::name chairman, eosio::name username, std::vector<eosio::name> rights);


  
  [[eosio::action]] void propose();
  [[eosio::action]] void approve();
  [[eosio::action]] void unapprove();
  [[eosio::action]] void cancel();
  [[eosio::action]] void exec();
  [[eosio::action]] void invalidate();
  
  using create_board_action = eosio::action_wrapper<"createboard"_n, &soviet::createboard>;  
  using propose_action = eosio::action_wrapper<"propose"_n, &soviet::propose>;
  using approve_action = eosio::action_wrapper<"approve"_n, &soviet::approve>;
  using unapprove_action =
      eosio::action_wrapper<"unapprove"_n, &soviet::unapprove>;
  using cancel_action = eosio::action_wrapper<"cancel"_n, &soviet::cancel>;
  using exec_action = eosio::action_wrapper<"exec"_n, &soviet::exec>;
  using invalidate_action =
      eosio::action_wrapper<"invalidate"_n, &soviet::invalidate>;

  
  struct [[eosio::table, eosio::contract("soviet")]] proposal {
    uint64_t id;
    name type;
    name proposer;

    uint64_t primary_key() const { return id; }
  };

  typedef eosio::multi_index<"proposal"_n, proposal> proposals_index;


  struct [[eosio::table, eosio::contract("soviet")]] boards {
    uint64_t id;
    eosio::time_point_sec created_at;
    eosio::time_point_sec expired_at;
    
    eosio::name chairman;
    std::vector<eosio::name> members;

    uint64_t primary_key() const { return id; }
      
  };

  typedef eosio::multi_index< "boards"_n, boards > board_index;



  struct [[eosio::table, eosio::contract("soviet")]] admins {
    eosio::name username;
    std::vector<eosio::name> rights;

    uint64_t primary_key() const { return username.value; }
      
  };

  typedef eosio::multi_index< "admins"_n, admins > admin_index;



};
}