/**
 * @brief      Таблица хранения объектов гостей
 * @ingroup public_tables
 * @table individuals
 * @contract _me
 * @scope _me
 * @details
 */
struct [[eosio::table, eosio::contract(REGISTRATOR)]] individuals {
  eosio::name username; /*!< имя аккаунта */
  uint64_t coop_id;
  eosio::name registrator; /*!< имя аккаунта регистратора */
  std::string first_name;
  std::string second_name;
  std::string middle_name;
  std::string birthdate;
  std::string country;
  std::string city;
  std::string address;
  std::string phone;

  std::string meta;

  uint64_t primary_key() const {
    return username.value;
  } /*!< return username - primary_key */
  uint64_t by_coop() const { return coop_id; }
  uint64_t byregistr() const {
    return registrator.value;
  } /*!< return registrator - secondary_key 3 */
};

typedef eosio::multi_index<
    "individuals"_n, individuals,
    eosio::indexed_by<
        "bycoop"_n,
        eosio::const_mem_fun<individuals, uint64_t, &individuals::by_coop>>,
    eosio::indexed_by<
        "byregistr"_n,
        eosio::const_mem_fun<individuals, uint64_t, &individuals::byregistr>>>
    individuals_index;

/**
 * @brief      Таблица хранения отозванных аккаунтов гостей
 * @ingroup public_tables
 * @table newaccounts
 * @contract _me
 * @scope _me
 * @details Хранит аккаунты, отозванные у гостей путём замены их активного
 * ключа на ключ регистратора за истечением срока давности без поступления
 * оплаты.
 */
struct [[eosio::table, eosio::contract(REGISTRATOR)]] catalog {
  eosio::name username; /*!< имя аккаунта гостя */
  uint64_t coop_id;
  eosio::name status; /*!< статус аккаунта "" - никто, "member" */
  std::string nickname;
  eosio::checksum256 nickhash;
  eosio::name type;        // invidual | coorparate
  eosio::name registrator; /*!< имя аккаунта регистратора */
  eosio::name referer;
  eosio::asset payed; /*!< количество токенов к оплате */
  std::string meta;
  eosio::time_point_sec registered_at;

  uint64_t primary_key() const {
    return username.value;
  } /*!< return username - primary_key */
  uint64_t by_coop() const { return coop_id; }
  uint64_t by_referer() const { return referer.value; }
  uint64_t by_amount() const { return payed.amount; }
  uint64_t by_type() const { return type.value; }
  uint64_t by_status() const { return status.value; }
  uint64_t by_registr() const { return registrator.value; }

  eosio::checksum256 bynickhash() const { return nickhash; }
};

typedef eosio::multi_index<
    "catalog"_n, catalog,
    eosio::indexed_by<"bycoop"_n, eosio::const_mem_fun<catalog, uint64_t,
                                                       &catalog::by_coop>>,
    eosio::indexed_by<
        "byreferer"_n,
        eosio::const_mem_fun<catalog, uint64_t, &catalog::by_referer>>,
    eosio::indexed_by<"bytype"_n, eosio::const_mem_fun<catalog, uint64_t,
                                                       &catalog::by_type>>,
    eosio::indexed_by<
        "bystatus"_n,
        eosio::const_mem_fun<catalog, uint64_t, &catalog::by_status>>,
    eosio::indexed_by<
        "byregistr"_n,
        eosio::const_mem_fun<catalog, uint64_t, &catalog::by_registr>>,
    eosio::indexed_by<
        "byamount"_n,
        eosio::const_mem_fun<catalog, uint64_t, &catalog::by_amount>>,
    eosio::indexed_by<"bynickhash"_n,
                      eosio::const_mem_fun<catalog, eosio::checksum256,
                                           &catalog::bynickhash>>

    >
    catalog_index;


