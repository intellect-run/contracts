#pragma once

#include <eosio/binary_extension.hpp>
#include <eosio/eosio.hpp>
#include <eosio/ignore.hpp>
#include <eosio/transaction.hpp>
#include <eosio/asset.hpp>
#include <eosio/singleton.hpp>

static constexpr eosio::name _me = "soviet"_n;             /*!< собственное имя аккаунта контракта */
static constexpr eosio::name _registrator = "registrator"_n;  /*!< имя аккаунта контракта регистратора */
static constexpr eosio::name _marketplace = "marketplace"_n; /*!< имя аккаунта контракта маркетплейса */

static constexpr eosio::name _REGACCOUNT = "regaccount"_n;  /*!< код имени действия на регистрацию */
static constexpr eosio::name _CHANGE = "change"_n;  /*!< код имени действия на регистрацию */

static constexpr eosio::name _chairman = "chairman"_n;  /*!< имя аккаунта председателя */


namespace eosio {
class [[eosio::contract("soviet")]] soviet : public contract {
public:
  using contract::contract;
  
  static uint128_t combine_ids(const uint64_t &x, const uint64_t &y) {
    return (uint128_t{x} << 64) | y;
  };

  uint64_t get_global_id(eosio::name key);

  //sovet.cpp
  [[eosio::action]] void exec(eosio::name executer, uint64_t decision_id);
  [[eosio::action]] void newid(uint64_t id);
  

  //admin.cpp
  [[eosio::action]] void addadmin(eosio::name chairman, eosio::name username, std::vector<eosio::name> rights, std::string meta);
  [[eosio::action]] void rmadmin(eosio::name chairman, eosio::name username);
  [[eosio::action]] void setadmrights(eosio::name chairman, eosio::name username, std::vector<eosio::name> rights);
  [[eosio::action]] void validate(eosio::name username, uint64_t decision_id);
  
  //regaccount.cpp
  [[eosio::action]] void regaccount(eosio::name username);
  
  static void regaccount_effect(eosio::name executer, uint64_t decision_id, eosio::name username);

  //automator.cpp
  [[eosio::action]] void automate(eosio::name member, eosio::name action_type, eosio::name provider, std::string private_key);
  [[eosio::action]] void disautomate(eosio::name member, uint64_t automation_id );
  
  //chairman.cpp
  [[eosio::action]] void authorize(eosio::name chairman, uint64_t decision_id);
  [[eosio::action]] void createboard(eosio::name chairman, std::vector<eosio::name> members, uint64_t expired_after_days);
  static uint64_t get_members_count(uint64_t board_id);
  static uint64_t get_consensus_percent(uint64_t board_id);
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
  

  struct [[eosio::table, eosio::contract("soviet")]] counts {
    eosio::name key;
    eosio::name secondary_key;
    uint64_t value;

    uint64_t primary_key() const {
      return key.value;
    } /*!< return id - primary_key */
    uint128_t keyskey() const {
      return soviet::combine_ids(key.value, secondary_key.value);
    } /*!< (contract, blocked_now.symbol) - комбинированный secondary_key для
         получения курса по имени выходного контракта и символу */
    uint128_t keyvalue() const {
      return soviet::combine_ids(key.value, value);
    } /*!< (contract, blocked_now.symbol) - комбинированный secondary_key для
         получения курса по имени выходного контракта и символу */
  };

  typedef eosio::multi_index<
      "counts"_n, counts,
      eosio::indexed_by<"keyskey"_n, eosio::const_mem_fun<counts, uint128_t,
                                                          &counts::keyskey>>>
      counts_index;


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
    std::string meta;

    uint64_t primary_key() const { return username.value; }
      
  };

  typedef eosio::multi_index< "admins"_n, admins > admin_index;



  struct [[eosio::table, eosio::contract("soviet")]] decisions {
    uint64_t id;
    uint64_t board_id;
    eosio::name type; // openproposal | +regaccount | change | contribute | withdraw
    uint64_t secondary_id;

    std::vector<eosio::name> votes_for;
    std::vector<eosio::name> votes_against;
    
    bool approved = false;   //сигнальный флаг, что решение советом принято
    bool validated = false;   //сигнальный флаг, что администратор подтверждает валидность
    bool authorized = false; //получена авторизация председателя после голосования и валидации до исполнения
    bool executed = false;   //исполнять будем отдельным действием для торжественности момента

    uint64_t primary_key() const { return id; }
    
    uint64_t bysecondary() const { return secondary_id; }
    uint64_t bytype() const { return type.value; }

    uint64_t byapproved() const { return approved; }
    uint64_t byvalidated() const { return validated; }
    uint64_t byauthorized() const { return authorized; }
    uint64_t byexecuted() const { return executed; }
  };

  typedef eosio::multi_index< "decisions"_n, decisions,
    eosio::indexed_by<"bysecondary"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::bysecondary>>,
    eosio::indexed_by<"bytype"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::bytype>>,
    eosio::indexed_by<"byapproved"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::byapproved>>,
    eosio::indexed_by<"byvalidated"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::byvalidated>>,
    eosio::indexed_by<"byauthorized"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::byauthorized>>,
    eosio::indexed_by<"byexecuted"_n, eosio::const_mem_fun<decisions, uint64_t, &decisions::byexecuted>>
  > decision_index;


  struct [[eosio::table, eosio::contract("soviet")]] automator {
    uint64_t id;
    eosio::name member;
    eosio::name action_type;
    eosio::name provider;
    std::string private_key;

    uint64_t primary_key() const { return id; }
    uint128_t by_member_and_action_type() const { return soviet::combine_ids(member.value, action_type.value); }
    uint64_t by_action() const { return action_type.value; }

  };

  typedef eosio::multi_index< "automator"_n, automator,
    eosio::indexed_by<"byaction"_n, eosio::const_mem_fun<automator, uint64_t, &automator::by_action>>,
    eosio::indexed_by<"bymembaction"_n, eosio::const_mem_fun<automator, uint128_t, &automator::by_member_and_action_type>>
  > automator_index;


  struct [[eosio::table, eosio::contract("soviet")]] oracle {
    uint64_t id;
    
    uint64_t primary_key() const { return id; }    
  };

  typedef eosio::multi_index< "oracle"_n, oracle> oracle_index;

}