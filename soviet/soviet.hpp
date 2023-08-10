#pragma once

#include <eosio/binary_extension.hpp>
#include <eosio/eosio.hpp>
#include <eosio/ignore.hpp>
#include <eosio/transaction.hpp>
#include <eosio/asset.hpp>
#include <eosio/singleton.hpp>

static constexpr eosio::name _me = "soviet"_n;             /*!< собственное имя аккаунта контракта */
static constexpr eosio::name _registrator = "registrator"_n;  /*!< имя аккаунта контракта регистратора */
static constexpr eosio::name _REGACCOUNT = "regaccount"_n;  /*!< код имени действия на регистрацию */


namespace eosio {
class [[eosio::contract("soviet")]] soviet : public contract {
public:
  using contract::contract;
  
  //sovet.cpp
  [[eosio::action]] void exec(eosio::name executer, uint64_t decision_id);
  using exec_action = eosio::action_wrapper<"exec"_n, &soviet::exec>;
  
  //admin.cpp
  [[eosio::action]] void addadmin(eosio::name chairman, eosio::name username, std::vector<eosio::name> rights);
  using addadmin_action = eosio::action_wrapper<"addadmin"_n, &soviet::addadmin>;  
  [[eosio::action]] void rmadmin(eosio::name chairman, eosio::name username);
  using rmadmin_action = eosio::action_wrapper<"rmadmin"_n, &soviet::rmadmin>;  
  [[eosio::action]] void setadmrights(eosio::name chairman, eosio::name username, std::vector<eosio::name> rights);
  using setadmrights_action = eosio::action_wrapper<"setadmrights"_n, &soviet::setadmrights>;  
  [[eosio::action]] void validate(eosio::name username, uint64_t decision_id);
  using validate_action = eosio::action_wrapper<"validate"_n, &soviet::validate>;  

  //regaccount.cpp
  [[eosio::action]] void regaccount(eosio::name username);
  using regaccount_action = eosio::action_wrapper<"regaccount"_n, &soviet::regaccount>;

  static void regaccount_effect(eosio::name executer, uint64_t decision_id, eosio::name username);

  //automator.cpp
  [[eosio::action]] void automate(eosio::name member, eosio::name action_type);
  using automate_action = eosio::action_wrapper<"automate"_n, &soviet::automate>;  
  [[eosio::action]] void disautomate(eosio::name member, uint64_t automation_id );
  using disautomate_action = eosio::action_wrapper<"disautomate"_n, &soviet::disautomate>;  
  static void check_and_sign_by_chairman(eosio::name action_type, uint64_t decision_id);
  static void check_and_sign_by_members(eosio::name action_type, uint64_t decision_id);

  //chairman.cpp
  [[eosio::action]] void authorize(eosio::name chairman, uint64_t decision_id);
  using authorize_action = eosio::action_wrapper<"authorize"_n, &soviet::authorize>;  
  [[eosio::action]] void createboard(eosio::name chairman, std::vector<eosio::name> members, uint64_t expired_after_days);
  using create_board_action = eosio::action_wrapper<"createboard"_n, &soviet::createboard>;  
  
  [[eosio::action]] void autochair(eosio::name chairman, eosio::name action_type);
  using autochair_action = eosio::action_wrapper<"autochair"_n, &soviet::autochair>;  
  [[eosio::action]] void disautochair(eosio::name chairman, eosio::name action_type);
  using disautochair_action = eosio::action_wrapper<"disautochair"_n, &soviet::disautochair>;  

  static uint64_t get_members_count(uint64_t board_id);
  static uint64_t get_consensus_percent(uint64_t board_id);
  static void is_valid_member(eosio::name member);
  static void is_valid_chairman(eosio::name chairman);
  static void is_valid_action(eosio::name action_type);

  //voting.cpp
  [[eosio::action]] void votefor(eosio::name member, uint64_t decision_id);
  [[eosio::action]] void voteagainst(eosio::name member, uint64_t decision_id);
  [[eosio::action]] void cancelvote(eosio::name member, uint64_t decision_id);

};


  struct [[eosio::table, eosio::contract("soviet")]] boards {
    uint64_t id;
    eosio::time_point_sec created_at;
    eosio::time_point_sec expired_at;
    
    uint64_t consensus = 50;
    eosio::name chairman;
    std::vector<eosio::name> members;

    uint64_t primary_key() const { return id; }
    uint64_t bychairman() const { return chairman.value; }
        
  };

  typedef eosio::multi_index< "boards"_n, boards,
    eosio::indexed_by< "bychairman"_n, eosio::const_mem_fun<boards, uint64_t, &boards::bychairman>>
   > board_index;



  struct [[eosio::table, eosio::contract("soviet")]] admins {
    eosio::name username;
    std::vector<eosio::name> rights;

    uint64_t primary_key() const { return username.value; }
      
  };

  typedef eosio::multi_index< "admins"_n, admins > admin_index;



  struct [[eosio::table, eosio::contract("soviet")]] decisions {
    uint64_t id;
    uint64_t board_id;
    eosio::name type; // openproposal | +regaccount | exchange | contribute | withdraw
    uint64_t secondary_id;

    std::vector<eosio::name> votes_for;
    std::vector<eosio::name> votes_against;
    
    bool approved = false;   //сигнальный флаг, что решение советом принято
    bool validated = false;   //сигнальный флаг, что администратор подтверждает валидность
    bool authorized = false; //получена авторизация председателя после голосования и валидации до исполнения
    bool executed = false;   //исполнять будем отдельным действием для торжественности момента

    uint64_t primary_key() const { return id; }
      
  };

  typedef eosio::multi_index< "decisions"_n, decisions > decision_index;


  struct [[eosio::table, eosio::contract("soviet")]] automator {
    uint64_t id;
    eosio::name member;
    eosio::name action_type;

    uint64_t primary_key() const { return id; }
    uint64_t by_action() const { return action_type.value; }
  };

  typedef eosio::multi_index< "automator"_n, automator,
    eosio::indexed_by<"byaction"_n, eosio::const_mem_fun<automator, uint64_t, &automator::by_action>>
  > automator_index;


  struct [[eosio::table, eosio::contract("soviet")]] autochair {
    eosio::name action_type;
    
    uint64_t primary_key() const { return action_type.value; }    
  };

  typedef eosio::multi_index< "autochair"_n, autochair> autochair_index;

}