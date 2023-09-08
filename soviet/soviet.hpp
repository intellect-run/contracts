#pragma once

#include <eosio/binary_extension.hpp>
#include <eosio/eosio.hpp>
#include <eosio/ignore.hpp>
#include <eosio/transaction.hpp>
#include <eosio/asset.hpp>
#include <eosio/singleton.hpp>

#include "../common/consts.hpp"
#include "../common/utils.hpp"
#include "../common/soviet.hpp"
#include "../common/coops.hpp"
#include "../common/counts.hpp"
#include "../common/admins.hpp"

static constexpr eosio::name _chairman = "chairman"_n;  /*!< имя аккаунта председателя */

namespace eosio {
class [[eosio::contract(SOVIET)]] soviet : public contract {
public:
  using contract::contract;
   //sovet.cpp
  [[eosio::action]] void exec(eosio::name executer, uint64_t decision_id);
  [[eosio::action]] void newid(uint64_t decision_id);
  

  //admin.cpp
  [[eosio::action]] void addadmin(uint64_t union_id, eosio::name chairman, eosio::name username, std::vector<eosio::name> rights, std::string meta);
  [[eosio::action]] void rmadmin(uint64_t union_id, eosio::name chairman, eosio::name username);
  [[eosio::action]] void setadmrights(uint64_t union_id, eosio::name chairman, eosio::name username, std::vector<eosio::name> rights);
  [[eosio::action]] void validate(uint64_t union_id, eosio::name username, uint64_t decision_id);
  
  //regaccount.cpp
  [[eosio::action]] void regaccount(eosio::name username);
  
  static void regaccount_effect(eosio::name executer, uint64_t decision_id, eosio::name username);

  //automator.cpp
  [[eosio::action]] void automate(eosio::name member, eosio::name action_type, eosio::name provider, std::string private_key);
  [[eosio::action]] void disautomate(eosio::name member, uint64_t automation_id );
  
  //chairman.cpp
  [[eosio::action]] void authorize(eosio::name chairman, uint64_t decision_id);
  [[eosio::action]] void createunion(uint64_t coop_id, uint64_t parent_id, eosio::name chairman, std::vector<eosio::name> members);
  static uint64_t get_members_count(uint64_t union_id);
  
  static void is_valid_member(eosio::name member);
  static void is_valid_chairman(eosio::name chairman);
  static void is_valid_action(eosio::name action_type);

  //voting.cpp
  [[eosio::action]] void votefor(eosio::name member, uint64_t decision_id);
  [[eosio::action]] void voteagainst(eosio::name member, uint64_t decision_id);
  [[eosio::action]] void cancelvote(eosio::name member, uint64_t decision_id);

  //marketplace.cpp
  [[eosio::action]] void change(uint64_t order_id);
  static void change_effect(eosio::name executer, uint64_t decision_id, eosio::name username);

};
  

  struct [[eosio::table, eosio::contract(SOVIET)]] counts : counts_base {};
 
  struct [[eosio::table, eosio::contract(SOVIET)]] automator {
    uint64_t id;
    eosio::name member;
    eosio::name action_type;
    eosio::name provider;
    std::string private_key;

    uint64_t primary_key() const { return id; }
    uint128_t by_member_and_action_type() const { return combine_ids(member.value, action_type.value); }
    uint64_t by_action() const { return action_type.value; }

  };

  typedef eosio::multi_index< "automator"_n, automator,
    eosio::indexed_by<"byaction"_n, eosio::const_mem_fun<automator, uint64_t, &automator::by_action>>,
    eosio::indexed_by<"bymembaction"_n, eosio::const_mem_fun<automator, uint128_t, &automator::by_member_and_action_type>>
  > automator_index;


  struct [[eosio::table, eosio::contract(SOVIET)]] oracle {
    uint64_t id;
    
    uint64_t primary_key() const { return id; }    
  };

  typedef eosio::multi_index< "oracle"_n, oracle> oracle_index;

}
