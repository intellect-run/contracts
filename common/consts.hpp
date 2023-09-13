#define ANO "ano"
#define DRAFT "draft"
#define MARKETPLACE "marketplace"
#define SOVIET "soviet"
#define REGISTRATOR "registrator"
#define SYSTEM "eosio"
#define PARTNERS "part"

static constexpr uint64_t _auction_name_length_limit = 5;

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

static constexpr eosio::name _regaccount_action = "joincoop"_n;
static constexpr eosio::name _change_action = "change"_n;

static constexpr eosio::symbol _root_symbol =
    eosio::symbol(eosio::symbol_code("AXON"), 4); /*!< системный токен */
static constexpr eosio::name _root_contract =
    "eosio.token"_n; /*!< системный контракт */
static constexpr eosio::symbol RAM_symbol{
    "RAM", 0}; /*!< токен рынка оперативной памяти */
static constexpr eosio::symbol _ramcore_symbol =
    eosio::symbol(eosio::symbol_code("RAMCORE"),
                  4); /*!< идентификационный токен рынка оперативной памяти */
