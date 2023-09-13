
struct verification {
  eosio::name verificator; //организация, которая произвела верификацию 
  bool is_verified;
  uint64_t procedure;
    // (0, _('online')),
    // (1, _('video call')),
    // (2, _('qualified signature')),
    // (3, _('gosuslugi')),
    // (4, _('app')),		-  с помощью мобильного приложения
    // (5, _('agent store')),   	- некоторые платежные системы 
    // проводят верификацию в Связном
    // (6, _('bank')),		- верификация в банке
    // (7, _('in person')),	- верификация в кооперативе
  eosio::time_point_sec created_at;
  eosio::time_point_sec last_update;
  std::string notice;
};


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
struct [[eosio::table, eosio::contract(REGISTRATOR)]] accounts {
  eosio::name username; /*!< имя аккаунта гостя */
  eosio::name status; /*!< статус аккаунта:
  "pending" - ожидание утверждения советом, 
  "active" - активный аккаунт;
  "blocked" - заблокированный аккаунт;
  "deleted" - удален пользователем;
  */
  uint64_t reputation;
  std::string uid;
  eosio::checksum256 uid_hash;
  eosio::name type;        // user | org
  eosio::name registrator; /*!< имя аккаунта регистратора */
  eosio::name referer;
  
  eosio::asset registration_amount; /*!< количество токенов к оплате */
  std::string meta;
  eosio::time_point_sec registered_at;
  eosio::time_point_sec last_update;
  eosio::time_point_sec signature_expires_at;
  eosio::time_point_sec signature_last_update; 
 
  uint64_t primary_key() const {
    return username.value;
  } /*!< return username - primary_key */
  uint64_t by_referer() const { return referer.value; }
  uint64_t by_type() const { return type.value; }
  uint64_t by_status() const { return status.value; }
  uint64_t by_registr() const { return registrator.value; }
  eosio::checksum256 byuidhash() const { return uid_hash; }
};

typedef eosio::multi_index<
    "accounts"_n, accounts,
    eosio::indexed_by<
        "byreferer"_n,
        eosio::const_mem_fun<accounts, uint64_t, &accounts::by_referer>>,
    eosio::indexed_by<"bytype"_n, eosio::const_mem_fun<accounts, uint64_t,
                                                       &accounts::by_type>>,
    eosio::indexed_by<
        "bystatus"_n,
        eosio::const_mem_fun<accounts, uint64_t, &accounts::by_status>>,
    eosio::indexed_by<
        "byregistr"_n,
        eosio::const_mem_fun<accounts, uint64_t, &accounts::by_registr>>,
    eosio::indexed_by<"byuidhash"_n,
                      eosio::const_mem_fun<accounts, eosio::checksum256,
                                           &accounts::byuidhash>>>
    accounts_index;

/**
 * @brief      Таблица хранения объектов гостей
 * @ingroup public_tables
 * @table individuals
 * @contract _me
 * @scope _me
 * @details
 */
struct [[eosio::table, eosio::contract(REGISTRATOR)]] users {
  eosio::name username; /*!< имя аккаунта */
  std::string profile; 

  verification verification;
  uint64_t primary_key() const {
    return username.value;
  } /*!< return username - primary_key */
  uint64_t by_verified() const {
    return verification.is_verified == true ? 1 : 0;
  }
};

typedef eosio::multi_index<"users"_n, users,
  eosio::indexed_by<"byverif"_n, eosio::const_mem_fun<users, uint64_t,
                                                       &users::by_verified>>
> users_index;

struct bank {
  std::string account; //Номер расчётного счёта
  eosio::time_point_sec created_at;
  eosio::time_point_sec last_update;
  bool is_active;
};

struct new_org_struct {
  eosio::name username;
  uint64_t coop_id;

  std::string name; //Полное наименование
  std::string short_name; //Краткое наименование;
  std::string address; //юридический адрес;
  std::string ogrn;
  std::string inn;
  std::string logo;
  std::string phone;
  std::string email;
  std::string registration; //дата регистрации юрлица
  std::string website;
  std::vector <bank> accounts;
  bool is_cooperative = false;
  std::optional<eosio::name> coop_type;
  std::optional<eosio::name> token_contract;
  std::optional<std::string> slug; 
  std::optional<std::string> announce;
  std::optional<std::string> description;
  std::optional<uint64_t> members;
  std::optional<eosio::asset> initial;//Вступительный взнос
  std::optional<eosio::asset> minimum;//Минимальный взнос
  std::optional<eosio::asset> membership;//Членский взнос
  std::optional<eosio::name> period;//Периодичность
  //  (0, _('per case')), 	 - зависит от программы
	// (1, _('daily')),
	// (2, _('weekly')),
	// (3, _('monthly')),
	// (4, _('quarterly')),
	// (5, _('half a year')),
	// (6, _('annually')),
	// (7, _('onetime')),

}; 



struct [[eosio::table, eosio::contract(REGISTRATOR)]] orgs {
  eosio::name username;
  eosio::name parent_username;
  verification verification;
  std::string name; //Полное наименование
  std::string short_name; //Краткое наименование;
  std::string address; //юридический адрес;
  std::string ogrn;
  std::string inn;
  std::string logo;
  std::string phone;
  std::string email;
  std::string registration; //дата регистрации юрлица
  std::string website;
  std::vector <bank> accounts;
  bool is_cooperative = false;
  std::optional<eosio::name> coop_type;
  // Тип некоммерческой организации
  //  (0, _('Union of Societies')),
  // 	(1, _('Consumer Cooperative')),
  // 	(2, _('Production Cooperative')),
  // 	(3, _('Agriculture Cooperative')),
  // 	(4, _('Builder\'s Societes')),
  // 	(5, _('Non-profit organization'))
  std::optional<eosio::name> token_contract;
  std::optional<std::string> slug; 
  std::optional<std::string> announce;
  std::optional<std::string> description;
  std::optional<uint64_t> members_count;
  std::optional<uint64_t> users_count;
  std::optional<uint64_t> orgs_counts;
  std::optional<eosio::asset> initial;//Вступительный взнос
  std::optional<eosio::asset> minimum;//Минимальный взнос
  std::optional<eosio::asset> membership;//Членский взнос
  std::optional<eosio::name> period;//Периодичность
  //  (0, _('per case')), 	 - зависит от программы
	// (1, _('daily')),
	// (2, _('weekly')),
	// (3, _('monthly')),
	// (4, _('quarterly')),
	// (5, _('half a year')),
	// (6, _('annually')),
	// (7, _('onetime')),



  uint64_t primary_key() const {
    return username.value;
  }
  uint64_t by_parent() const {
    return parent_username.value;
  }
  
  uint128_t by_coop_childs() const {
    return combine_ids(username.value, parent_username.value);
  }

  uint64_t is_coop_index() const {
    return is_cooperative == true ? 1:0;
  }
  uint64_t bycooptype() const {
    return coop_type.value_or(""_n).value;
  }

  uint64_t is_verified_index() const {
    return verification.is_verified == true ? 1 : 0;
  }

  bool is_coop() const {
    return is_cooperative;
  }
  bool is_verified() const {
    return verification.is_verified;
  }



};

typedef eosio::multi_index<"orgs"_n, orgs,
eosio::indexed_by<"iscoop"_n, eosio::const_mem_fun<orgs, uint64_t,
                                                       &orgs::is_coop_index>>,
eosio::indexed_by<"byparent"_n, eosio::const_mem_fun<orgs, uint64_t,
                                                       &orgs::by_parent>>,
eosio::indexed_by<"bycoopchilds"_n, eosio::const_mem_fun<orgs, uint128_t, &orgs::by_coop_childs>>,
eosio::indexed_by<"bycooptype"_n, eosio::const_mem_fun<orgs, uint64_t, &orgs::bycooptype>>,
eosio::indexed_by<"byverif"_n, eosio::const_mem_fun<orgs, uint64_t,
                                                       &orgs::is_verified_index>>

> orgs_index;


