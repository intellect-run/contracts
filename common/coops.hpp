#pragma once

struct [[eosio::table, eosio::contract(ANO)]] coops {
  uint64_t id;
  eosio::name system_name;
  eosio::name status;
  eosio::name chairman;
  eosio::name registrator;
  std::string data;
  std::string message;

  uint64_t primary_key() const {
    return id;
  };
};

typedef eosio::multi_index<"coops"_n, coops> coops_index;

struct [[eosio::table, eosio::contract(SOVIET)]] decisions {
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
 
struct [[eosio::table, eosio::contract(SOVIET)]] unions {
  uint64_t id;
  uint64_t parent_id;
  eosio::name chairman;
  std::vector<eosio::name> members;
  eosio::time_point_sec created_at;
  
  uint64_t primary_key() const { return id; }
  uint64_t bychairman() const { return chairman.value; }
      
};

typedef eosio::multi_index< "unions"_n, unions,
  eosio::indexed_by< "bychairman"_n, eosio::const_mem_fun<unions, uint64_t, &unions::bychairman>>
 > union_index;



