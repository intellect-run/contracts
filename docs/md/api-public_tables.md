# group `public_tables` {#group__public__tables}

Структуры таблиц контракта

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[`accounts`](#structaccounts) | Таблица хранения отозванных аккаунтов гостей<br/><br/>@table newaccounts @contract _me @scope _me.
`struct `[`users`](#structusers) | Таблица хранения объектов гостей<br/><br/>@table individuals @contract _me @scope _me.
`struct `[`registrator::balances`](#structregistrator_1_1balances) | Таблица хранения глобальной сети партнёров<br/><br/>@contract _me @scope _me @table partners.

# struct `accounts` {#structaccounts}

Таблица хранения отозванных аккаунтов гостей

@table newaccounts @contract _me @scope _me.

Хранит аккаунты, отозванные у гостей путём замены их активного ключа на ключ регистратора за истечением срока давности без поступления оплаты.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::name `[`username`](#structaccounts_1a05876c5415522c3ff8a3d8e8a783d6a7) | имя аккаунта гостя
`public eosio::name `[`status`](#structaccounts_1a0498f8a07ad571d52548a076370d9253) | статус аккаунта: "pending" - ожидание утверждения советом, "active" - активный аккаунт; "blocked" - заблокированный аккаунт; "deleted" - удален пользователем;
`public uint64_t `[`reputation`](#structaccounts_1aaa9631adef3e542db5ddc1e2388dfd61) | 
`public std::string `[`uid`](#structaccounts_1af38528c6fa35cb2763035b76af1a8189) | 
`public eosio::checksum256 `[`uid_hash`](#structaccounts_1ae973d8ff759b32dc26bb3b5e1174619d) | 
`public eosio::name `[`type`](#structaccounts_1af1bfc2d1e94ebb71271c0ce836558160) | 
`public eosio::name `[`registrator`](#structaccounts_1a432b7b14e9da714d2de1546dbbd74a7e) | имя аккаунта регистратора
`public eosio::name `[`referer`](#structaccounts_1a42c6052506d3b2d89bbbb95913591809) | 
`public eosio::asset `[`registration_amount`](#structaccounts_1a9aa73b3535b162d4dbcdb5c581146ce2) | количество токенов к оплате
`public std::string `[`meta`](#structaccounts_1aeecfd8c0939c8e7de20db6126b965bd9) | 
`public eosio::time_point_sec `[`registered_at`](#structaccounts_1a5ab584c673fa71b1aebd8eb3ec4e69e5) | 
`public eosio::time_point_sec `[`last_update`](#structaccounts_1a84633a253175f02bb81c1260645780ea) | 
`public eosio::time_point_sec `[`signature_expires_at`](#structaccounts_1a38b262d4ca61e4cecb3f1eab1a5d3887) | 
`public eosio::time_point_sec `[`signature_last_update`](#structaccounts_1a00f7df522967257d7bf5fd065d942241) | 
`public inline uint64_t `[`primary_key`](#structaccounts_1ac5356720544cfbfc9b82d829f4fa4f37)`() const` | return username - primary_key
`public inline uint64_t `[`by_referer`](#structaccounts_1a779b22d35ce6564c3b2e34e03b77aa29)`() const` | 
`public inline uint64_t `[`by_type`](#structaccounts_1a336640e99b5ae6106b3715cae302ff46)`() const` | 
`public inline uint64_t `[`by_status`](#structaccounts_1ae34d3eff438789f8e09b1fef2eed2af2)`() const` | 
`public inline uint64_t `[`by_registr`](#structaccounts_1a88ed8c7045efdf796cfadb54e91ef284)`() const` | 
`public inline eosio::checksum256 `[`byuidhash`](#structaccounts_1a15da9b51d8a9d7acaff45fdeaa80c5a4)`() const` | 

## Members

#### `public eosio::name `[`username`](#structaccounts_1a05876c5415522c3ff8a3d8e8a783d6a7) {#structaccounts_1a05876c5415522c3ff8a3d8e8a783d6a7}

имя аккаунта гостя

#### `public eosio::name `[`status`](#structaccounts_1a0498f8a07ad571d52548a076370d9253) {#structaccounts_1a0498f8a07ad571d52548a076370d9253}

статус аккаунта: "pending" - ожидание утверждения советом, "active" - активный аккаунт; "blocked" - заблокированный аккаунт; "deleted" - удален пользователем;

#### `public uint64_t `[`reputation`](#structaccounts_1aaa9631adef3e542db5ddc1e2388dfd61) {#structaccounts_1aaa9631adef3e542db5ddc1e2388dfd61}

#### `public std::string `[`uid`](#structaccounts_1af38528c6fa35cb2763035b76af1a8189) {#structaccounts_1af38528c6fa35cb2763035b76af1a8189}

#### `public eosio::checksum256 `[`uid_hash`](#structaccounts_1ae973d8ff759b32dc26bb3b5e1174619d) {#structaccounts_1ae973d8ff759b32dc26bb3b5e1174619d}

#### `public eosio::name `[`type`](#structaccounts_1af1bfc2d1e94ebb71271c0ce836558160) {#structaccounts_1af1bfc2d1e94ebb71271c0ce836558160}

#### `public eosio::name `[`registrator`](#structaccounts_1a432b7b14e9da714d2de1546dbbd74a7e) {#structaccounts_1a432b7b14e9da714d2de1546dbbd74a7e}

имя аккаунта регистратора

#### `public eosio::name `[`referer`](#structaccounts_1a42c6052506d3b2d89bbbb95913591809) {#structaccounts_1a42c6052506d3b2d89bbbb95913591809}

#### `public eosio::asset `[`registration_amount`](#structaccounts_1a9aa73b3535b162d4dbcdb5c581146ce2) {#structaccounts_1a9aa73b3535b162d4dbcdb5c581146ce2}

количество токенов к оплате

#### `public std::string `[`meta`](#structaccounts_1aeecfd8c0939c8e7de20db6126b965bd9) {#structaccounts_1aeecfd8c0939c8e7de20db6126b965bd9}

#### `public eosio::time_point_sec `[`registered_at`](#structaccounts_1a5ab584c673fa71b1aebd8eb3ec4e69e5) {#structaccounts_1a5ab584c673fa71b1aebd8eb3ec4e69e5}

#### `public eosio::time_point_sec `[`last_update`](#structaccounts_1a84633a253175f02bb81c1260645780ea) {#structaccounts_1a84633a253175f02bb81c1260645780ea}

#### `public eosio::time_point_sec `[`signature_expires_at`](#structaccounts_1a38b262d4ca61e4cecb3f1eab1a5d3887) {#structaccounts_1a38b262d4ca61e4cecb3f1eab1a5d3887}

#### `public eosio::time_point_sec `[`signature_last_update`](#structaccounts_1a00f7df522967257d7bf5fd065d942241) {#structaccounts_1a00f7df522967257d7bf5fd065d942241}

#### `public inline uint64_t `[`primary_key`](#structaccounts_1ac5356720544cfbfc9b82d829f4fa4f37)`() const` {#structaccounts_1ac5356720544cfbfc9b82d829f4fa4f37}

return username - primary_key

#### `public inline uint64_t `[`by_referer`](#structaccounts_1a779b22d35ce6564c3b2e34e03b77aa29)`() const` {#structaccounts_1a779b22d35ce6564c3b2e34e03b77aa29}

#### `public inline uint64_t `[`by_type`](#structaccounts_1a336640e99b5ae6106b3715cae302ff46)`() const` {#structaccounts_1a336640e99b5ae6106b3715cae302ff46}

#### `public inline uint64_t `[`by_status`](#structaccounts_1ae34d3eff438789f8e09b1fef2eed2af2)`() const` {#structaccounts_1ae34d3eff438789f8e09b1fef2eed2af2}

#### `public inline uint64_t `[`by_registr`](#structaccounts_1a88ed8c7045efdf796cfadb54e91ef284)`() const` {#structaccounts_1a88ed8c7045efdf796cfadb54e91ef284}

#### `public inline eosio::checksum256 `[`byuidhash`](#structaccounts_1a15da9b51d8a9d7acaff45fdeaa80c5a4)`() const` {#structaccounts_1a15da9b51d8a9d7acaff45fdeaa80c5a4}

# struct `users` {#structusers}

Таблица хранения объектов гостей

@table individuals @contract _me @scope _me.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::name `[`username`](#structusers_1a737eae3ed6e76f98919b26b20288164b) | имя аккаунта
`public std::string `[`profile_hash`](#structusers_1ae07b933da6c46eb7dfe70f5c95ade143) | 
`public `[`verification`](docs/md/api-undefined.md#structverification)` `[`verification`](#structusers_1ac39df2d81bcbcf04648eab679a910044) | 
`public inline uint64_t `[`primary_key`](#structusers_1a6894c358dbcce05a63de742f2b5fbd8e)`() const` | return username - primary_key
`public inline uint64_t `[`by_verified`](#structusers_1a0aef32204b2b1f86902c63150d4f230c)`() const` | 

## Members

#### `public eosio::name `[`username`](#structusers_1a737eae3ed6e76f98919b26b20288164b) {#structusers_1a737eae3ed6e76f98919b26b20288164b}

имя аккаунта

#### `public std::string `[`profile_hash`](#structusers_1ae07b933da6c46eb7dfe70f5c95ade143) {#structusers_1ae07b933da6c46eb7dfe70f5c95ade143}

#### `public `[`verification`](docs/md/api-undefined.md#structverification)` `[`verification`](#structusers_1ac39df2d81bcbcf04648eab679a910044) {#structusers_1ac39df2d81bcbcf04648eab679a910044}

#### `public inline uint64_t `[`primary_key`](#structusers_1a6894c358dbcce05a63de742f2b5fbd8e)`() const` {#structusers_1a6894c358dbcce05a63de742f2b5fbd8e}

return username - primary_key

#### `public inline uint64_t `[`by_verified`](#structusers_1a0aef32204b2b1f86902c63150d4f230c)`() const` {#structusers_1a0aef32204b2b1f86902c63150d4f230c}

# struct `registrator::balances` {#structregistrator_1_1balances}

```
struct registrator::balances
  : public balances_base
```  

Таблица хранения глобальной сети партнёров

@contract _me @scope _me @table partners.

Таблица хранит реферальные связи партнёров, их профили и глобальные статусы.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

