struct [[eosio::table, eosio::contract(DRAFT)]] drafts {
  uint64_t id;
  eosio::name lang;
  eosio::name action_name;
  std::string name;
  std::string description;
  std::string context;
  std::string data;
  bool is_active;
  bool is_approved;
  bool is_standart;
  eosio::time_point_sec created_at;
  eosio::time_point_sec last_update;
  uint64_t doc_version;

  uint64_t primary_key() const { return id; };

  uint64_t by_action() const { return action_name.value; };

  uint128_t by_action_lang() const {
    return combine_ids(action_name.value, lang.value);
  };
};

typedef eosio::multi_index<
    "drafts"_n, drafts,
    eosio::indexed_by<"byaction"_n, eosio::const_mem_fun<drafts, uint64_t,
                                                         &drafts::by_action>>,
    eosio::indexed_by<
        "byactionlang"_n,
        eosio::const_mem_fun<drafts, uint128_t, &drafts::by_action_lang>>>
    drafts_index;


