static constexpr eosio::name _ano = "ano"_n;
static constexpr eosio::name _draft = "draft"_n;
static constexpr eosio::name _marketplace =
    "marketplace"_n; /*!< имя контракта */
static constexpr eosio::name _soviet =
    "soviet"_n; /*!< дополнительная константа */
static constexpr eosio::name _registrator = "registrator"_n;
static constexpr eosio::name _system = "eosio"_n;
static constexpr eosio::name _partners =
      "part"_n; /*!< имя аккаунта контракта хранилища партнёров */



static constexpr eosio::symbol _root_symbol =
    eosio::symbol(eosio::symbol_code("AXON"), 4); /*!< системный токен */
static constexpr eosio::name _root_contract =
    "eosio.token"_n; /*!< системный контракт */
static constexpr eosio::symbol RAM_symbol{
    "RAM", 0}; /*!< токен рынка оперативной памяти */
static constexpr eosio::symbol _ramcore_symbol =
    eosio::symbol(eosio::symbol_code("RAMCORE"),
                  4); /*!< идентификационный токен рынка оперативной памяти */
