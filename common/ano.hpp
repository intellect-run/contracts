struct [[eosio::table, eosio::contract("ano")]] coops {
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
