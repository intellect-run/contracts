# group `public_actions` {#group__public__actions}

Методы действий контракта

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`reguser`](#group__public__actions_1ga25589c2c87b594bea2a82aea5bd1112c)`(eosio::name username,std::string profile_hash)`            | Метод регистрации индивидуального лица @auth registrator.
`public void `[`update`](#group__public__actions_1ga526630a59833df6756f1d1854f04a89d)`(eosio::name username,std::string uid,std::string meta)`            | Метод обновления профиля @auth username.
`public void `[`changekey`](#group__public__actions_1ga68df314fe90a719f00f0931c097bc6c5)`(eosio::name username,eosio::public_key public_key)`            | Метод восстановления ключа @auth любой аккаунт
`public void `[`confirmreg`](#group__public__actions_1gade0cb6032b21e1b753ec1b4f2b4bea73)`(eosio::name coop_username,eosio::name member,std::string position_title,eosio::name position)`            | Метод подтверждения регистрации @auth payer.

## Members

#### `public void `[`reguser`](#group__public__actions_1ga25589c2c87b594bea2a82aea5bd1112c)`(eosio::name username,std::string profile_hash)` {#group__public__actions_1ga25589c2c87b594bea2a82aea5bd1112c}

Метод регистрации индивидуального лица @auth registrator.

###### Parameters
* `registrator` имя аккаунта регистратора 

* `referer` имя аккаунта реферера нового аккаунта (не обязательно, если set_referer = false) 

* `newaccount` имя нового аккаунта 

* `public_key` публичный ключ нового аккаунта 

* `cpu` количество системного токена в CPU 

* `net` количество системного токена в NET 

* `ram_bytes` 

количество оперативной памяти нового аккаунта 
###### Parameters
* `is_guest` флаг регистрации в качестве гостя 

* `set_referer` флаг автоматической установки реферера в контракт партнёров

Метод производит регистрацию нового аккаунта в системе. Если is_guest = true, то аккаунт регистрируется в качестве гостя, что означает, что контракт регистратора устанавливает права владельца нового аккаунта на себя. Если is_guest = false, то регистратор создаёт новый аккаунт с передачей прав владельца на него. Флаг set_referer используется для автоматической установки партнёра в реферальную структуру, что не обязательно.

#### `public void `[`update`](#group__public__actions_1ga526630a59833df6756f1d1854f04a89d)`(eosio::name username,std::string uid,std::string meta)` {#group__public__actions_1ga526630a59833df6756f1d1854f04a89d}

Метод обновления профиля @auth username.

Метод производит поиск аккаунтов гостей с истекшим сроком давности и заменяет им активные права доступа. Отозванные аккаунты помещаются в таблицу reserved для дальнейшего использования или полного удаления.

#### `public void `[`changekey`](#group__public__actions_1ga68df314fe90a719f00f0931c097bc6c5)`(eosio::name username,eosio::public_key public_key)` {#group__public__actions_1ga68df314fe90a719f00f0931c097bc6c5}

Метод восстановления ключа @auth любой аккаунт

Метод производит поиск аккаунтов гостей с истекшим сроком давности и заменяет им активные права доступа. Отозванные аккаунты помещаются в таблицу reserved для дальнейшего использования или полного удаления.

#### `public void `[`confirmreg`](#group__public__actions_1gade0cb6032b21e1b753ec1b4f2b4bea73)`(eosio::name coop_username,eosio::name member,std::string position_title,eosio::name position)` {#group__public__actions_1gade0cb6032b21e1b753ec1b4f2b4bea73}

Метод подтверждения регистрации @auth payer.

###### Parameters
* `payer` 

* `username` The username 

* `quantity` The quantity

Метод оплаты вызывается гостем после пополнения своего баланса как регистратора. Оплата списывается с баланса регистратора, а права владельца заменяются на публичный ключ, указанный в объекте гостя.

