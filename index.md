docs/xml   Compound {
  name: undefined,
  compounds: {},
  members: [],
  basecompoundref: [],
  filtered: {}
} {
  doxygenindex: {
    '$': {
      'xmlns:xsi': 'http://www.w3.org/2001/XMLSchema-instance',
      'xsi:noNamespaceSchemaLocation': 'index.xsd',
      version: '1.9.3',
      'xml:lang': 'en-US'
    },
    compound: [
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object],
      ... 175 more items
    ]
  }
}
# namespace `eosiobios`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``bios``](#classeosiobios_1_1bios)    | 
`struct `[``authority``](#structeosiobios_1_1authority)    | 
`struct `[``block_header``](#structeosiobios_1_1block__header)    | 
`struct `[``key_weight``](#structeosiobios_1_1key__weight)    | 
`struct `[``permission_level_weight``](#structeosiobios_1_1permission__level__weight)    | 
`struct `[``wait_weight``](#structeosiobios_1_1wait__weight)    | 

# class `bios` {#classeosiobios_1_1bios}

```
class bios
  : public eosio::contract
```  



The `eosio.bios` is the first sample of system contract provided by `block.one` through the EOSIO platform. It is a minimalist system contract because it only supplies the actions that are absolutely critical to bootstrap a chain and nothing more. This allows for a chain agnostic approach to bootstrapping a chain.

Just like in the `eosio.system` sample contract implementation, there are a few actions which are not implemented at the contract level (`newaccount`, `updateauth`, `deleteauth`, `linkauth`, `unlinkauth`, `canceldelay`, `onerror`, `setabi`, `setcode`), they are just declared in the contract so they will show in the contract's ABI and users will be able to push those actions to the chain via the account holding the `eosio.system` contract, but the implementation is at the EOSIO core level. They are referred to as EOSIO native actions.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[``abi_hash``](#structeosiobios_1_1bios_1_1abi__hash)        | 
`public inline void newaccount(name creator,name name,ignore< `[`authority`](#structeosiobios_1_1authority)` > owner,ignore< `[`authority`](#structeosiobios_1_1authority)` > active)` | 
`public inline void updateauth(ignore< name > account,ignore< name > permission,ignore< name > parent,ignore< `[`authority`](#structeosiobios_1_1authority)` > auth)` | 
`public inline void deleteauth(ignore< name > account,ignore< name > permission)` | 
`public inline void linkauth(ignore< name > account,ignore< name > code,ignore< name > type,ignore< name > requirement)` | 
`public inline void unlinkauth(ignore< name > account,ignore< name > code,ignore< name > type)` | 
`public inline void canceldelay(ignore< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > canceling_auth,ignore< checksum256 > trx_id)` | 
`public inline void setcode(name account,uint8_t vmtype,uint8_t vmversion,const std::vector< char > & code)` | 
`public void setabi(name account,const std::vector< char > & abi)` | 
`public void onerror(ignore< uint128_t > sender_id,ignore< std::vector< char > > sent_trx)` | 
`public void setpriv(name account,uint8_t is_priv)` | 
`public void setalimits(name account,int64_t ram_bytes,int64_t net_weight,int64_t cpu_weight)` | 
`public void setprods(const std::vector< eosio::producer_authority > & schedule)` | 
`public void setparams(const eosio::blockchain_parameters & params)` | 
`public void reqauth(name from)` | 
`public void activate(const eosio::checksum256 & feature_digest)` | 
`public void reqactivated(const eosio::checksum256 & feature_digest)` | 

## Members

### `struct `[``abi_hash``](#structeosiobios_1_1bios_1_1abi__hash) {#structeosiobios_1_1bios_1_1abi__hash}




### `public inline void newaccount(name creator,name name,ignore< `[`authority`](#structeosiobios_1_1authority)` > owner,ignore< `[`authority`](#structeosiobios_1_1authority)` > active)` {#classeosiobios_1_1bios_1a289a68eec1095060829ae3f3cedba2b1}



New account action, called after a new account is created. This code enforces resource-limits rules for new accounts as well as new account naming conventions.

* accounts cannot contain '.' symbols which forces all acccounts to be 12 characters long without '.' until a future account auction process is implemented which prevents name squatting.


* new accounts must stake a minimal number of tokens (as set in system parameters) therefore, this method will execute an inline buyram from receiver for newacnt in an amount equal to the current new account creation fee.

### `public inline void updateauth(ignore< name > account,ignore< name > permission,ignore< name > parent,ignore< `[`authority`](#structeosiobios_1_1authority)` > auth)` {#classeosiobios_1_1bios_1a6da029e3f9ffbcb2bfc3cc6f555a3bcd}



Update authorization action updates pemission for an account.


#### Parameters
* `account` - the account for which the permission is updated, 


* `pemission` - the permission name which is updated, 


* `parem` - the parent of the permission which is updated, 


* `aut` - the json describing the permission authorization.

### `public inline void deleteauth(ignore< name > account,ignore< name > permission)` {#classeosiobios_1_1bios_1a496491a411e8263ae0d91179526c25a6}



Delete authorization action deletes the authorization for an account's permission.


#### Parameters
* `account` - the account for which the permission authorization is deleted, 


* `permission` - the permission name been deleted.

### `public inline void linkauth(ignore< name > account,ignore< name > code,ignore< name > type,ignore< name > requirement)` {#classeosiobios_1_1bios_1ac88e1fbb2bf9f23fcf351ab4f02bcf23}



Link authorization action assigns a specific action from a contract to a permission you have created. Five system actions can not be linked `updateauth`, `deleteauth`, `linkauth`, `unlinkauth`, and `canceldelay`. This is useful because when doing authorization checks, the EOSIO based blockchain starts with the action needed to be authorized (and the contract belonging to), and looks up which permission is needed to pass authorization validation. If a link is set, that permission is used for authoraization validation otherwise then active is the default, with the exception of `eosio.any`. `eosio.any` is an implicit permission which exists on every account; you can link actions to `eosio.any` and that will make it so linked actions are accessible to any permissions defined for the account.


#### Parameters
* `account` - the permission's owner to be linked and the payer of the RAM needed to store this link, 


* `code` - the owner of the action to be linked, 


* `type` - the action to be linked, 


* `requirement` - the permission to be linked.

### `public inline void unlinkauth(ignore< name > account,ignore< name > code,ignore< name > type)` {#classeosiobios_1_1bios_1a754f09c20691df6b7292dad22b3a80c9}



Unlink authorization action it's doing the reverse of linkauth action, by unlinking the given action.


#### Parameters
* `account` - the owner of the permission to be unlinked and the receiver of the freed RAM, 


* `code` - the owner of the action to be unlinked, 


* `type` - the action to be unlinked.

### `public inline void canceldelay(ignore< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > canceling_auth,ignore< checksum256 > trx_id)` {#classeosiobios_1_1bios_1a7b70dcae7153a74de611cc78e59b0352}



Cancel delay action cancels a deferred transaction.


#### Parameters
* `canceling_auth` - the permission that authorizes this action, 


* `trx_id` - the deferred transaction id to be cancelled.

### `public inline void setcode(name account,uint8_t vmtype,uint8_t vmversion,const std::vector< char > & code)` {#classeosiobios_1_1bios_1afb059bb5862ce9b0cda885bc130a52e3}



Set code action sets the contract code for an account.


#### Parameters
* `account` - the account for which to set the contract code. 


* `vmtype` - reserved, set it to zero. 


* `vmversion` - reserved, set it to zero. 


* `code` - the code content to be set, in the form of a blob binary..

### `public void setabi(name account,const std::vector< char > & abi)` {#classeosiobios_1_1bios_1a0663bbf0563a9ad67960ccbae6222911}



Set abi action sets the abi for contract identified by `account` name. Creates an entry in the abi_hash_table index, with `account` name as key, if it is not already present and sets its value with the abi hash. Otherwise it is updating the current abi hash value for the existing `account` key.


#### Parameters
* `account` - the name of the account to set the abi for 


* `abi` - the abi hash represented as a vector of characters

### `public void onerror(ignore< uint128_t > sender_id,ignore< std::vector< char > > sent_trx)` {#classeosiobios_1_1bios_1a317235869c18964d6d9425eefa533098}



On error action, notification of this action is delivered to the sender of a deferred transaction when an objective error occurs while executing the deferred transaction. This action is not meant to be called directly.


#### Parameters
* `sender_id` - the id for the deferred transaction chosen by the sender, 


* `sent_trx` - the deferred transaction that failed.

### `public void setpriv(name account,uint8_t is_priv)` {#classeosiobios_1_1bios_1ae5de33639414c0c00e090a2ca7418c69}



Set privilege action allows to set privilege status for an account (turn it on/off). 
#### Parameters
* `account` - the account to set the privileged status for. 


* `is_priv` - 0 for false, > 0 for true.

### `public void setalimits(name account,int64_t ram_bytes,int64_t net_weight,int64_t cpu_weight)` {#classeosiobios_1_1bios_1ac7a64a2f4cf193136957f5be5aeca85b}



Sets the resource limits of an account


#### Parameters
* `account` - name of the account whose resource limit to be set 


* `ram_bytes` - ram limit in absolute bytes 


* `net_weight` - fractionally proportionate net limit of available resources based on (weight / total_weight_of_all_accounts) 


* `cpu_weight` - fractionally proportionate cpu limit of available resources based on (weight / total_weight_of_all_accounts)

### `public void setprods(const std::vector< eosio::producer_authority > & schedule)` {#classeosiobios_1_1bios_1aac48a883107aeacbd1b567a2e3fbad12}



Set producers action, sets a new list of active producers, by proposing a schedule change, once the block that contains the proposal becomes irreversible, the schedule is promoted to "pending" automatically. Once the block that promotes the schedule is irreversible, the schedule will become "active".


#### Parameters
* `schedule` - New list of active producers to set

### `public void setparams(const eosio::blockchain_parameters & params)` {#classeosiobios_1_1bios_1ad4047afa380b9eda3ecc232d89bf05a7}



Set params action, sets the blockchain parameters. By tuning these parameters, various degrees of customization can be achieved.


#### Parameters
* `params` - New blockchain parameters to set

### `public void reqauth(name from)` {#classeosiobios_1_1bios_1abfefcfb3d6b2b221052a6e017de18c56}



Require authorization action, checks if the account name `from` passed in as param has authorization to access current action, that is, if it is listed in the action’s allowed permissions vector.


#### Parameters
* `from` - the account name to authorize

### `public void activate(const eosio::checksum256 & feature_digest)` {#classeosiobios_1_1bios_1ad642c358d927b33340654d59f9dd0df9}



Activate action, activates a protocol feature


#### Parameters
* `feature_digest` - hash of the protocol feature to activate.

### `public void reqactivated(const eosio::checksum256 & feature_digest)` {#classeosiobios_1_1bios_1a3f7b5f24b41381cde54901b02ee1793d}



Require activated action, asserts that a protocol feature has been activated


#### Parameters
* `feature_digest` - hash of the protocol feature to check for activation.


# struct `abi_hash` {#structeosiobios_1_1bios_1_1abi__hash}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name owner` | 
`public checksum256 hash` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public name owner` {#structeosiobios_1_1bios_1_1abi__hash_1a9192f39fbb92a8ef905d1f28056e904d}





### `public checksum256 hash` {#structeosiobios_1_1bios_1_1abi__hash_1aa92ab376c71ad111a260a5b566207656}





### `public inline uint64_t primary_key() const` {#structeosiobios_1_1bios_1_1abi__hash_1aee318ae24137cc1a7c1db705957d9e52}






# struct `authority` {#structeosiobios_1_1authority}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint32_t threshold` | 
`public std::vector< `[`key_weight`](#structeosiobios_1_1key__weight)` > keys` | 
`public std::vector< `[`permission_level_weight`](#structeosiobios_1_1permission__level__weight)` > accounts` | 
`public std::vector< `[`wait_weight`](#structeosiobios_1_1wait__weight)` > waits` | 

## Members

### `public uint32_t threshold` {#structeosiobios_1_1authority_1a39fdbcf135683889becbb79b7f494df0}





### `public std::vector< `[`key_weight`](#structeosiobios_1_1key__weight)` > keys` {#structeosiobios_1_1authority_1ab3a3f653907a5490ab96ac7605198f2c}





### `public std::vector< `[`permission_level_weight`](#structeosiobios_1_1permission__level__weight)` > accounts` {#structeosiobios_1_1authority_1a1f834bcacfd6abd1d2f7aa389990cf5a}





### `public std::vector< `[`wait_weight`](#structeosiobios_1_1wait__weight)` > waits` {#structeosiobios_1_1authority_1a674014ea85ff0ee9d4dcd9a3d1922d61}






# struct `block_header` {#structeosiobios_1_1block__header}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint32_t timestamp` | 
`public name producer` | 
`public uint16_t confirmed` | 
`public checksum256 previous` | 
`public checksum256 transaction_mroot` | 
`public checksum256 action_mroot` | 
`public uint32_t schedule_version` | 
`public std::optional< eosio::producer_schedule > new_producers` | 

## Members

### `public uint32_t timestamp` {#structeosiobios_1_1block__header_1ac25070170e000a8427f2e96d0e3fd7b0}





### `public name producer` {#structeosiobios_1_1block__header_1a0c794f15d473ccc576dc403676689536}





### `public uint16_t confirmed` {#structeosiobios_1_1block__header_1ad0e00f2357c447a2001b9192849aa839}





### `public checksum256 previous` {#structeosiobios_1_1block__header_1aae1cc92b2256891adbd2539efa99cc34}





### `public checksum256 transaction_mroot` {#structeosiobios_1_1block__header_1adb40a37bf4327f68e081a07cc2abe5c8}





### `public checksum256 action_mroot` {#structeosiobios_1_1block__header_1af1c275fdf2db888deff6db96514dfbd8}





### `public uint32_t schedule_version` {#structeosiobios_1_1block__header_1af34fd0dd085bf489c10b02be5f4dd209}





### `public std::optional< eosio::producer_schedule > new_producers` {#structeosiobios_1_1block__header_1a75189b8a7b99f93b14f9b775bf343396}






# struct `key_weight` {#structeosiobios_1_1key__weight}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::public_key key` | 
`public uint16_t weight` | 

## Members

### `public eosio::public_key key` {#structeosiobios_1_1key__weight_1ac2a44ff06f540ec05005ea808278b398}





### `public uint16_t weight` {#structeosiobios_1_1key__weight_1a712f1942b6ad8deec868c03a156e609c}






# struct `permission_level_weight` {#structeosiobios_1_1permission__level__weight}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` permission` | 
`public uint16_t weight` | 

## Members

### `public `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` permission` {#structeosiobios_1_1permission__level__weight_1a541c2041fbf4a2847144a156531ed3bb}





### `public uint16_t weight` {#structeosiobios_1_1permission__level__weight_1ad0a6f4cb52b93d3673b1fc22486880fa}






# struct `wait_weight` {#structeosiobios_1_1wait__weight}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint32_t wait_sec` | 
`public uint16_t weight` | 

## Members

### `public uint32_t wait_sec` {#structeosiobios_1_1wait__weight_1ad5cbfb9e4e061f20ad06134ff7c7a8e9}





### `public uint16_t weight` {#structeosiobios_1_1wait__weight_1a9a3d73af3abe1105cbb23ea8cbdecc5c}






# namespace `eosiosystem`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[``block_info``](#namespaceeosiosystem_1_1block__info)    | 
`class `[``system_contract``](#classeosiosystem_1_1system__contract)    | 
`class `[``native``](#classeosiosystem_1_1native)    | 
`struct `[``abi_hash``](#structeosiosystem_1_1abi__hash)    | 
`struct `[``authority``](#structeosiosystem_1_1authority)    | 
`struct `[``bid_refund``](#structeosiosystem_1_1bid__refund)    | 
`struct `[``block_header``](#structeosiosystem_1_1block__header)    | 
`struct `[``exchange_state``](#structeosiosystem_1_1exchange__state)    | 
`struct `[``delegated_bandwidth``](#structeosiosystem_1_1delegated__bandwidth)    | 
`struct `[``eosio_global_state``](#structeosiosystem_1_1eosio__global__state)    | 
`struct `[``eosio_global_state2``](#structeosiosystem_1_1eosio__global__state2)    | 
`struct `[``eosio_global_state3``](#structeosiosystem_1_1eosio__global__state3)    | 
`struct `[``eosio_global_state4``](#structeosiosystem_1_1eosio__global__state4)    | 
`struct `[``key_weight``](#structeosiosystem_1_1key__weight)    | 
`struct `[``limit_auth_change``](#structeosiosystem_1_1limit__auth__change)    | 
`struct `[``name_bid``](#structeosiosystem_1_1name__bid)    | 
`struct `[``pair_time_point_sec_int64``](#structeosiosystem_1_1pair__time__point__sec__int64)    | 
`struct `[``permission_level_weight``](#structeosiosystem_1_1permission__level__weight)    | 
`struct `[``powerup_config``](#structeosiosystem_1_1powerup__config)    | 
`struct `[``powerup_config_resource``](#structeosiosystem_1_1powerup__config__resource)    | 
`struct `[``powerup_order``](#structeosiosystem_1_1powerup__order)    | 
`struct `[``powerup_state``](#structeosiosystem_1_1powerup__state)    | 
`struct `[``powerup_state_resource``](#structeosiosystem_1_1powerup__state__resource)    | 
`struct `[``producer_info``](#structeosiosystem_1_1producer__info)    | 
`struct `[``producer_info2``](#structeosiosystem_1_1producer__info2)    | 
`struct `[``refund_request``](#structeosiosystem_1_1refund__request)    | 
`struct `[``rex_balance``](#structeosiosystem_1_1rex__balance)    | 
`struct `[``rex_fund``](#structeosiosystem_1_1rex__fund)    | 
`struct `[``rex_loan``](#structeosiosystem_1_1rex__loan)    | 
`struct `[``rex_order``](#structeosiosystem_1_1rex__order)    | 
`struct `[``rex_order_outcome``](#structeosiosystem_1_1rex__order__outcome)    | 
`struct `[``rex_pool``](#structeosiosystem_1_1rex__pool)    | 
`struct `[``rex_return_buckets``](#structeosiosystem_1_1rex__return__buckets)    | 
`struct `[``rex_return_pool``](#structeosiosystem_1_1rex__return__pool)    | 
`struct `[``user_resources``](#structeosiosystem_1_1user__resources)    | 
`struct `[``voter_info``](#structeosiosystem_1_1voter__info)    | 
`struct `[``wait_weight``](#structeosiosystem_1_1wait__weight)    | 

# namespace `block_info`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[``block_batch_info``](#structeosiosystem_1_1block__info_1_1block__batch__info)    | 
`struct `[``block_info_record``](#structeosiosystem_1_1block__info_1_1block__info__record)    | 
`struct `[``latest_block_batch_info_result``](#structeosiosystem_1_1block__info_1_1latest__block__batch__info__result)    | 

# struct `block_batch_info` {#structeosiosystem_1_1block__info_1_1block__batch__info}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint32_t batch_start_height` | 
`public eosio::time_point batch_start_timestamp` | 
`public uint32_t batch_current_end_height` | 
`public eosio::time_point batch_current_end_timestamp` | 

## Members

### `public uint32_t batch_start_height` {#structeosiosystem_1_1block__info_1_1block__batch__info_1aabf1478c4a361b8fc044f77c4617e32b}





### `public eosio::time_point batch_start_timestamp` {#structeosiosystem_1_1block__info_1_1block__batch__info_1af7f9f6a56f32f91ec80622736fe86478}





### `public uint32_t batch_current_end_height` {#structeosiosystem_1_1block__info_1_1block__batch__info_1a54af69850d006e2a43fdea538f5c0695}





### `public eosio::time_point batch_current_end_timestamp` {#structeosiosystem_1_1block__info_1_1block__batch__info_1aef63da736d0ed2568917a4e9aeb44931}






# struct `block_info_record` {#structeosiosystem_1_1block__info_1_1block__info__record}




The blockinfo table holds a rolling window of records containing information for recent blocks.

Each record stores the height and timestamp of the correspond block. A record is added for a new block through the onblock action. The onblock action also erases up to two old records at a time in an attempt to keep the table consisting of only records for blocks going back a particular block height difference backward from the most recent block. Currently that block height difference is hardcoded to 10.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public uint32_t block_height` | 
`public eosio::time_point block_timestamp` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public uint8_t version` {#structeosiosystem_1_1block__info_1_1block__info__record_1a9561691091de21a997db569d84d53a0d}





### `public uint32_t block_height` {#structeosiosystem_1_1block__info_1_1block__info__record_1a7e0b0f4b78c5dcdff23495596e7cb488}





### `public eosio::time_point block_timestamp` {#structeosiosystem_1_1block__info_1_1block__info__record_1afaa04cfe4be674be7f3d4d497e90c072}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1block__info_1_1block__info__record_1abbe8ecea1c14ab583d956b76a9be0407}






# struct `latest_block_batch_info_result` {#structeosiosystem_1_1block__info_1_1latest__block__batch__info__result}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::optional< `[`block_batch_info`](#structeosiosystem_1_1block__info_1_1block__batch__info)` > result` | 
`public `[`error_code_enum`](#structeosiosystem_1_1block__info_1_1latest__block__batch__info__result_1aae67f275b3852dbc62dcfbc8be6e7e8c)` error_code` | 

## Members

### `public std::optional< `[`block_batch_info`](#structeosiosystem_1_1block__info_1_1block__batch__info)` > result` {#structeosiosystem_1_1block__info_1_1latest__block__batch__info__result_1ad6bb99259a46f73549ee37819affcc1a}





### `public `[`error_code_enum`](#structeosiosystem_1_1block__info_1_1latest__block__batch__info__result_1aae67f275b3852dbc62dcfbc8be6e7e8c)` error_code` {#structeosiosystem_1_1block__info_1_1latest__block__batch__info__result_1ae64b5eb7efe7ddafb9aa3e260dc4fa8e}






# class `system_contract` {#classeosiosystem_1_1system__contract}

```
class system_contract
  : public eosiosystem::native
```  



The `eosio.system` smart contract is provided by `block.one` as a sample system contract, and it defines the structures and actions needed for blockchain's core functionality.

Just like in the `eosio.bios` sample contract implementation, there are a few actions which are not implemented at the contract level (`newaccount`, `updateauth`, `deleteauth`, `linkauth`, `unlinkauth`, `canceldelay`, `onerror`, `setabi`, `setcode`), they are just declared in the contract so they will show in the contract's ABI and users will be able to push those actions to the chain via the account holding the `eosio.system` contract, but the implementation is at the EOSIO core level. They are referred to as EOSIO native actions.



* Users can stake tokens for CPU and Network bandwidth, and then vote for producers or delegate their vote to a proxy.


* Producers register in order to be voted for, and can claim per-block and per-vote rewards.


* Users can buy and sell RAM at a market-determined price.


* Users can bid on premium names.


* A resource exchange system (REX) allows token holders to lend their tokens, and users to rent CPU and Network resources in return for a market-determined fee.


* A resource market separate from REX: `power`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``registration``](#classeosiosystem_1_1system__contract_1_1registration)        | 
`public  system_contract(name s,name code,datastream< const char * > ds)` | 
`public  ~system_contract()` | 
`public void init(unsigned_int version,const symbol & core)` | 
`public void emit()` | 
`public void onblock(ignore< `[`block_header`](#structeosiosystem_1_1block__header)` > header)` | 
`public void setalimits(const name & account,int64_t ram_bytes,int64_t net_weight,int64_t cpu_weight)` | 
`public void setacctram(const name & account,const std::optional< int64_t > & ram_bytes)` | 
`public void setacctnet(const name & account,const std::optional< int64_t > & net_weight)` | 
`public void setacctcpu(const name & account,const std::optional< int64_t > & cpu_weight)` | 
`public void activate(const eosio::checksum256 & feature_digest)` | 
`public void delegatebw(const name & from,const name & receiver,const asset & stake_net_quantity,const asset & stake_cpu_quantity,bool transfer)` | 
`public void setrex(const asset & balance)` | 
`public void deposit(const name & owner,const asset & amount)` | 
`public void withdraw(const name & owner,const asset & amount)` | 
`public void buyrex(const name & from,const asset & amount)` | 
`public void unstaketorex(const name & owner,const name & receiver,const asset & from_net,const asset & from_cpu)` | 
`public void sellrex(const name & from,const asset & rex)` | 
`public void cnclrexorder(const name & owner)` | 
`public void rentcpu(const name & from,const name & receiver,const asset & loan_payment,const asset & loan_fund)` | 
`public void rentnet(const name & from,const name & receiver,const asset & loan_payment,const asset & loan_fund)` | 
`public void fundcpuloan(const name & from,uint64_t loan_num,const asset & payment)` | 
`public void fundnetloan(const name & from,uint64_t loan_num,const asset & payment)` | 
`public void defcpuloan(const name & from,uint64_t loan_num,const asset & amount)` | 
`public void defnetloan(const name & from,uint64_t loan_num,const asset & amount)` | 
`public void updaterex(const name & owner)` | 
`public void rexexec(const name & user,uint16_t max)` | 
`public void consolidate(const name & owner)` | 
`public void mvtosavings(const name & owner,const asset & rex)` | 
`public void mvfrsavings(const name & owner,const asset & rex)` | 
`public void closerex(const name & owner)` | 
`public void undelegatebw(const name & from,const name & receiver,const asset & unstake_net_quantity,const asset & unstake_cpu_quantity)` | 
`public void buyram(const name & payer,const name & receiver,const asset & quant)` | 
`public void buyrambytes(const name & payer,const name & receiver,uint32_t bytes)` | 
`public void sellram(const name & account,int64_t bytes)` | 
`public void refund(const name & owner)` | 
`public void regproducer(const name & producer,const public_key & producer_key,const std::string & url,uint16_t location)` | 
`public void regproducer2(const name & producer,const eosio::block_signing_authority & producer_authority,const std::string & url,uint16_t location)` | 
`public void unregprod(const name & producer)` | 
`public void setram(uint64_t max_ram_size)` | 
`public void setramrate(uint16_t bytes_per_block)` | 
`public void voteproducer(const name & voter,const name & proxy,const std::vector< name > & producers)` | 
`public void voteupdate(const name & voter_name)` | 
`public void regproxy(const name & proxy,bool isproxy)` | 
`public void setparams(const `[`blockchain_parameters_t`](#namespaceeosiosystem_1a5e1fbfc9229b1616bfc70a519e26e9c2)` & params)` | 
`public void claimrewards(const name & owner)` | 
`public void setpriv(const name & account,uint8_t is_priv)` | 
`public void rmvproducer(const name & producer)` | 
`public void updtrevision(uint8_t revision)` | 
`public void bidname(const name & bidder,const name & newname,const asset & bid)` | 
`public void bidrefund(const name & bidder,const name & newname)` | 
`public void setinflation(int64_t annual_rate,int64_t inflation_pay_factor,int64_t votepay_factor)` | 
`public void cfgpowerup(`[`powerup_config`](#structeosiosystem_1_1powerup__config)` & args)` | 
`public void powerupexec(const name & user,uint16_t max)` | 
`public void powerup(const name & payer,const name & receiver,uint32_t days,int64_t net_frac,int64_t cpu_frac,const asset & max_payment)` | 
`public void limitauthchg(const name & account,const std::vector< name > & allow_perms,const std::vector< name > & disallow_perms)` | 

## Members

### `class `[``registration``](#classeosiosystem_1_1system__contract_1_1registration) {#classeosiosystem_1_1system__contract_1_1registration}




### `public  system_contract(name s,name code,datastream< const char * > ds)` {#classeosiosystem_1_1system__contract_1ae1a0434a7adf53cc3a168f1b2f947ebd}





### `public  ~system_contract()` {#classeosiosystem_1_1system__contract_1ae0264c3f2d2a640d9a60a4c9c9ca089c}





### `public void init(unsigned_int version,const symbol & core)` {#classeosiosystem_1_1system__contract_1a63afe62bd82d52230be1e0ded1bdb644}



The Init action initializes the system contract for a version and a symbol. Only succeeds when:

* version is 0 and


* symbol is found and


* system token supply is greater than 0,


* and system contract wasn’t already been initialized.






#### Parameters
* `version` - the version, has to be 0, 


* `core` - the system symbol.

### `public void emit()` {#classeosiosystem_1_1system__contract_1a139df610c139741a86ef0de91f2ad4d9}





### `public void onblock(ignore< `[`block_header`](#structeosiosystem_1_1block__header)` > header)` {#classeosiosystem_1_1system__contract_1ae75458e3f898b3bc834311fa54abc6a0}



On block action. This special action is triggered when a block is applied by the given producer and cannot be generated from any other source. It is used to pay producers and calculate missed blocks of other producers. Producer pay is deposited into the producer's stake balance and can be withdrawn over time. Once a minute, it may update the active producer config from the producer votes. The action also populates the blockinfo table.


#### Parameters
* `header` - the block header produced.

### `public void setalimits(const name & account,int64_t ram_bytes,int64_t net_weight,int64_t cpu_weight)` {#classeosiosystem_1_1system__contract_1ad5b9178dfbe60ba6059c52d488ecf303}



Set account limits action sets the resource limits of an account


#### Parameters
* `account` - name of the account whose resource limit to be set, 


* `ram_bytes` - ram limit in absolute bytes, 


* `net_weight` - fractionally proportionate net limit of available resources based on (weight / total_weight_of_all_accounts), 


* `cpu_weight` - fractionally proportionate cpu limit of available resources based on (weight / total_weight_of_all_accounts).

### `public void setacctram(const name & account,const std::optional< int64_t > & ram_bytes)` {#classeosiosystem_1_1system__contract_1acdd7c75402f43876338d33649d2e6903}



Set account RAM limits action, which sets the RAM limits of an account


#### Parameters
* `account` - name of the account whose resource limit to be set, 


* `ram_bytes` - ram limit in absolute bytes.

### `public void setacctnet(const name & account,const std::optional< int64_t > & net_weight)` {#classeosiosystem_1_1system__contract_1aa4559928f468c62867916d1251fa33b3}



Set account NET limits action, which sets the NET limits of an account


#### Parameters
* `account` - name of the account whose resource limit to be set, 


* `net_weight` - fractionally proportionate net limit of available resources based on (weight / total_weight_of_all_accounts).

### `public void setacctcpu(const name & account,const std::optional< int64_t > & cpu_weight)` {#classeosiosystem_1_1system__contract_1a9a005d230746b68cafa934a067f287af}



Set account CPU limits action, which sets the CPU limits of an account


#### Parameters
* `account` - name of the account whose resource limit to be set, 


* `cpu_weight` - fractionally proportionate cpu limit of available resources based on (weight / total_weight_of_all_accounts).

### `public void activate(const eosio::checksum256 & feature_digest)` {#classeosiosystem_1_1system__contract_1a1873247483b285e19010b7469419a60d}



The activate action, activates a protocol feature


#### Parameters
* `feature_digest` - hash of the protocol feature to activate.

### `public void delegatebw(const name & from,const name & receiver,const asset & stake_net_quantity,const asset & stake_cpu_quantity,bool transfer)` {#classeosiosystem_1_1system__contract_1aa54b498595abb1a3ad9c62c597d4f7b5}



Delegate bandwidth and/or cpu action. Stakes SYS from the balance of `from` for the benefit of `receiver`.


#### Parameters
* `from` - the account to delegate bandwidth from, that is, the account holding tokens to be staked, 


* `receiver` - the account to delegate bandwidth to, that is, the account to whose resources staked tokens are added 


* `stake_net_quantity` - tokens staked for NET bandwidth, 


* `stake_cpu_quantity` - tokens staked for CPU bandwidth, 


* `transfer` - if true, ownership of staked tokens is transferred to `receiver`.




All producers `from` account has voted for will have their votes updated immediately.

### `public void setrex(const asset & balance)` {#classeosiosystem_1_1system__contract_1a1b875a922b7ab8079b742eb8e714ae48}



Setrex action, sets total_rent balance of REX pool to the passed value. 
#### Parameters
* `balance` - amount to set the REX pool balance.

### `public void deposit(const name & owner,const asset & amount)` {#classeosiosystem_1_1system__contract_1a99e6b1b401c6a8a023f61ed2b52e98d7}



Deposit to REX fund action. Deposits core tokens to user REX fund. All proceeds and expenses related to REX are added to or taken out of this fund. An inline transfer from 'owner' liquid balance is executed. All REX-related costs and proceeds are deducted from and added to 'owner' REX fund, with one exception being buying REX using staked tokens. Storage change is billed to 'owner'.


#### Parameters
* `owner` - REX fund owner account, 


* `amount` - amount of tokens to be deposited.

### `public void withdraw(const name & owner,const asset & amount)` {#classeosiosystem_1_1system__contract_1a45eea3c4ce35174eb1c3ad1e64954d5e}



Withdraw from REX fund action, withdraws core tokens from user REX fund. An inline token transfer to user balance is executed.


#### Parameters
* `owner` - REX fund owner account, 


* `amount` - amount of tokens to be withdrawn.

### `public void buyrex(const name & from,const asset & amount)` {#classeosiosystem_1_1system__contract_1a36aebc85b90ecf7e5389f8daea64592a}



Buyrex action, buys REX in exchange for tokens taken out of user's REX fund by transferring core tokens from user REX fund and converts them to REX stake. By buying REX, user is lending tokens in order to be rented as CPU or NET resources. Storage change is billed to 'from' account.


#### Parameters
* `from` - owner account name, 


* `amount` - amount of tokens taken out of 'from' REX fund.




A voting requirement must be satisfied before action can be executed. 

User must vote for at least 21 producers or delegate vote to proxy before buying REX.

User votes are updated following this action. 

Tokens used in purchase are added to user's voting power. 

Bought REX cannot be sold before 4 days counting from end of day of purchase.

### `public void unstaketorex(const name & owner,const name & receiver,const asset & from_net,const asset & from_cpu)` {#classeosiosystem_1_1system__contract_1a94675167323c97d0dcdc92c5b7f0df60}



Unstaketorex action, uses staked core tokens to buy REX. Storage change is billed to 'owner' account.


#### Parameters
* `owner` - owner of staked tokens, 


* `receiver` - account name that tokens have previously been staked to, 


* `from_net` - amount of tokens to be unstaked from NET bandwidth and used for REX purchase, 


* `from_cpu` - amount of tokens to be unstaked from CPU bandwidth and used for REX purchase.




A voting requirement must be satisfied before action can be executed. 

User must vote for at least 21 producers or delegate vote to proxy before buying REX.

User votes are updated following this action. 

Tokens used in purchase are added to user's voting power. 

Bought REX cannot be sold before 4 days counting from end of day of purchase.

### `public void sellrex(const name & from,const asset & rex)` {#classeosiosystem_1_1system__contract_1a9ee2d79b7e9c1432f312535936e4848f}



Sellrex action, sells REX in exchange for core tokens by converting REX stake back into core tokens at current exchange rate. If order cannot be processed, it gets queued until there is enough in REX pool to fill order, and will be processed within 30 days at most. If successful, user votes are updated, that is, proceeds are deducted from user's voting power. In case sell order is queued, storage change is billed to 'from' account.


#### Parameters
* `from` - owner account of REX, 


* `rex` - amount of REX to be sold.

### `public void cnclrexorder(const name & owner)` {#classeosiosystem_1_1system__contract_1ac4bc1aa3fe5d72c9b1ed8af258c9f935}



Cnclrexorder action, cancels unfilled REX sell order by owner if one exists.


#### Parameters
* `owner` - owner account name.




Order cannot be cancelled once it's been filled.

### `public void rentcpu(const name & from,const name & receiver,const asset & loan_payment,const asset & loan_fund)` {#classeosiosystem_1_1system__contract_1a2babe24ecc07b5576ce48c0b7220e7f4}



Rentcpu action, uses payment to rent as many SYS tokens as possible as determined by market price and stake them for CPU for the benefit of receiver, after 30 days the rented core delegation of CPU will expire. At expiration, if balance is greater than or equal to `loan_payment`, `loan_payment` is taken out of loan balance and used to renew the loan. Otherwise, the loan is closed and user is refunded any remaining balance. Owner can fund or refund a loan at any time before its expiration. All loan expenses and refunds come out of or are added to owner's REX fund.


#### Parameters
* `from` - account creating and paying for CPU loan, 'from' account can add tokens to loan balance using action `fundcpuloan` and withdraw from loan balance using `defcpuloan`


* `receiver` - account receiving rented CPU resources, 


* `loan_payment` - tokens paid for the loan, it has to be greater than zero, amount of rented resources is calculated from `loan_payment`, 


* `loan_fund` - additional tokens can be zero, and is added to loan balance. Loan balance represents a reserve that is used at expiration for automatic loan renewal.

### `public void rentnet(const name & from,const name & receiver,const asset & loan_payment,const asset & loan_fund)` {#classeosiosystem_1_1system__contract_1a89b5465c60b08ecb06538ea162751319}



Rentnet action, uses payment to rent as many SYS tokens as possible as determined by market price and stake them for NET for the benefit of receiver, after 30 days the rented core delegation of NET will expire. At expiration, if balance is greater than or equal to `loan_payment`, `loan_payment` is taken out of loan balance and used to renew the loan. Otherwise, the loan is closed and user is refunded any remaining balance. Owner can fund or refund a loan at any time before its expiration. All loan expenses and refunds come out of or are added to owner's REX fund.


#### Parameters
* `from` - account creating and paying for NET loan, 'from' account can add tokens to loan balance using action `fundnetloan` and withdraw from loan balance using `defnetloan`, 


* `receiver` - account receiving rented NET resources, 


* `loan_payment` - tokens paid for the loan, it has to be greater than zero, amount of rented resources is calculated from `loan_payment`, 


* `loan_fund` - additional tokens can be zero, and is added to loan balance. Loan balance represents a reserve that is used at expiration for automatic loan renewal.

### `public void fundcpuloan(const name & from,uint64_t loan_num,const asset & payment)` {#classeosiosystem_1_1system__contract_1aed60ee281d5277819ed1335322b2d53f}



Fundcpuloan action, transfers tokens from REX fund to the fund of a specific CPU loan in order to be used for loan renewal at expiry.


#### Parameters
* `from` - loan creator account, 


* `loan_num` - loan id, 


* `payment` - tokens transferred from REX fund to loan fund.

### `public void fundnetloan(const name & from,uint64_t loan_num,const asset & payment)` {#classeosiosystem_1_1system__contract_1a8e99bf65da50dc92089140618112db27}



Fundnetloan action, transfers tokens from REX fund to the fund of a specific NET loan in order to be used for loan renewal at expiry.


#### Parameters
* `from` - loan creator account, 


* `loan_num` - loan id, 


* `payment` - tokens transferred from REX fund to loan fund.

### `public void defcpuloan(const name & from,uint64_t loan_num,const asset & amount)` {#classeosiosystem_1_1system__contract_1a94e2f4698dd0ad80e4252a772d424481}



Defcpuloan action, withdraws tokens from the fund of a specific CPU loan and adds them to REX fund.


#### Parameters
* `from` - loan creator account, 


* `loan_num` - loan id, 


* `amount` - tokens transferred from CPU loan fund to REX fund.

### `public void defnetloan(const name & from,uint64_t loan_num,const asset & amount)` {#classeosiosystem_1_1system__contract_1a56a54ec0ca8f37271fbcbc9cc5181145}



Defnetloan action, withdraws tokens from the fund of a specific NET loan and adds them to REX fund.


#### Parameters
* `from` - loan creator account, 


* `loan_num` - loan id, 


* `amount` - tokens transferred from NET loan fund to REX fund.

### `public void updaterex(const name & owner)` {#classeosiosystem_1_1system__contract_1a33a33fedadd8b07f8b9fcee22e1a966d}



Updaterex action, updates REX owner vote weight to current value of held REX tokens.


#### Parameters
* `owner` - REX owner account.

### `public void rexexec(const name & user,uint16_t max)` {#classeosiosystem_1_1system__contract_1a21d675936f040b2dcdcebff3765a60a7}



Rexexec action, processes max CPU loans, max NET loans, and max queued sellrex orders. Action does not execute anything related to a specific user.


#### Parameters
* `user` - any account can execute this action, 


* `max` - number of each of CPU loans, NET loans, and sell orders to be processed.

### `public void consolidate(const name & owner)` {#classeosiosystem_1_1system__contract_1ac6c59d9470ffe96336455b92804aa4de}



Consolidate action, consolidates REX maturity buckets into one bucket that can be sold after 4 days starting from the end of the day.


#### Parameters
* `owner` - REX owner account name.

### `public void mvtosavings(const name & owner,const asset & rex)` {#classeosiosystem_1_1system__contract_1ac673c662e873032e4a67b1d888b23e6f}



Mvtosavings action, moves a specified amount of REX into savings bucket. REX savings bucket never matures. In order for it to be sold, it has to be moved explicitly out of that bucket. Then the moved amount will have the regular maturity period of 4 days starting from the end of the day.


#### Parameters
* `owner` - REX owner account name. 


* `rex` - amount of REX to be moved.

### `public void mvfrsavings(const name & owner,const asset & rex)` {#classeosiosystem_1_1system__contract_1a975cbc9b4670f245c76b0e3f3c86136f}



Mvfrsavings action, moves a specified amount of REX out of savings bucket. The moved amount will have the regular REX maturity period of 4 days.


#### Parameters
* `owner` - REX owner account name. 


* `rex` - amount of REX to be moved.

### `public void closerex(const name & owner)` {#classeosiosystem_1_1system__contract_1a0a1b64d68fa08a63ee570a58d45e5626}



Closerex action, deletes owner records from REX tables and frees used RAM. Owner must not have an outstanding REX balance.


#### Parameters
* `owner` - user account name.




If owner has a non-zero REX balance, the action fails; otherwise, owner REX balance entry is deleted. 

If owner has no outstanding loans and a zero REX fund balance, REX fund entry is deleted.

### `public void undelegatebw(const name & from,const name & receiver,const asset & unstake_net_quantity,const asset & unstake_cpu_quantity)` {#classeosiosystem_1_1system__contract_1a4db0be2c90d342ecd269fdbb57c51091}



Undelegate bandwidth action, decreases the total tokens delegated by `from` to `receiver` and/or frees the memory associated with the delegation if there is nothing left to delegate. This will cause an immediate reduction in net/cpu bandwidth of the receiver. A transaction is scheduled to send the tokens back to `from` after the staking period has passed. If existing transaction is scheduled, it will be canceled and a new transaction issued that has the combined undelegated amount. The `from` account loses voting power as a result of this call and all producer tallies are updated.


#### Parameters
* `from` - the account to undelegate bandwidth from, that is, the account whose tokens will be unstaked, 


* `receiver` - the account to undelegate bandwidth to, that is, the account to whose benefit tokens have been staked, 


* `unstake_net_quantity` - tokens to be unstaked from NET bandwidth, 


* `unstake_cpu_quantity` - tokens to be unstaked from CPU bandwidth,




Unstaked tokens are transferred to `from` liquid balance via a deferred transaction with a delay of 3 days. 

If called during the delay period of a previous `undelegatebw` action, pending action is canceled and timer is reset. 

All producers `from` account has voted for will have their votes updated immediately. 

Bandwidth and storage for the deferred transaction are billed to `from`.

### `public void buyram(const name & payer,const name & receiver,const asset & quant)` {#classeosiosystem_1_1system__contract_1a04be77ea83f87d1533606390c37cf5d1}



Buy ram action, increases receiver's ram quota based upon current price and quantity of tokens provided. An inline transfer from receiver to system contract of tokens will be executed.


#### Parameters
* `payer` - the ram buyer, 


* `receiver` - the ram receiver, 


* `quant` - the quantity of tokens to buy ram with.





When buying ram the payer irreversibly transfers quant to system contract and only the receiver may reclaim the tokens via the sellram action. The receiver pays for the storage of all database records associated with this action.

RAM is a scarce resource whose supply is defined by global properties max_ram_size. RAM is priced using the bancor algorithm such that price-per-byte with a constant reserve ratio of 100:1.

### `public void buyrambytes(const name & payer,const name & receiver,uint32_t bytes)` {#classeosiosystem_1_1system__contract_1a93950629ac6f931b47542727a5411097}



Buy a specific amount of ram bytes action. Increases receiver's ram in quantity of bytes provided. An inline transfer from receiver to system contract of tokens will be executed.


#### Parameters
* `payer` - the ram buyer, 


* `receiver` - the ram receiver, 


* `bytes` - the quantity of ram to buy specified in bytes.





This action will buy an exact amount of ram and bill the payer the current market price.

### `public void sellram(const name & account,int64_t bytes)` {#classeosiosystem_1_1system__contract_1a6b00b900a128d2718244ac8a408f65d3}



Sell ram action, reduces quota by bytes and then performs an inline transfer of tokens to receiver based upon the average purchase price of the original quota.


#### Parameters
* `account` - the ram seller account, 


* `bytes` - the amount of ram to sell in bytes.





The system contract now buys and sells RAM allocations at prevailing market prices. This may result in traders buying RAM today in anticipation of potential shortages tomorrow. Overall this will result in the market balancing the supply and demand for RAM over time.

### `public void refund(const name & owner)` {#classeosiosystem_1_1system__contract_1a10a63e006f9869caeaf2592bdfbccc42}



Refund action, this action is called after the delegation-period to claim all pending unstaked tokens belonging to owner.


#### Parameters
* `owner` - the owner of the tokens claimed.

### `public void regproducer(const name & producer,const public_key & producer_key,const std::string & url,uint16_t location)` {#classeosiosystem_1_1system__contract_1a252441c7b5811068d336f37ab627ecd9}



Register producer action, indicates that a particular account wishes to become a producer, this action will create a `producer_config` and a `[producer_info](#structeosiosystem_1_1producer__info)` object for `producer` scope in producers tables.


#### Parameters
* `producer` - account registering to be a producer candidate, 


* `producer_key` - the public key of the block producer, this is the key used by block producer to sign blocks, 


* `url` - the url of the block producer, normally the url of the block producer presentation website, 


* `location` - is the country code as defined in the ISO 3166, [https://en.wikipedia.org/wiki/List_of_ISO_3166_country_codes](https://en.wikipedia.org/wiki/List_of_ISO_3166_country_codes)




Producer to register is an account 

Authority of producer to register

### `public void regproducer2(const name & producer,const eosio::block_signing_authority & producer_authority,const std::string & url,uint16_t location)` {#classeosiosystem_1_1system__contract_1a6c1143de786b7d7601ac0b0968cb0f19}



Register producer action, indicates that a particular account wishes to become a producer, this action will create a `producer_config` and a `[producer_info](#structeosiosystem_1_1producer__info)` object for `producer` scope in producers tables.


#### Parameters
* `producer` - account registering to be a producer candidate, 


* `producer_authority` - the weighted threshold multisig block signing authority of the block producer used to sign blocks, 


* `url` - the url of the block producer, normally the url of the block producer presentation website, 


* `location` - is the country code as defined in the ISO 3166, [https://en.wikipedia.org/wiki/List_of_ISO_3166_country_codes](https://en.wikipedia.org/wiki/List_of_ISO_3166_country_codes)




Producer to register is an account 

Authority of producer to register

### `public void unregprod(const name & producer)` {#classeosiosystem_1_1system__contract_1a0b8c45d3226929472bc5785742c05152}



Unregister producer action, deactivates the block producer with account name `producer`.

Deactivate the block producer with account name `producer`. 
#### Parameters
* `producer` - the block producer account to unregister.

### `public void setram(uint64_t max_ram_size)` {#classeosiosystem_1_1system__contract_1ad8a6eb47fd97c9f243019d93916ff78f}



Set ram action sets the ram supply. 
#### Parameters
* `max_ram_size` - the amount of ram supply to set.

### `public void setramrate(uint16_t bytes_per_block)` {#classeosiosystem_1_1system__contract_1a7d984add31b6060bb59d472f9f1bd1a1}



Set ram rate action, sets the rate of increase of RAM in bytes per block. It is capped by the uint16_t to a maximum rate of 3 TB per year. If update_ram_supply hasn't been called for the most recent block, then new ram will be allocated at the old rate up to the present block before switching the rate.


#### Parameters
* `bytes_per_block` - the amount of bytes per block increase to set.

### `public void voteproducer(const name & voter,const name & proxy,const std::vector< name > & producers)` {#classeosiosystem_1_1system__contract_1a19d51a2b9b57ffb656612c280ee4ab4e}



Vote producer action, votes for a set of producers. This action updates the list of `producers` voted for, for `voter` account. If voting for a `proxy`, the producer votes will not change until the proxy updates their own vote. Voter can vote for a proxy **or** a list of at most 30 producers. Storage change is billed to `voter`.


#### Parameters
* `voter` - the account to change the voted producers for, 


* `proxy` - the proxy to change the voted producers for, 


* `producers` - the list of producers to vote for, a maximum of 30 producers is allowed.




Producers must be sorted from lowest to highest and must be registered and active 

If proxy is set then no producers can be voted for 

If proxy is set then proxy account must exist and be registered as a proxy 

Every listed producer or proxy must have been previously registered 

Voter must authorize this action 

Voter must have previously staked some EOS for voting 

Voter->staked must be up to date

Every producer previously voted for will have vote reduced by previous vote weight 

Every producer newly voted for will have vote increased by new vote amount 

Prior proxy will proxied_vote_weight decremented by previous vote weight 

New proxy will proxied_vote_weight incremented by new vote weight

### `public void voteupdate(const name & voter_name)` {#classeosiosystem_1_1system__contract_1afd8f9ea7890c647010bc9bccdcda6ba9}



Update the vote weight for the producers or proxy `voter_name` currently votes for. This will also update the `staked` value for the `voter_name` by checking `rexbal` and all delegated NET and CPU.


#### Parameters
* `voter_name` - the account to update the votes for,




the voter.staked will be updated 

previously voted for producers vote weight will be updated with new weight 

previously voted for proxy vote weight will be updated with new weight

### `public void regproxy(const name & proxy,bool isproxy)` {#classeosiosystem_1_1system__contract_1a7192c64e5a9d0b9b202390dbfade0858}



Register proxy action, sets `proxy` account as proxy. An account marked as a proxy can vote with the weight of other accounts which have selected it as a proxy. Other accounts must refresh their voteproducer to update the proxy's weight. Storage change is billed to `proxy`.


#### Parameters
* `proxy` - the account registering as voter proxy (or unregistering), 


* `isproxy` - if true, proxy is registered; if false, proxy is unregistered.




Proxy must have something staked (existing row in voters table) 

New state must be different than current state

### `public void setparams(const `[`blockchain_parameters_t`](#namespaceeosiosystem_1a5e1fbfc9229b1616bfc70a519e26e9c2)` & params)` {#classeosiosystem_1_1system__contract_1aa4ea1b93cfb3d99fcaaabb994c711bee}



Set the blockchain parameters. By tunning these parameters a degree of customization can be achieved. 
#### Parameters
* `params` - New blockchain parameters to set.

### `public void claimrewards(const name & owner)` {#classeosiosystem_1_1system__contract_1a34b35d1f073383e599d4e2bb56e20524}



Claim rewards action, claims block producing and vote rewards. 
#### Parameters
* `owner` - producer account claiming per-block and per-vote rewards.

### `public void setpriv(const name & account,uint8_t is_priv)` {#classeosiosystem_1_1system__contract_1a648ec27a9bc3bf7e36c5c88f6932b9ca}



Set privilege status for an account. Allows to set privilege status for an account (turn it on/off). 
#### Parameters
* `account` - the account to set the privileged status for. 


* `is_priv` - 0 for false, > 0 for true.

### `public void rmvproducer(const name & producer)` {#classeosiosystem_1_1system__contract_1a2a41dc1871059a536a55626b8c76f5b9}



Remove producer action, deactivates a producer by name, if not found asserts. 
#### Parameters
* `producer` - the producer account to deactivate.

### `public void updtrevision(uint8_t revision)` {#classeosiosystem_1_1system__contract_1a0af4a55018801131ae7dc7a923bead0b}



Update revision action, updates the current revision. 
#### Parameters
* `revision` - it has to be incremented by 1 compared with current revision.




Current revision can not be higher than 254, and has to be smaller than or equal 1 (“set upper bound to greatest revision supported in the code”).

### `public void bidname(const name & bidder,const name & newname,const asset & bid)` {#classeosiosystem_1_1system__contract_1af1c329fbf0e3e45b62b729e6ee743c62}



Bid name action, allows an account `bidder` to place a bid for a name `newname`. 
#### Parameters
* `bidder` - the account placing the bid, 


* `newname` - the name the bid is placed for, 


* `bid` - the amount of system tokens payed for the bid.




Bids can be placed only on top-level suffix, 

Non empty name, 

Names longer than 12 chars are not allowed, 

Names equal with 12 chars can be created without placing a bid, 

Bid has to be bigger than zero, 

Bid's symbol must be system token, 

Bidder account has to be different than current highest bidder, 

Bid must increase current bid by 10%, 

Auction must still be opened.

### `public void bidrefund(const name & bidder,const name & newname)` {#classeosiosystem_1_1system__contract_1a1ad9f05ad7242412bf5ad87706f923ff}



Bid refund action, allows the account `bidder` to get back the amount it bid so far on a `newname` name.


#### Parameters
* `bidder` - the account that gets refunded, 


* `newname` - the name for which the bid was placed and now it gets refunded for.

### `public void setinflation(int64_t annual_rate,int64_t inflation_pay_factor,int64_t votepay_factor)` {#classeosiosystem_1_1system__contract_1ac2cab12a3c2a1d20a3215124100cf3e1}



Change the annual inflation rate of the core token supply and specify how the new issued tokens will be distributed based on the following structure.


#### Parameters
* `annual_rate` - Annual inflation rate of the core token supply. (eg. For 5% Annual inflation => annual_rate=500 For 1.5% Annual inflation => annual_rate=150 


* `inflation_pay_factor` - Inverse of the fraction of the inflation used to reward block producers. The remaining inflation will be sent to the `eosio.saving` account. (eg. For 20% of inflation going to block producer rewards => inflation_pay_factor = 50000 For 100% of inflation going to block producer rewards => inflation_pay_factor = 10000). 


* `votepay_factor` - Inverse of the fraction of the block producer rewards to be distributed proportional to blocks produced. The remaining rewards will be distributed proportional to votes received. (eg. For 25% of block producer rewards going towards block pay => votepay_factor = 40000 For 75% of block producer rewards going towards block pay => votepay_factor = 13333).

### `public void cfgpowerup(`[`powerup_config`](#structeosiosystem_1_1powerup__config)` & args)` {#classeosiosystem_1_1system__contract_1ae71212071f747832a2a56eb4868d9c81}



Configure the `power` market. The market becomes available the first time this action is invoked.

### `public void powerupexec(const name & user,uint16_t max)` {#classeosiosystem_1_1system__contract_1aa573d628b237c167aa99fc71cb150736}



Process power queue and update state. Action does not execute anything related to a specific user.


#### Parameters
* `user` - any account can execute this action 


* `max` - number of queue items to process

### `public void powerup(const name & payer,const name & receiver,uint32_t days,int64_t net_frac,int64_t cpu_frac,const asset & max_payment)` {#classeosiosystem_1_1system__contract_1a998b5936930f7ce0f60df2b6a8404926}



Powerup NET and CPU resources by percentage


#### Parameters
* `payer` - the resource buyer 


* `receiver` - the resource receiver 


* `days` - number of days of resource availability. Must match market configuration. 


* `net_frac` - fraction of net (100% = 10^15) managed by this market 


* `cpu_frac` - fraction of cpu (100% = 10^15) managed by this market 


* `max_payment` - the maximum amount `payer` is willing to pay. Tokens are withdrawn from `payer`'s token balance.

### `public void limitauthchg(const name & account,const std::vector< name > & allow_perms,const std::vector< name > & disallow_perms)` {#classeosiosystem_1_1system__contract_1ab940f454d4d3d0018f22bf472caf3b52}



limitauthchg opts into or out of restrictions on updateauth, deleteauth, linkauth, and unlinkauth.

If either allow_perms or disallow_perms is non-empty, then opts into restrictions. If allow_perms is non-empty, then the authorized_by argument of the restricted actions must be in the vector, or the actions will abort. If disallow_perms is non-empty, then the authorized_by argument of the restricted actions must not be in the vector, or the actions will abort.

If both allow_perms and disallow_perms are empty, then opts out of the restrictions. limitauthchg aborts if both allow_perms and disallow_perms are non-empty.


#### Parameters
* `account` - account to change 


* `allow_perms` - permissions which may use the restricted actions 


* `disallow_perms` - permissions which may not use the restricted actions


# class `registration` {#classeosiosystem_1_1system__contract_1_1registration}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[``for_each``](#structeosiosystem_1_1system__contract_1_1registration_1_1for__each)        | 
`struct `[``for_each< P >``](#structeosiosystem_1_1system__contract_1_1registration_1_1for__each_3_01_p_01_4)        | 
`public `[`system_contract`](#classeosiosystem_1_1system__contract)` * this_contract` | 
`public template<typename... Args>`  <br/>`inline constexpr void operator()(Args &&... args)` | 

## Members

### `struct `[``for_each``](#structeosiosystem_1_1system__contract_1_1registration_1_1for__each) {#structeosiosystem_1_1system__contract_1_1registration_1_1for__each}




### `struct `[``for_each< P >``](#structeosiosystem_1_1system__contract_1_1registration_1_1for__each_3_01_p_01_4) {#structeosiosystem_1_1system__contract_1_1registration_1_1for__each_3_01_p_01_4}




### `public `[`system_contract`](#classeosiosystem_1_1system__contract)` * this_contract` {#classeosiosystem_1_1system__contract_1_1registration_1a86e430555979d16ce46d11fbfc4c5673}





### `public template<typename... Args>`  <br/>`inline constexpr void operator()(Args &&... args)` {#classeosiosystem_1_1system__contract_1_1registration_1a766e47b24eb13d3c1f1cc234cbfdb06a}






# struct `for_each` {#structeosiosystem_1_1system__contract_1_1registration_1_1for__each}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members


# struct `for_each< P >` {#structeosiosystem_1_1system__contract_1_1registration_1_1for__each_3_01_p_01_4}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members


# class `native` {#classeosiosystem_1_1native}

```
class native
  : public eosio::contract
```  



The EOSIO core `native` contract that governs authorization and contracts' abi.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void newaccount(const name & creator,const name & name,ignore< `[`authority`](#structeosiosystem_1_1authority)` > owner,ignore< `[`authority`](#structeosiosystem_1_1authority)` > active)` | 
`public inline void updateauth(name account,name permission,name parent,`[`authority`](#structeosiosystem_1_1authority)` auth,binary_extension< name > authorized_by)` | 
`public inline void deleteauth(name account,name permission,binary_extension< name > authorized_by)` | 
`public inline void linkauth(name account,name code,name type,name requirement,binary_extension< name > authorized_by)` | 
`public inline void unlinkauth(name account,name code,name type,binary_extension< name > authorized_by)` | 
`public inline void canceldelay(ignore< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > canceling_auth,ignore< checksum256 > trx_id)` | 
`public void onerror(ignore< uint128_t > sender_id,ignore< std::vector< char > > sent_trx)` | 
`public void setabi(const name & account,const std::vector< char > & abi,const binary_extension< std::string > & memo)` | 
`public inline void setcode(const name & account,uint8_t vmtype,uint8_t vmversion,const std::vector< char > & code,const binary_extension< std::string > & memo)` | 

## Members

### `public void newaccount(const name & creator,const name & name,ignore< `[`authority`](#structeosiosystem_1_1authority)` > owner,ignore< `[`authority`](#structeosiosystem_1_1authority)` > active)` {#classeosiosystem_1_1native_1ab81dda3be834b68780bbae5c2e8368e0}



These actions map one-on-one with the ones defined in core layer of EOSIO, that's where their implementation actually is done. They are present here only so they can show up in the abi file and thus user can send them to this contract, but they have no specific implementation at this contract level, they will execute the implementation at the core layer and nothing else. New account action is called after a new account is created. This code enforces resource-limits rules for new accounts as well as new account naming conventions.

Called after a new account is created. This code enforces resource-limits rules for new accounts as well as new account naming conventions.

Account names containing '.' symbols must have a suffix equal to the name of the creator. This allows users who buy a premium name (shorter than 12 characters with no dots) to be the only ones who can create accounts with the creator's name as a suffix.

### `public inline void updateauth(name account,name permission,name parent,`[`authority`](#structeosiosystem_1_1authority)` auth,binary_extension< name > authorized_by)` {#classeosiosystem_1_1native_1a2bbeca58b24029a5ab0fc90832dde56b}



Update authorization action updates permission for an account.

This contract enforces additional rules:

* If authorized_by is present and not "", then the contract does a require_auth2(account, authorized_by).


* If the account has opted into limitauthchg, then authorized_by must be present and not "".


* If the account has opted into limitauthchg, and allow_perms is not empty, then authorized_by must be in the array.


* If the account has opted into limitauthchg, and disallow_perms is not empty, then authorized_by must not be in the array.





#### Parameters
* `account` - the account for which the permission is updated 


* `permission` - the permission name which is updated 


* `parent` - the parent of the permission which is updated 


* `auth` - the json describing the permission authorization 


* `authorized_by` - the permission which is authorizing this change

### `public inline void deleteauth(name account,name permission,binary_extension< name > authorized_by)` {#classeosiosystem_1_1native_1a49cc638f16ddc898952a8f032ffd6c2c}



Delete authorization action deletes the authorization for an account's permission.

This contract enforces additional rules:

* If authorized_by is present and not "", then the contract does a require_auth2(account, authorized_by).


* If the account has opted into limitauthchg, then authorized_by must be present and not "".


* If the account has opted into limitauthchg, and allow_perms is not empty, then authorized_by must be in the array.


* If the account has opted into limitauthchg, and disallow_perms is not empty, then authorized_by must not be in the array.





#### Parameters
* `account` - the account for which the permission authorization is deleted, 


* `permission` - the permission name been deleted. 


* `authorized_by` - the permission which is authorizing this change

### `public inline void linkauth(name account,name code,name type,name requirement,binary_extension< name > authorized_by)` {#classeosiosystem_1_1native_1a35b93b9e7ae3eaa60619189c7694499e}



Link authorization action assigns a specific action from a contract to a permission you have created. Five system actions can not be linked `updateauth`, `deleteauth`, `linkauth`, `unlinkauth`, and `canceldelay`. This is useful because when doing authorization checks, the EOSIO based blockchain starts with the action needed to be authorized (and the contract belonging to), and looks up which permission is needed to pass authorization validation. If a link is set, that permission is used for authorization validation otherwise then active is the default, with the exception of `eosio.any`. `eosio.any` is an implicit permission which exists on every account; you can link actions to `eosio.any` and that will make it so linked actions are accessible to any permissions defined for the account.

This contract enforces additional rules:

* If authorized_by is present and not "", then the contract does a require_auth2(account, authorized_by).


* If the account has opted into limitauthchg, then authorized_by must be present and not "".


* If the account has opted into limitauthchg, and allow_perms is not empty, then authorized_by must be in the array.


* If the account has opted into limitauthchg, and disallow_perms is not empty, then authorized_by must not be in the array.





#### Parameters
* `account` - the permission's owner to be linked and the payer of the RAM needed to store this link, 


* `code` - the owner of the action to be linked, 


* `type` - the action to be linked, 


* `requirement` - the permission to be linked. 


* `authorized_by` - the permission which is authorizing this change

### `public inline void unlinkauth(name account,name code,name type,binary_extension< name > authorized_by)` {#classeosiosystem_1_1native_1aa1e2097e289d4da3acc2876cc24e8897}



Unlink authorization action it's doing the reverse of linkauth action, by unlinking the given action.

This contract enforces additional rules:

* If authorized_by is present and not "", then the contract does a require_auth2(account, authorized_by).


* If the account has opted into limitauthchg, then authorized_by must be present and not "".


* If the account has opted into limitauthchg, and allow_perms is not empty, then authorized_by must be in the array.


* If the account has opted into limitauthchg, and disallow_perms is not empty, then authorized_by must not be in the array.





#### Parameters
* `account` - the owner of the permission to be unlinked and the receiver of the freed RAM, 


* `code` - the owner of the action to be unlinked, 


* `type` - the action to be unlinked. 


* `authorized_by` - the permission which is authorizing this change

### `public inline void canceldelay(ignore< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > canceling_auth,ignore< checksum256 > trx_id)` {#classeosiosystem_1_1native_1ac2da52c0f6c1698bbe76a84f23917feb}



Cancel delay action cancels a deferred transaction.


#### Parameters
* `canceling_auth` - the permission that authorizes this action, 


* `trx_id` - the deferred transaction id to be cancelled.

### `public void onerror(ignore< uint128_t > sender_id,ignore< std::vector< char > > sent_trx)` {#classeosiosystem_1_1native_1a379fe8f4ca5a42a6011dbf9c8f30b6ff}



On error action, notification of this action is delivered to the sender of a deferred transaction when an objective error occurs while executing the deferred transaction. This action is not meant to be called directly.


#### Parameters
* `sender_id` - the id for the deferred transaction chosen by the sender, 


* `sent_trx` - the deferred transaction that failed.

### `public void setabi(const name & account,const std::vector< char > & abi,const binary_extension< std::string > & memo)` {#classeosiosystem_1_1native_1aff24a543859381c1670183f5b4d343aa}



Set abi action sets the contract abi for an account.


#### Parameters
* `account` - the account for which to set the contract abi. 


* `abi` - the abi content to be set, in the form of a blob binary. 


* `memo` - may be omitted

### `public inline void setcode(const name & account,uint8_t vmtype,uint8_t vmversion,const std::vector< char > & code,const binary_extension< std::string > & memo)` {#classeosiosystem_1_1native_1a225a51ac200eb80061ecbea5980e0b7b}



Set code action sets the contract code for an account.


#### Parameters
* `account` - the account for which to set the contract code. 


* `vmtype` - reserved, set it to zero. 


* `vmversion` - reserved, set it to zero. 


* `code` - the code content to be set, in the form of a blob binary.. 


* `memo` - may be omitted


# struct `abi_hash` {#structeosiosystem_1_1abi__hash}




[abi_hash](#structeosiosystem_1_1abi__hash) is the structure underlying the abihash table and consists of:

* `owner`: the account owner of the contract's abi


* `hash`: is the sha256 hash of the abi/binary

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name owner` | 
`public checksum256 hash` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public name owner` {#structeosiosystem_1_1abi__hash_1a4fb47566cda77ad38ad41fcf4fa3616d}





### `public checksum256 hash` {#structeosiosystem_1_1abi__hash_1aa4a25380a39a47af422f17cbea44ba7a}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1abi__hash_1ad54c525ed4f04c7729f5d46b8e641e30}






# struct `authority` {#structeosiosystem_1_1authority}




Blockchain authority.

An authority is defined by:

* a vector of key_weights (a [key_weight](#structeosiosystem_1_1key__weight) is a public key plus a weight),


* a vector of permission_level_weights, (a permission_level is an account name plus a permission name)


* a vector of wait_weights (a [wait_weight](#structeosiosystem_1_1wait__weight) is defined by a number of seconds to wait and a weight)


* a threshold value

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint32_t threshold` | 
`public std::vector< `[`key_weight`](#structeosiosystem_1_1key__weight)` > keys` | 
`public std::vector< `[`permission_level_weight`](#structeosiosystem_1_1permission__level__weight)` > accounts` | 
`public std::vector< `[`wait_weight`](#structeosiosystem_1_1wait__weight)` > waits` | 

## Members

### `public uint32_t threshold` {#structeosiosystem_1_1authority_1a81af9d5da4986a2630f58039f1b42848}





### `public std::vector< `[`key_weight`](#structeosiosystem_1_1key__weight)` > keys` {#structeosiosystem_1_1authority_1a9143e8ec444196d3e3fd99a47a2df4c8}





### `public std::vector< `[`permission_level_weight`](#structeosiosystem_1_1permission__level__weight)` > accounts` {#structeosiosystem_1_1authority_1ad24536a9a087da188510fec55141ef37}





### `public std::vector< `[`wait_weight`](#structeosiosystem_1_1wait__weight)` > waits` {#structeosiosystem_1_1authority_1a7015a1a5d7dd1bb6a723b7f121f4870f}






# struct `bid_refund` {#structeosiosystem_1_1bid__refund}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name bidder` | 
`public asset amount` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public name bidder` {#structeosiosystem_1_1bid__refund_1ae6bd67f412850f81514ea8b5a5ad4abd}





### `public asset amount` {#structeosiosystem_1_1bid__refund_1aec14d41b70f2332af3e94d84f480077f}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1bid__refund_1a3a7f9c7f81457c17f15ade541c402af1}






# struct `block_header` {#structeosiosystem_1_1block__header}




Blockchain block header.

A block header is defined by:

* a timestamp,


* the producer that created it,


* a confirmed flag default as zero,


* a link to previous block,


* a link to the transaction merkel root,


* a link to action root,


* a schedule version,


* and a producers' schedule.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint32_t timestamp` | 
`public name producer` | 
`public uint16_t confirmed` | 
`public checksum256 previous` | 
`public checksum256 transaction_mroot` | 
`public checksum256 action_mroot` | 
`public uint32_t schedule_version` | 
`public std::optional< eosio::producer_schedule > new_producers` | 

## Members

### `public uint32_t timestamp` {#structeosiosystem_1_1block__header_1a9c9c9cbc1cd8ef72b0fce4d6e81002ec}





### `public name producer` {#structeosiosystem_1_1block__header_1aaa922bddcad01318dc6fc11dc13c5e79}





### `public uint16_t confirmed` {#structeosiosystem_1_1block__header_1a4982fd9b60cbc7a50b5b533af097c373}





### `public checksum256 previous` {#structeosiosystem_1_1block__header_1a777160bdbc82a251b0bfb9c7d6e2e4a8}





### `public checksum256 transaction_mroot` {#structeosiosystem_1_1block__header_1abdae1afa7aa05897fe48322c0973fe7a}





### `public checksum256 action_mroot` {#structeosiosystem_1_1block__header_1a743915ddc889a572f74dbd4f20be28c4}





### `public uint32_t schedule_version` {#structeosiosystem_1_1block__header_1a5a58fc892253b39a20815926440e0637}





### `public std::optional< eosio::producer_schedule > new_producers` {#structeosiosystem_1_1block__header_1a209c1b178d315a0f672d628675f065ac}






# struct `exchange_state` {#structeosiosystem_1_1exchange__state}




Uses Bancor math to create a 50/50 relay between two asset types. The state of the bancor exchange is entirely contained within this struct. There are no external side effects associated with using this API.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[``connector``](#structeosiosystem_1_1exchange__state_1_1connector)        | 
`public asset supply` | 
`public `[`connector`](#structeosiosystem_1_1exchange__state_1_1connector)` base` | 
`public `[`connector`](#structeosiosystem_1_1exchange__state_1_1connector)` quote` | 
`public inline asset convert_to_exchange(`[`connector`](#structeosiosystem_1_1exchange__state_1_1connector)` & c,asset in)` | 
`public inline asset convert_from_exchange(`[`connector`](#structeosiosystem_1_1exchange__state_1_1connector)` & c,asset in)` | 
`public inline asset convert(asset from,const symbol & to)` | 
`public inline uint64_t primary_key() const` | 
`public asset convert_to_exchange(`[`connector`](#structeosiosystem_1_1exchange__state_1_1connector)` & reserve,const asset & payment)` | 
`public asset convert_from_exchange(`[`connector`](#structeosiosystem_1_1exchange__state_1_1connector)` & reserve,const asset & tokens)` | 
`public asset convert(const asset & from,const symbol & to)` | 
`public asset direct_convert(const asset & from,const symbol & to)` | 

## Members

### `struct `[``connector``](#structeosiosystem_1_1exchange__state_1_1connector) {#structeosiosystem_1_1exchange__state_1_1connector}




### `public asset supply` {#structeosiosystem_1_1exchange__state_1a46dd436b7c53a2cc5fb718f18176f55f}





### `public `[`connector`](#structeosiosystem_1_1exchange__state_1_1connector)` base` {#structeosiosystem_1_1exchange__state_1a64022b0822ac4b53ff484590f76ef021}





### `public `[`connector`](#structeosiosystem_1_1exchange__state_1_1connector)` quote` {#structeosiosystem_1_1exchange__state_1a193594141203ddbb6a37d7cf56201f7f}





### `public inline asset convert_to_exchange(`[`connector`](#structeosiosystem_1_1exchange__state_1_1connector)` & c,asset in)` {#structeosiosystem_1_1exchange__state_1a7c029ed83a27b04524911cf1c3f647c8}





### `public inline asset convert_from_exchange(`[`connector`](#structeosiosystem_1_1exchange__state_1_1connector)` & c,asset in)` {#structeosiosystem_1_1exchange__state_1ade7bfd99be01e15093f27d95a3013ba7}





### `public inline asset convert(asset from,const symbol & to)` {#structeosiosystem_1_1exchange__state_1a9b44e4142697e729fe05dc028b932c0e}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1exchange__state_1a124e84f589746ad2bada2ea98af5b5e2}





### `public asset convert_to_exchange(`[`connector`](#structeosiosystem_1_1exchange__state_1_1connector)` & reserve,const asset & payment)` {#structeosiosystem_1_1exchange__state_1aa6e00de0427eba26f16acc1d0c85e5a7}





### `public asset convert_from_exchange(`[`connector`](#structeosiosystem_1_1exchange__state_1_1connector)` & reserve,const asset & tokens)` {#structeosiosystem_1_1exchange__state_1a7056cfffba84abdf75b38f2d81d95ccd}





### `public asset convert(const asset & from,const symbol & to)` {#structeosiosystem_1_1exchange__state_1aff0f484e4eac6b51e3b01839a884e12e}





### `public asset direct_convert(const asset & from,const symbol & to)` {#structeosiosystem_1_1exchange__state_1a048b1798df129a50aade23df905cd87b}






# struct `connector` {#structeosiosystem_1_1exchange__state_1_1connector}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public asset balance` | 
`public double weight` | 

## Members

### `public asset balance` {#structeosiosystem_1_1exchange__state_1_1connector_1aa0c34b770479927ae7d4f0760bc0e574}





### `public double weight` {#structeosiosystem_1_1exchange__state_1_1connector_1a0132eb8bc9c7a9fe1958c98a436e4262}






# struct `delegated_bandwidth` {#structeosiosystem_1_1delegated__bandwidth}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name from` | 
`public name to` | 
`public asset net_weight` | 
`public asset cpu_weight` | 
`public inline bool is_empty() const` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public name from` {#structeosiosystem_1_1delegated__bandwidth_1a390e64c81acb62584280ecdf77e67882}





### `public name to` {#structeosiosystem_1_1delegated__bandwidth_1a45fe0c03daff4ca74728a490a1973f6d}





### `public asset net_weight` {#structeosiosystem_1_1delegated__bandwidth_1afb71866724fce6fda77786d5f1d4eb6a}





### `public asset cpu_weight` {#structeosiosystem_1_1delegated__bandwidth_1a62526659e054a4e788ecfd334056dfdf}





### `public inline bool is_empty() const` {#structeosiosystem_1_1delegated__bandwidth_1a445d41ecfce48fe5e7b73de079a889d8}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1delegated__bandwidth_1acc330b16cef3555d2b8bb1a1547f58dc}






# struct `eosio_global_state` {#structeosiosystem_1_1eosio__global__state}

```
struct eosio_global_state
  : public eosio::blockchain_parameters
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint64_t max_ram_size` | 
`public uint64_t total_ram_bytes_reserved` | 
`public int64_t total_ram_stake` | 
`public block_timestamp last_producer_schedule_update` | 
`public time_point last_pervote_bucket_fill` | 
`public int64_t pervote_bucket` | 
`public int64_t perblock_bucket` | 
`public uint32_t total_unpaid_blocks` | 
`public int64_t total_activated_stake` | all blocks which have been produced but not paid
`public time_point thresh_activated_stake_time` | 
`public uint16_t last_producer_schedule_size` | 
`public double total_producer_vote_weight` | 
`public block_timestamp last_name_close` | the sum of all producer votes
`public inline uint64_t free_ram() const` | 

## Members

### `public uint64_t max_ram_size` {#structeosiosystem_1_1eosio__global__state_1a2a2f2607dd31f0623a7d5185bf967c4d}





### `public uint64_t total_ram_bytes_reserved` {#structeosiosystem_1_1eosio__global__state_1ab11f6efb709f15f9d31c3e8a20897149}





### `public int64_t total_ram_stake` {#structeosiosystem_1_1eosio__global__state_1a491a74bf4176ddd4485941a841fff13a}





### `public block_timestamp last_producer_schedule_update` {#structeosiosystem_1_1eosio__global__state_1a00d9962c27103495ffdae8b14ca89fb4}





### `public time_point last_pervote_bucket_fill` {#structeosiosystem_1_1eosio__global__state_1afabbd0323315bef9ad7b5d2f953a0340}





### `public int64_t pervote_bucket` {#structeosiosystem_1_1eosio__global__state_1a1533ba61f8191c5323d28a19684fe0bd}





### `public int64_t perblock_bucket` {#structeosiosystem_1_1eosio__global__state_1ab7c0fbe51aa0335e5048be97bf453db7}





### `public uint32_t total_unpaid_blocks` {#structeosiosystem_1_1eosio__global__state_1af7d50c559ad0cfffaa68749e16aed7aa}





### `public int64_t total_activated_stake` {#structeosiosystem_1_1eosio__global__state_1a08c4b026bea40e1d1ee500d289e786ad}

all blocks which have been produced but not paid



### `public time_point thresh_activated_stake_time` {#structeosiosystem_1_1eosio__global__state_1a67107f34cfdffa85a1195ed0e64612db}





### `public uint16_t last_producer_schedule_size` {#structeosiosystem_1_1eosio__global__state_1a4e768096f99af94ce4048446c90075a8}





### `public double total_producer_vote_weight` {#structeosiosystem_1_1eosio__global__state_1a40342aff032242dd2a54723c60587d29}





### `public block_timestamp last_name_close` {#structeosiosystem_1_1eosio__global__state_1aa4f0ee20aedd1f86a3f984c57270bfd7}

the sum of all producer votes



### `public inline uint64_t free_ram() const` {#structeosiosystem_1_1eosio__global__state_1ab13e31d124330a1ba278dfb46fdee173}






# struct `eosio_global_state2` {#structeosiosystem_1_1eosio__global__state2}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint16_t new_ram_per_block` | 
`public block_timestamp last_ram_increase` | 
`public block_timestamp last_block_num` | 
`public double total_producer_votepay_share` | 
`public uint8_t revision` | used to track version updates in the future.
`public inline  eosio_global_state2()` | 

## Members

### `public uint16_t new_ram_per_block` {#structeosiosystem_1_1eosio__global__state2_1ad29c5ed6cc975beb7578f57aaf20c98f}





### `public block_timestamp last_ram_increase` {#structeosiosystem_1_1eosio__global__state2_1a7b233e1f64b6da410d227d5891ca399c}





### `public block_timestamp last_block_num` {#structeosiosystem_1_1eosio__global__state2_1a5efff2639a098649fc9f3478a5e7115a}





### `public double total_producer_votepay_share` {#structeosiosystem_1_1eosio__global__state2_1a23b66248b9c355c2fa9d2a3c8eba11b5}





### `public uint8_t revision` {#structeosiosystem_1_1eosio__global__state2_1aa14325e22eebf822987145b396e7fb60}

used to track version updates in the future.



### `public inline  eosio_global_state2()` {#structeosiosystem_1_1eosio__global__state2_1ab1a68ec079eab13d8d945ff9db03cb1f}






# struct `eosio_global_state3` {#structeosiosystem_1_1eosio__global__state3}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public time_point last_vpay_state_update` | 
`public double total_vpay_share_change_rate` | 
`public inline  eosio_global_state3()` | 

## Members

### `public time_point last_vpay_state_update` {#structeosiosystem_1_1eosio__global__state3_1accd351e80b36cfc0ed6db8eebef527d2}





### `public double total_vpay_share_change_rate` {#structeosiosystem_1_1eosio__global__state3_1a346f3101b6b89488cba4d6d4e67d9273}





### `public inline  eosio_global_state3()` {#structeosiosystem_1_1eosio__global__state3_1a8580bac2c916643fb0e5ffd33185419d}






# struct `eosio_global_state4` {#structeosiosystem_1_1eosio__global__state4}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public double continuous_rate` | 
`public int64_t inflation_pay_factor` | 
`public int64_t votepay_factor` | 
`public inline  eosio_global_state4()` | 

## Members

### `public double continuous_rate` {#structeosiosystem_1_1eosio__global__state4_1aea57a6e1843364aeed35c5fc72c51376}





### `public int64_t inflation_pay_factor` {#structeosiosystem_1_1eosio__global__state4_1a5978c2508b9d874e8191992236852b2f}





### `public int64_t votepay_factor` {#structeosiosystem_1_1eosio__global__state4_1a8546257ff3690e0fcb4f73a9c88762b3}





### `public inline  eosio_global_state4()` {#structeosiosystem_1_1eosio__global__state4_1ad1567456a109d93a0308bb1780207abf}






# struct `key_weight` {#structeosiosystem_1_1key__weight}




Weighted key.

A weighted key is defined by a public key and an associated weight.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::public_key key` | 
`public uint16_t weight` | 

## Members

### `public eosio::public_key key` {#structeosiosystem_1_1key__weight_1a31686ad5ac920e70870cf69e6a2dddc6}





### `public uint16_t weight` {#structeosiosystem_1_1key__weight_1a2e8de08d6240bb75204c4d5195489f85}






# struct `limit_auth_change` {#structeosiosystem_1_1limit__auth__change}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public name account` | 
`public std::vector< name > allow_perms` | 
`public std::vector< name > disallow_perms` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public uint8_t version` {#structeosiosystem_1_1limit__auth__change_1ac9ee9788288b853d89f9bbe7ab73ccac}





### `public name account` {#structeosiosystem_1_1limit__auth__change_1a624c1c7a43da37e6697c618801ac1a4c}





### `public std::vector< name > allow_perms` {#structeosiosystem_1_1limit__auth__change_1a9535c07d3294a3a65a69adb9ff8f6301}





### `public std::vector< name > disallow_perms` {#structeosiosystem_1_1limit__auth__change_1a49b0036332a792a390387813cfe20afd}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1limit__auth__change_1afca9e603259b25aca9807294c17d3a5a}






# struct `name_bid` {#structeosiosystem_1_1name__bid}




The `eosio.system` smart contract is provided by `block.one` as a sample system contract, and it defines the structures and actions needed for blockchain's core functionality.

Just like in the `eosio.bios` sample contract implementation, there are a few actions which are not implemented at the contract level (`newaccount`, `updateauth`, `deleteauth`, `linkauth`, `unlinkauth`, `canceldelay`, `onerror`, `setabi`, `setcode`), they are just declared in the contract so they will show in the contract's ABI and users will be able to push those actions to the chain via the account holding the `eosio.system` contract, but the implementation is at the EOSIO core level. They are referred to as EOSIO native actions.



* Users can stake tokens for CPU and Network bandwidth, and then vote for producers or delegate their vote to a proxy.


* Producers register in order to be voted for, and can claim per-block and per-vote rewards.


* Users can buy and sell RAM at a market-determined price.


* Users can bid on premium names.


* A resource exchange system (REX) allows token holders to lend their tokens, and users to rent CPU and Network resources in return for a market-determined fee.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name newname` | 
`public name high_bidder` | 
`public int64_t high_bid` | negative high_bid == closed auction waiting to be claimed
`public time_point last_bid_time` | 
`public inline uint64_t primary_key() const` | 
`public inline uint64_t by_high_bid() const` | 

## Members

### `public name newname` {#structeosiosystem_1_1name__bid_1a3463fcad67e50421775df9e215fcc6f5}





### `public name high_bidder` {#structeosiosystem_1_1name__bid_1a96ebb10d61560583560670e686216783}





### `public int64_t high_bid` {#structeosiosystem_1_1name__bid_1ac9ef960920cc7cf790dbe29b7378a1e6}

negative high_bid == closed auction waiting to be claimed



### `public time_point last_bid_time` {#structeosiosystem_1_1name__bid_1aaf689933142cde0cc33c8a945d5e1dde}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1name__bid_1aee075c874d04b3b4fa03a6b7ba0e1be5}





### `public inline uint64_t by_high_bid() const` {#structeosiosystem_1_1name__bid_1a5b559444f1ddf4eee7a32c53a3ef9485}






# struct `pair_time_point_sec_int64` {#structeosiosystem_1_1pair__time__point__sec__int64}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public time_point_sec first` | 
`public int64_t second` | 
`public  EOSLIB_SERIALIZE(`[`pair_time_point_sec_int64`](#structeosiosystem_1_1pair__time__point__sec__int64)`,(`[`first](#structeosiosystem_1_1pair__time__point__sec__int64_1acd031753aeb4381736b222cb5af110f1))([second`](#structeosiosystem_1_1pair__time__point__sec__int64_1ac501dfa169ad5f4a3d72554082f1ea26))`)` | 

## Members

### `public time_point_sec first` {#structeosiosystem_1_1pair__time__point__sec__int64_1acd031753aeb4381736b222cb5af110f1}





### `public int64_t second` {#structeosiosystem_1_1pair__time__point__sec__int64_1ac501dfa169ad5f4a3d72554082f1ea26}





### `public  EOSLIB_SERIALIZE(`[`pair_time_point_sec_int64`](#structeosiosystem_1_1pair__time__point__sec__int64)`,(`[`first](#structeosiosystem_1_1pair__time__point__sec__int64_1acd031753aeb4381736b222cb5af110f1))([second`](#structeosiosystem_1_1pair__time__point__sec__int64_1ac501dfa169ad5f4a3d72554082f1ea26))`)` {#structeosiosystem_1_1pair__time__point__sec__int64_1a61aef904c9c7214339d59263e49148b1}






# struct `permission_level_weight` {#structeosiosystem_1_1permission__level__weight}




A weighted permission.

Defines a weighted permission, that is a permission which has a weight associated. A permission is defined by an account name plus a permission name.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` permission` | 
`public uint16_t weight` | 

## Members

### `public `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` permission` {#structeosiosystem_1_1permission__level__weight_1ac98d5c5795870835a76e2c1d73bda998}





### `public uint16_t weight` {#structeosiosystem_1_1permission__level__weight_1a2df97f79b29e376a927df14444071684}






# struct `powerup_config` {#structeosiosystem_1_1powerup__config}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`powerup_config_resource`](#structeosiosystem_1_1powerup__config__resource)` net` | 
`public `[`powerup_config_resource`](#structeosiosystem_1_1powerup__config__resource)` cpu` | 
`public std::optional< uint32_t > powerup_days` | 
`public std::optional< asset > min_powerup_fee` | 

## Members

### `public `[`powerup_config_resource`](#structeosiosystem_1_1powerup__config__resource)` net` {#structeosiosystem_1_1powerup__config_1a1deffd1cf5b8de9c3ac49b5e4b08e65d}





### `public `[`powerup_config_resource`](#structeosiosystem_1_1powerup__config__resource)` cpu` {#structeosiosystem_1_1powerup__config_1a72a3d237b4877c573f429353dd3b8807}





### `public std::optional< uint32_t > powerup_days` {#structeosiosystem_1_1powerup__config_1a0bf5894e66ce146b1d46dab27ed79052}





### `public std::optional< asset > min_powerup_fee` {#structeosiosystem_1_1powerup__config_1a2d7ede4759845fcf1dd25498dfb48f10}






# struct `powerup_config_resource` {#structeosiosystem_1_1powerup__config__resource}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::optional< int64_t > current_weight_ratio` | 
`public std::optional< int64_t > target_weight_ratio` | 
`public std::optional< int64_t > assumed_stake_weight` | 
`public std::optional< time_point_sec > target_timestamp` | 
`public std::optional< double > exponent` | 
`public std::optional< uint32_t > decay_secs` | 
`public std::optional< asset > min_price` | 
`public std::optional< asset > max_price` | 

## Members

### `public std::optional< int64_t > current_weight_ratio` {#structeosiosystem_1_1powerup__config__resource_1a898798179695199cb53c5e71898956a9}





### `public std::optional< int64_t > target_weight_ratio` {#structeosiosystem_1_1powerup__config__resource_1a1a3d56ace89256c70b617043f60277f0}





### `public std::optional< int64_t > assumed_stake_weight` {#structeosiosystem_1_1powerup__config__resource_1a9e95f745ed5d212817932eca48bdf0bf}





### `public std::optional< time_point_sec > target_timestamp` {#structeosiosystem_1_1powerup__config__resource_1afc1c25dba26389ed543136d08b7da03f}





### `public std::optional< double > exponent` {#structeosiosystem_1_1powerup__config__resource_1a7c8254c0a368f5104090b068775cb6d2}





### `public std::optional< uint32_t > decay_secs` {#structeosiosystem_1_1powerup__config__resource_1aaf607638f0aa2bc03080307342367da4}





### `public std::optional< asset > min_price` {#structeosiosystem_1_1powerup__config__resource_1a999a90e06ab3ec5cd79b6d16985e8b5a}





### `public std::optional< asset > max_price` {#structeosiosystem_1_1powerup__config__resource_1a7eaa914ee1cff949e5721d526e0e8308}






# struct `powerup_order` {#structeosiosystem_1_1powerup__order}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public uint64_t id` | 
`public name owner` | 
`public int64_t net_weight` | 
`public int64_t cpu_weight` | 
`public time_point_sec expires` | 
`public inline uint64_t primary_key() const` | 
`public inline uint64_t by_owner() const` | 
`public inline uint64_t by_expires() const` | 

## Members

### `public uint8_t version` {#structeosiosystem_1_1powerup__order_1a5add3b2a59588f2a986ab8533b6ef07e}





### `public uint64_t id` {#structeosiosystem_1_1powerup__order_1a0c852ce9dc447d27818c6f76c9966f5b}





### `public name owner` {#structeosiosystem_1_1powerup__order_1a7367e434fe5c04cc3eea0a4e79d925f4}





### `public int64_t net_weight` {#structeosiosystem_1_1powerup__order_1a4ef585bec4e45a5643280a2be23c8abe}





### `public int64_t cpu_weight` {#structeosiosystem_1_1powerup__order_1afedd41b2e48a95941cf15b1a44dc401c}





### `public time_point_sec expires` {#structeosiosystem_1_1powerup__order_1a2d6b97d6744b9d46cb2fa6f64ecbcc9e}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1powerup__order_1a84d6154b02216683f5bac277a9c332ab}





### `public inline uint64_t by_owner() const` {#structeosiosystem_1_1powerup__order_1ad6f472ce4c90343ff6c3a2a312ac64ab}





### `public inline uint64_t by_expires() const` {#structeosiosystem_1_1powerup__order_1a9a404ef12847703055ba5da5b47af05a}






# struct `powerup_state` {#structeosiosystem_1_1powerup__state}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public `[`powerup_state_resource`](#structeosiosystem_1_1powerup__state__resource)` net` | 
`public `[`powerup_state_resource`](#structeosiosystem_1_1powerup__state__resource)` cpu` | 
`public uint32_t powerup_days` | 
`public asset min_powerup_fee` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public uint8_t version` {#structeosiosystem_1_1powerup__state_1adf46a1a98481f10048a71ad402193ddb}





### `public `[`powerup_state_resource`](#structeosiosystem_1_1powerup__state__resource)` net` {#structeosiosystem_1_1powerup__state_1a50378b359db22153b5767eebf3d5e91e}





### `public `[`powerup_state_resource`](#structeosiosystem_1_1powerup__state__resource)` cpu` {#structeosiosystem_1_1powerup__state_1ac00370168898d00ee8c2793728e45636}





### `public uint32_t powerup_days` {#structeosiosystem_1_1powerup__state_1a41192b702d0a81d46a3f19e87149c740}





### `public asset min_powerup_fee` {#structeosiosystem_1_1powerup__state_1a1e3527154e64dac849d3a04037ff131a}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1powerup__state_1a2ee6f547d067dd757cc345f51b0b385a}






# struct `powerup_state_resource` {#structeosiosystem_1_1powerup__state__resource}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public int64_t weight` | 
`public int64_t weight_ratio` | 
`public int64_t assumed_stake_weight` | 
`public int64_t initial_weight_ratio` | 
`public int64_t target_weight_ratio` | 
`public time_point_sec initial_timestamp` | 
`public time_point_sec target_timestamp` | 
`public double exponent` | 
`public uint32_t decay_secs` | 
`public asset min_price` | 
`public asset max_price` | 
`public int64_t utilization` | 
`public int64_t adjusted_utilization` | 
`public time_point_sec utilization_timestamp` | 

## Members

### `public uint8_t version` {#structeosiosystem_1_1powerup__state__resource_1ab33e538575a6bd6b1e73443701c9d6e6}





### `public int64_t weight` {#structeosiosystem_1_1powerup__state__resource_1ae11adb8af7452cc4b56b3c4efd27c4b5}





### `public int64_t weight_ratio` {#structeosiosystem_1_1powerup__state__resource_1aff92555e09aaa263ed2adaa3611ef7af}





### `public int64_t assumed_stake_weight` {#structeosiosystem_1_1powerup__state__resource_1a0b3fa07302f6fb0dcb44a2b581bf868e}





### `public int64_t initial_weight_ratio` {#structeosiosystem_1_1powerup__state__resource_1a61179807bb5fd8b89f504a58a8bd1a92}





### `public int64_t target_weight_ratio` {#structeosiosystem_1_1powerup__state__resource_1a11b0208fbcb1a05c5796020f924d29f6}





### `public time_point_sec initial_timestamp` {#structeosiosystem_1_1powerup__state__resource_1a153836a8d10a7c6b92f1d5ee936afc14}





### `public time_point_sec target_timestamp` {#structeosiosystem_1_1powerup__state__resource_1a6a95640c112f10d333c5605c0616250e}





### `public double exponent` {#structeosiosystem_1_1powerup__state__resource_1a0584f8973ecce81b54c6463575d8dadd}





### `public uint32_t decay_secs` {#structeosiosystem_1_1powerup__state__resource_1a4402b1bf923b042aded39e7296f0a658}





### `public asset min_price` {#structeosiosystem_1_1powerup__state__resource_1a5e30c55b2f38371c654d8a806fa26d3c}





### `public asset max_price` {#structeosiosystem_1_1powerup__state__resource_1a9792d8b112772e112a51193873e020f2}





### `public int64_t utilization` {#structeosiosystem_1_1powerup__state__resource_1a57a7d6c1f329f96a1964815e67bf5948}





### `public int64_t adjusted_utilization` {#structeosiosystem_1_1powerup__state__resource_1aebc618f4a8c543197c89496058ac444a}





### `public time_point_sec utilization_timestamp` {#structeosiosystem_1_1powerup__state__resource_1ad0454e9d4e79e5814f5acaf8324ea2e2}






# struct `producer_info` {#structeosiosystem_1_1producer__info}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name owner` | 
`public double total_votes` | 
`public eosio::public_key producer_key` | 
`public bool is_active` | a packed public key object
`public std::string url` | 
`public uint32_t unpaid_blocks` | 
`public time_point last_claim_time` | 
`public uint16_t location` | 
`public eosio::binary_extension< eosio::block_signing_authority > producer_authority` | 
`public inline uint64_t primary_key() const` | 
`public inline double by_votes() const` | 
`public inline bool active() const` | 
`public inline void deactivate()` | 
`public inline eosio::block_signing_authority get_producer_authority() const` | 

## Members

### `public name owner` {#structeosiosystem_1_1producer__info_1a8e7b745ce26e291c9bb6c01197b39481}





### `public double total_votes` {#structeosiosystem_1_1producer__info_1abc5e3b6f64341d7a4c47dcf7f7303466}





### `public eosio::public_key producer_key` {#structeosiosystem_1_1producer__info_1ae39a2bd7332a10fe183c86e8810ffc42}





### `public bool is_active` {#structeosiosystem_1_1producer__info_1a1e99c8edf840eef65937a55e81a96b50}

a packed public key object



### `public std::string url` {#structeosiosystem_1_1producer__info_1ae5fa32f4888e2db7faddb5e5b2b4da58}





### `public uint32_t unpaid_blocks` {#structeosiosystem_1_1producer__info_1a24e7945da7f329a88dd915d1582a877c}





### `public time_point last_claim_time` {#structeosiosystem_1_1producer__info_1a2c0ee0458d7b6b5629bab41d2f94a156}





### `public uint16_t location` {#structeosiosystem_1_1producer__info_1a5e543ec2f645048f754beca0fafc9daa}





### `public eosio::binary_extension< eosio::block_signing_authority > producer_authority` {#structeosiosystem_1_1producer__info_1acca552d34b42bf725872f6dd4883e8aa}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1producer__info_1a9a9423735c7e495e3e244a92719c5606}





### `public inline double by_votes() const` {#structeosiosystem_1_1producer__info_1a2923be76a2e0b28b39b772fc8f5f30aa}





### `public inline bool active() const` {#structeosiosystem_1_1producer__info_1ac747e9353d178231d7d71131b5c4e94e}





### `public inline void deactivate()` {#structeosiosystem_1_1producer__info_1ab83626158bab8b0d943315ace5255ada}





### `public inline eosio::block_signing_authority get_producer_authority() const` {#structeosiosystem_1_1producer__info_1a2134cf5d2aa6af5b55fa9a577654e4aa}






# struct `producer_info2` {#structeosiosystem_1_1producer__info2}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name owner` | 
`public double votepay_share` | 
`public time_point last_votepay_share_update` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public name owner` {#structeosiosystem_1_1producer__info2_1aa80744eebc2853521dd294e15124b2b3}





### `public double votepay_share` {#structeosiosystem_1_1producer__info2_1a62de9e8545175dc4aa45e5d9494c272b}





### `public time_point last_votepay_share_update` {#structeosiosystem_1_1producer__info2_1ae6771ab3b619d7cc3a354baf05336e96}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1producer__info2_1ae112142fed736880a03bd0ee305b34ef}






# struct `refund_request` {#structeosiosystem_1_1refund__request}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name owner` | 
`public time_point_sec request_time` | 
`public eosio::asset net_amount` | 
`public eosio::asset cpu_amount` | 
`public inline bool is_empty() const` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public name owner` {#structeosiosystem_1_1refund__request_1a11e5c7ef5cc00904a0d00bf0af8900ef}





### `public time_point_sec request_time` {#structeosiosystem_1_1refund__request_1ac5513485aad2e2e0de4717ca1b06530e}





### `public eosio::asset net_amount` {#structeosiosystem_1_1refund__request_1a5f314641a1ad02216a89275dd38c8b8b}





### `public eosio::asset cpu_amount` {#structeosiosystem_1_1refund__request_1a8d8e9e6b4bcdbdc1b30b045feb58c6fa}





### `public inline bool is_empty() const` {#structeosiosystem_1_1refund__request_1a2061e7187b06f1adb76043b7935bd091}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1refund__request_1a527ccee1812739017b22d69139b2e40b}






# struct `rex_balance` {#structeosiosystem_1_1rex__balance}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public name owner` | 
`public asset vote_stake` | 
`public asset rex_balance` | 
`public int64_t matured_rex` | 
`public std::vector< `[`pair_time_point_sec_int64`](#structeosiosystem_1_1pair__time__point__sec__int64)` > rex_maturities` | 
`public inline uint64_t primary_key() const` | REX daily maturity buckets.

## Members

### `public uint8_t version` {#structeosiosystem_1_1rex__balance_1a3db8caee6ce5eb1430db7d473a072098}





### `public name owner` {#structeosiosystem_1_1rex__balance_1aa7efa762e2abf679ec0c159fb1439372}





### `public asset vote_stake` {#structeosiosystem_1_1rex__balance_1a5b062ac98d3d4ad65bdda637f1687952}





### `public asset rex_balance` {#structeosiosystem_1_1rex__balance_1a530ed574f5fa7277422866734ba59aed}





### `public int64_t matured_rex` {#structeosiosystem_1_1rex__balance_1aae06fcc4eda99c14544e1e0394335834}





### `public std::vector< `[`pair_time_point_sec_int64`](#structeosiosystem_1_1pair__time__point__sec__int64)` > rex_maturities` {#structeosiosystem_1_1rex__balance_1ab69ca2daff48bdeb9a54de9f19895d38}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1rex__balance_1a8aebb3d7caed879be417d12c0ea75ff8}

REX daily maturity buckets.




# struct `rex_fund` {#structeosiosystem_1_1rex__fund}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public name owner` | 
`public asset balance` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public uint8_t version` {#structeosiosystem_1_1rex__fund_1a0d87faa3b4241bb715ef75854f885815}





### `public name owner` {#structeosiosystem_1_1rex__fund_1a9f04d7bcf465529f0870d54aabf5ae36}





### `public asset balance` {#structeosiosystem_1_1rex__fund_1af8fa096b0e2c5d24798a659aa5ddb309}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1rex__fund_1ada0d465ad79456e859e6dce84be99be5}






# struct `rex_loan` {#structeosiosystem_1_1rex__loan}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public name from` | 
`public name receiver` | 
`public asset payment` | 
`public asset balance` | 
`public asset total_staked` | 
`public uint64_t loan_num` | 
`public eosio::time_point expiration` | 
`public inline uint64_t primary_key() const` | 
`public inline uint64_t by_expr() const` | 
`public inline uint64_t by_owner() const` | 

## Members

### `public uint8_t version` {#structeosiosystem_1_1rex__loan_1a0b4256fabf5de5140d7454287b7ce635}





### `public name from` {#structeosiosystem_1_1rex__loan_1a59654a42de37d5f6ad11ef7b1ca8845f}





### `public name receiver` {#structeosiosystem_1_1rex__loan_1ad28a74d7cfcfcbe1c7502c49f34ab988}





### `public asset payment` {#structeosiosystem_1_1rex__loan_1aa0eb3d72cb30bc2b205cebab93a2c4f2}





### `public asset balance` {#structeosiosystem_1_1rex__loan_1aaa8b37af599e458df1cc4a4557558c34}





### `public asset total_staked` {#structeosiosystem_1_1rex__loan_1a030741dbdcc390ac07da48560f86a39b}





### `public uint64_t loan_num` {#structeosiosystem_1_1rex__loan_1a5727e851ef16e34096c5f3864a43d994}





### `public eosio::time_point expiration` {#structeosiosystem_1_1rex__loan_1ab9f18e11705c3798b616cf7caf476590}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1rex__loan_1a98d977e47a68a99e7af5283f5d7621d9}





### `public inline uint64_t by_expr() const` {#structeosiosystem_1_1rex__loan_1a7e1408b91e4d52c1381ce8f99b9eb521}





### `public inline uint64_t by_owner() const` {#structeosiosystem_1_1rex__loan_1a5dc4c8b0bf062ea5a729db6c859c033d}






# struct `rex_order` {#structeosiosystem_1_1rex__order}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public name owner` | 
`public asset rex_requested` | 
`public asset proceeds` | 
`public asset stake_change` | 
`public eosio::time_point order_time` | 
`public bool is_open` | 
`public inline void close()` | 
`public inline uint64_t primary_key() const` | 
`public inline uint64_t by_time() const` | 

## Members

### `public uint8_t version` {#structeosiosystem_1_1rex__order_1a3aa81dd239e34b29a863c01bc6af8d75}





### `public name owner` {#structeosiosystem_1_1rex__order_1ab655d38bd47b5e4ec102503954942035}





### `public asset rex_requested` {#structeosiosystem_1_1rex__order_1ab0d23a11ffd760162e02681f64e9639e}





### `public asset proceeds` {#structeosiosystem_1_1rex__order_1a87cdfd344b993ca26a3451124f128911}





### `public asset stake_change` {#structeosiosystem_1_1rex__order_1ad648133afca5497f7e4827b65d1cc529}





### `public eosio::time_point order_time` {#structeosiosystem_1_1rex__order_1aea99fc69a44d35acd09707dac2af61ee}





### `public bool is_open` {#structeosiosystem_1_1rex__order_1a4bc7bda7076a0a6b3b410ec83d2eb365}





### `public inline void close()` {#structeosiosystem_1_1rex__order_1a91ae93fddccc4a9bcc9cf156ff602bd6}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1rex__order_1a38851f3f71d5a2a95de515b044fcf90b}





### `public inline uint64_t by_time() const` {#structeosiosystem_1_1rex__order_1a177603993abdb4e9b521d273d9cbc818}






# struct `rex_order_outcome` {#structeosiosystem_1_1rex__order__outcome}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public bool success` | 
`public asset proceeds` | 
`public asset stake_change` | 

## Members

### `public bool success` {#structeosiosystem_1_1rex__order__outcome_1aa322c7f9f86c43de4134d427543f628f}





### `public asset proceeds` {#structeosiosystem_1_1rex__order__outcome_1a268d8b4466e29f8cb3dfaf58411a8602}





### `public asset stake_change` {#structeosiosystem_1_1rex__order__outcome_1a0cede7598459d110eb4f68ea71cb1e86}






# struct `rex_pool` {#structeosiosystem_1_1rex__pool}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public asset total_lent` | 
`public asset total_unlent` | 
`public asset total_rent` | 
`public asset total_lendable` | 
`public asset total_rex` | 
`public asset namebid_proceeds` | 
`public uint64_t loan_num` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public uint8_t version` {#structeosiosystem_1_1rex__pool_1addca00704e91405d1808533eefd8fd56}





### `public asset total_lent` {#structeosiosystem_1_1rex__pool_1a1819b3c6b83b60c9c31e1440dc074d58}





### `public asset total_unlent` {#structeosiosystem_1_1rex__pool_1aed217f873a6574c1db42493c9ad385d0}





### `public asset total_rent` {#structeosiosystem_1_1rex__pool_1ae2c5584ec5fe6f17b765e04b5c5c468a}





### `public asset total_lendable` {#structeosiosystem_1_1rex__pool_1a3a8999d7f7b8029e0d718f885b683737}





### `public asset total_rex` {#structeosiosystem_1_1rex__pool_1aaf99b9aead4d756af061f16febe73006}





### `public asset namebid_proceeds` {#structeosiosystem_1_1rex__pool_1a617f0698ad272dc19fae83cd576c1dc5}





### `public uint64_t loan_num` {#structeosiosystem_1_1rex__pool_1a95d45a7a85681d1930a62443d0fec47a}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1rex__pool_1a138432772e5150f86b56b22e5011048b}






# struct `rex_return_buckets` {#structeosiosystem_1_1rex__return__buckets}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public std::vector< `[`pair_time_point_sec_int64`](#structeosiosystem_1_1pair__time__point__sec__int64)` > return_buckets` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public uint8_t version` {#structeosiosystem_1_1rex__return__buckets_1a24996f1358821a23925f8fb6fedfbcac}





### `public std::vector< `[`pair_time_point_sec_int64`](#structeosiosystem_1_1pair__time__point__sec__int64)` > return_buckets` {#structeosiosystem_1_1rex__return__buckets_1a40398601193e8e6f2e343b417c5195c6}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1rex__return__buckets_1a91e47ae14cf12803658fc81858ba7d76}






# struct `rex_return_pool` {#structeosiosystem_1_1rex__return__pool}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public time_point_sec last_dist_time` | 
`public time_point_sec pending_bucket_time` | 
`public time_point_sec oldest_bucket_time` | 
`public int64_t pending_bucket_proceeds` | 
`public int64_t current_rate_of_increase` | 
`public int64_t proceeds` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public uint8_t version` {#structeosiosystem_1_1rex__return__pool_1a9b16ec989d93521cc26f51b97793c662}





### `public time_point_sec last_dist_time` {#structeosiosystem_1_1rex__return__pool_1a6bcacb0d59cb8951b83f089e2dee3bed}





### `public time_point_sec pending_bucket_time` {#structeosiosystem_1_1rex__return__pool_1a54bd0982d04bfea79eea5343cb2dce33}





### `public time_point_sec oldest_bucket_time` {#structeosiosystem_1_1rex__return__pool_1a50d9c4534af93ce26fffc8ae21c83981}





### `public int64_t pending_bucket_proceeds` {#structeosiosystem_1_1rex__return__pool_1a6586a70341c24f27a2b0ef2234fc5005}





### `public int64_t current_rate_of_increase` {#structeosiosystem_1_1rex__return__pool_1a9c40149b316eefb370e1733584ff1d6f}





### `public int64_t proceeds` {#structeosiosystem_1_1rex__return__pool_1a8c9014435e9325e35ee05115ac9e0ca3}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1rex__return__pool_1a1e8d9b3fd69ac163dcf6d77c3aedb80a}






# struct `user_resources` {#structeosiosystem_1_1user__resources}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name owner` | 
`public asset net_weight` | 
`public asset cpu_weight` | 
`public int64_t ram_bytes` | 
`public inline bool is_empty() const` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public name owner` {#structeosiosystem_1_1user__resources_1a8a373411ce7eb180649f9a7c938fb7dd}





### `public asset net_weight` {#structeosiosystem_1_1user__resources_1ad6532b1796871feb9d26c94e69266e7a}





### `public asset cpu_weight` {#structeosiosystem_1_1user__resources_1ace76500804d6a6bb4c0a2f0cc07f08b2}





### `public int64_t ram_bytes` {#structeosiosystem_1_1user__resources_1a89f602f8770024c9d9fd592854ac9e75}





### `public inline bool is_empty() const` {#structeosiosystem_1_1user__resources_1a62970931ec8e856b3ce21a78f5d51306}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1user__resources_1a8c06a7e1b3e4a3cc22af7fd677b09542}






# struct `voter_info` {#structeosiosystem_1_1voter__info}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name owner` | 
`public name proxy` | the voter
`public std::vector< name > producers` | the proxy set by the voter, if any
`public int64_t staked` | the producers approved by this voter if no proxy set
`public double last_vote_weight` | 
`public double proxied_vote_weight` | the vote weight cast the last time the vote was updated
`public bool is_proxy` | the total vote weight delegated to this voter as a proxy
`public uint32_t flags1` | whether the voter is a proxy for others
`public uint32_t reserved2` | 
`public eosio::asset reserved3` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public name owner` {#structeosiosystem_1_1voter__info_1a09e1d98da6939690519ea85baedf1c01}





### `public name proxy` {#structeosiosystem_1_1voter__info_1a482ed4e822024852ac234353ac5f08cc}

the voter



### `public std::vector< name > producers` {#structeosiosystem_1_1voter__info_1a90023077cb4f76e82c42482dc65a2783}

the proxy set by the voter, if any



### `public int64_t staked` {#structeosiosystem_1_1voter__info_1a3f1a76120b906f5f304c0c4604d4bf37}

the producers approved by this voter if no proxy set



### `public double last_vote_weight` {#structeosiosystem_1_1voter__info_1aa60bfb8489e47d8514efd230cd18288e}





### `public double proxied_vote_weight` {#structeosiosystem_1_1voter__info_1af7a7c2263d90ed79d2bf4281e57193c0}

the vote weight cast the last time the vote was updated



### `public bool is_proxy` {#structeosiosystem_1_1voter__info_1aee50442b79d5561a967486e6b7a61e65}

the total vote weight delegated to this voter as a proxy



### `public uint32_t flags1` {#structeosiosystem_1_1voter__info_1af77c6136a8d1300951ad6f39b3c28dc1}

whether the voter is a proxy for others



### `public uint32_t reserved2` {#structeosiosystem_1_1voter__info_1a5c4ecbb96e5e70acd2b9ce55c6a886d0}





### `public eosio::asset reserved3` {#structeosiosystem_1_1voter__info_1ac45fcd076d0257637f5c6b80618e4647}





### `public inline uint64_t primary_key() const` {#structeosiosystem_1_1voter__info_1a1fdb370974b4c33380e8114ff52a7d8f}






# struct `wait_weight` {#structeosiosystem_1_1wait__weight}




Wait weight.

A wait weight is defined by a number of seconds to wait for and a weight.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint32_t wait_sec` | 
`public uint16_t weight` | 

## Members

### `public uint32_t wait_sec` {#structeosiosystem_1_1wait__weight_1ad12a131189bb9c36470e221222338bb7}





### `public uint16_t weight` {#structeosiosystem_1_1wait__weight_1a9a1e16d11c7b5fd2ced0b1f15f418d8a}






# namespace `eosio`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[``chain``](#namespaceeosio_1_1chain)    | 
`namespace `[``testing``](#namespaceeosio_1_1testing)    | 
`class `[``token``](#classeosio_1_1token)    | 
`class `[``multisig``](#classeosio_1_1multisig)    | 
`class `[``soviet``](#classeosio_1_1soviet)    | 
`class `[``wrap``](#classeosio_1_1wrap)    | 
`struct `[``automator``](#structeosio_1_1automator)    | 
`struct `[``autosigner``](#structeosio_1_1autosigner)    | 
`struct `[``changes``](#structeosio_1_1changes)    | 
`struct `[``counts``](#structeosio_1_1counts)    | 
`struct `[``joincoops``](#structeosio_1_1joincoops)    | 

# namespace `chain`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

# namespace `testing`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

# class `token` {#classeosio_1_1token}

```
class token
  : public eosio::contract
```  



The `[eosio.token](#classeosio_1_1token)` sample system contract defines the structures and actions that allow users to create, issue, and manage tokens for EOSIO based blockchains. It demonstrates one way to implement a smart contract which allows for creation and management of tokens. It is possible for one to create a similar contract which suits different needs. However, it is recommended that if one only needs a token with the below listed actions, that one uses the `[eosio.token](#classeosio_1_1token)` contract instead of developing their own.

The `[eosio.token](#classeosio_1_1token)` contract class also implements two useful public static methods: `get_supply` and `get_balance`. The first allows one to check the total supply of a specified token, created by an account and the second allows one to check the balance of a token for a specified account (the token creator account has to be specified as well).

The `[eosio.token](#classeosio_1_1token)` contract manages the set of tokens, accounts and their corresponding balances, by using two internal multi-index structures: the `accounts` and `stats`. The `accounts` multi-index table holds, for each row, instances of `account` object and the `account` object holds information about the balance of one token. The `accounts` table is scoped to an EOSIO account, and it keeps the rows indexed based on the token's symbol. This means that when one queries the `accounts` multi-index table for an account name the result is all the tokens that account holds at the moment.

Similarly, the `stats` multi-index table, holds instances of `[currency_stats](#structeosio_1_1token_1_1currency__stats)` objects for each row, which contains information about current supply, maximum supply, and the creator account for a symbol token. The `stats` table is scoped to the token symbol. Therefore, when one queries the `stats` table for a token symbol the result is one single entry/row corresponding to the queried symbol token if it was previously created, or nothing, otherwise.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[``account``](#structeosio_1_1token_1_1account)        | 
`struct `[``currency_stats``](#structeosio_1_1token_1_1currency__stats)        | 
`public void create(const name & issuer,const asset & maximum_supply)` | 
`public void issue(const name & to,const asset & quantity,const string & memo)` | 
`public void retire(const asset & quantity,const string & memo)` | 
`public void transfer(const name & from,const name & to,const asset & quantity,const string & memo)` | 
`public void open(const name & owner,const symbol & symbol,const name & ram_payer)` | 
`public void close(const name & owner,const symbol & symbol)` | 

## Members

### `struct `[``account``](#structeosio_1_1token_1_1account) {#structeosio_1_1token_1_1account}




### `struct `[``currency_stats``](#structeosio_1_1token_1_1currency__stats) {#structeosio_1_1token_1_1currency__stats}




### `public void create(const name & issuer,const asset & maximum_supply)` {#classeosio_1_1token_1a5277670549e2458dd4a4fab4c56a9599}



Allows `issuer` account to create a token in supply of `maximum_supply`. If validation is successful a new entry in statstable for token symbol scope gets created.


#### Parameters
* `issuer` - the account that creates the token, 


* `maximum_supply` - the maximum supply set for the token created.




Token symbol has to be valid, 

Token symbol must not be already created, 

maximum_supply has to be smaller than the maximum supply allowed by the system: 1^62 - 1. 

Maximum supply must be positive;

### `public void issue(const name & to,const asset & quantity,const string & memo)` {#classeosio_1_1token_1a3a62d2a7493710b3e34fbdfd4fe81d59}



This action issues to `to` account a `quantity` of tokens.


#### Parameters
* `to` - the account to issue tokens to, it must be the same as the issuer, 


* `quantity` - the amount of tokens to be issued, @memo - the memo string that accompanies the token issue transaction.

### `public void retire(const asset & quantity,const string & memo)` {#classeosio_1_1token_1a4bf7770086ab81931c6c5a22265bae4f}



The opposite for create action, if all validations succeed, it debits the statstable.supply amount.


#### Parameters
* `quantity` - the quantity of tokens to retire, 


* `memo` - the memo string to accompany the transaction.

### `public void transfer(const name & from,const name & to,const asset & quantity,const string & memo)` {#classeosio_1_1token_1a8a9d08a9791d818797dc5f70ed8f826f}



Allows `from` account to transfer to `to` account the `quantity` tokens. One account is debited and the other is credited with quantity tokens.


#### Parameters
* `from` - the account to transfer from, 


* `to` - the account to be transferred to, 


* `quantity` - the quantity of tokens to be transferred, 


* `memo` - the memo string to accompany the transaction.

### `public void open(const name & owner,const symbol & symbol,const name & ram_payer)` {#classeosio_1_1token_1a4da303699332aacdc69f3ff582477141}



Allows `ram_payer` to create an account `owner` with zero balance for token `symbol` at the expense of `ram_payer`.


#### Parameters
* `owner` - the account to be created, 


* `symbol` - the token to be payed with by `ram_payer`, 


* `ram_payer` - the account that supports the cost of this action.





More information can be read [here](https://github.com/EOSIO/eosio.contracts/issues/62) and [here](https://github.com/EOSIO/eosio.contracts/issues/61).

### `public void close(const name & owner,const symbol & symbol)` {#classeosio_1_1token_1a88402f75888c4cfe6a3ef0391bd7ecbd}



This action is the opposite for open, it closes the account `owner` for token `symbol`.


#### Parameters
* `owner` - the owner account to execute the close action for, 


* `symbol` - the symbol of the token to execute the close action for.




The pair of owner plus symbol has to exist otherwise no action is executed, 

If the pair of owner plus symbol exists, the balance has to be zero.


# struct `account` {#structeosio_1_1token_1_1account}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public asset balance` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public asset balance` {#structeosio_1_1token_1_1account_1a6d6aaf37aa4e794b64a1b04990339043}





### `public inline uint64_t primary_key() const` {#structeosio_1_1token_1_1account_1a0881195a3cc88813bfc082903e2e627a}






# struct `currency_stats` {#structeosio_1_1token_1_1currency__stats}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public asset supply` | 
`public asset max_supply` | 
`public name issuer` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public asset supply` {#structeosio_1_1token_1_1currency__stats_1ab24e3519d9ea9063b80d74a64ec1fd73}





### `public asset max_supply` {#structeosio_1_1token_1_1currency__stats_1ab83559b6e1cdd215cf7b60153009a966}





### `public name issuer` {#structeosio_1_1token_1_1currency__stats_1a98c87418ed2e156ca2bd94a8e51a0b9f}





### `public inline uint64_t primary_key() const` {#structeosio_1_1token_1_1currency__stats_1ac651a49171c9e1b62d07e529657895ec}






# class `multisig` {#classeosio_1_1multisig}

```
class multisig
  : public contract
```  



The `eosio.msig` system contract allows for creation of proposed transactions which require authorization from a list of accounts, approval of the proposed transactions by those accounts required to approve it, and finally, it also allows the execution of the approved transactions on the blockchain.

In short, the workflow to propose, review, approve and then executed a transaction it can be described by the following:

* first you create a transaction json file,


* then you submit this proposal to the `eosio.msig` contract, and you also insert the account permissions required to approve this proposal into the command that submits the proposal to the blockchain,


* the proposal then gets stored on the blockchain by the `eosio.msig` contract, and is accessible for review and approval to those accounts required to approve it,


* after each of the appointed accounts required to approve the proposed transactions reviews and approves it, you can execute the proposed transaction. The `eosio.msig` contract will execute it automatically, but not before validating that the transaction has not expired, it is not cancelled, and it has been signed by all the permissions in the initial proposal's required permission list.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[``approval``](#structeosio_1_1multisig_1_1approval)        | 
`struct `[``approvals_info``](#structeosio_1_1multisig_1_1approvals__info)        | 
`struct `[``invalidation``](#structeosio_1_1multisig_1_1invalidation)        | 
`struct `[``old_approvals_info``](#structeosio_1_1multisig_1_1old__approvals__info)        | 
`struct `[``proposal``](#structeosio_1_1multisig_1_1proposal)        | 
`public void propose(name proposer,name proposal_name,std::vector< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > requested,ignore< transaction > trx)` | 
`public void approve(name proposer,name proposal_name,`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` level,const eosio::binary_extension< eosio::checksum256 > & proposal_hash)` | 
`public void unapprove(name proposer,name proposal_name,`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` level)` | 
`public void cancel(name proposer,name proposal_name,name canceler)` | 
`public void exec(name proposer,name proposal_name,name executer)` | 
`public void invalidate(name account)` | 

## Members

### `struct `[``approval``](#structeosio_1_1multisig_1_1approval) {#structeosio_1_1multisig_1_1approval}




### `struct `[``approvals_info``](#structeosio_1_1multisig_1_1approvals__info) {#structeosio_1_1multisig_1_1approvals__info}




### `struct `[``invalidation``](#structeosio_1_1multisig_1_1invalidation) {#structeosio_1_1multisig_1_1invalidation}




### `struct `[``old_approvals_info``](#structeosio_1_1multisig_1_1old__approvals__info) {#structeosio_1_1multisig_1_1old__approvals__info}




### `struct `[``proposal``](#structeosio_1_1multisig_1_1proposal) {#structeosio_1_1multisig_1_1proposal}




### `public void propose(name proposer,name proposal_name,std::vector< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > requested,ignore< transaction > trx)` {#classeosio_1_1multisig_1acb9cee084979625820b6f45492f13be0}



Propose action, creates a proposal containing one transaction. Allows an account `proposer` to make a proposal `proposal_name` which has `requested` permission levels expected to approve the proposal, and if approved by all expected permission levels then `trx` transaction can we executed by this proposal. The `proposer` account is authorized and the `trx` transaction is verified if it was authorized by the provided keys and permissions, and if the proposal name doesn’t already exist; if all validations pass the `proposal_name` and `trx` trasanction are saved in the proposals table and the `requested` permission levels to the approvals table (for the `proposer` context). Storage changes are billed to `proposer`.


#### Parameters
* `proposer` - The account proposing a transaction 


* `proposal_name` - The name of the proposal (should be unique for proposer) 


* `requested` - Permission levels expected to approve the proposal 


* `trx` - Proposed transaction

### `public void approve(name proposer,name proposal_name,`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` level,const eosio::binary_extension< eosio::checksum256 > & proposal_hash)` {#classeosio_1_1multisig_1a5cccb8b23b9fffa1b27d443fad9ce3e9}



Approve action approves an existing proposal. Allows an account, the owner of `level` permission, to approve a proposal `proposal_name` proposed by `proposer`. If the proposal's requested approval list contains the `level` permission then the `level` permission is moved from internal `requested_approvals` list to internal `provided_approvals` list of the proposal, thus persisting the approval for the `proposal_name` proposal. Storage changes are billed to `proposer`.


#### Parameters
* `proposer` - The account proposing a transaction 


* `proposal_name` - The name of the proposal (should be unique for proposer) 


* `level` - Permission level approving the transaction 


* `proposal_hash` - Transaction's checksum

### `public void unapprove(name proposer,name proposal_name,`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` level)` {#classeosio_1_1multisig_1a7d6e568f96c6697728e316557a9bcf1e}



Unapprove action revokes an existing proposal. This action is the reverse of the `approve` action: if all validations pass the `level` permission is erased from internal `provided_approvals` and added to the internal `requested_approvals` list, and thus un-approve or revoke the proposal.


#### Parameters
* `proposer` - The account proposing a transaction 


* `proposal_name` - The name of the proposal (should be an existing proposal) 


* `level` - Permission level revoking approval for proposal

### `public void cancel(name proposer,name proposal_name,name canceler)` {#classeosio_1_1multisig_1a2dc849ab961ea31c0e93ebace0f0dd00}



Cancel action cancels an existing proposal.


#### Parameters
* `proposer` - The account proposing a transaction 


* `proposal_name` - The name of the proposal (should be an existing proposal) 


* `canceler` - The account cancelling the proposal (only the proposer can cancel an unexpired transaction, and the canceler has to be different than the proposer)





Allows the `canceler` account to cancel the `proposal_name` proposal, created by a `proposer`, only after time has expired on the proposed transaction. It removes corresponding entries from internal proptable and from approval (or old approvals) tables as well.

### `public void exec(name proposer,name proposal_name,name executer)` {#classeosio_1_1multisig_1ac31b3d91892bf8fcdad8d6f123c278ff}



Exec action allows an `executer` account to execute a proposal.

Preconditions:

* `executer` has authorization,


* `proposal_name` is found in the proposals table,


* all requested approvals are received,


* proposed transaction is not expired,


* and approval accounts are not found in invalidations table.





If all preconditions are met the transaction is executed as a deferred transaction, and the proposal is erased from the proposals table.


#### Parameters
* `proposer` - The account proposing a transaction 


* `proposal_name` - The name of the proposal (should be an existing proposal) 


* `executer` - The account executing the transaction

### `public void invalidate(name account)` {#classeosio_1_1multisig_1a59e26671d5a02dd2f809b08f56b4d3b8}



Invalidate action allows an `account` to invalidate itself, that is, its name is added to the invalidations table and this table will be cross referenced when exec is performed.


#### Parameters
* `account` - The account invalidating the transaction


# struct `approval` {#structeosio_1_1multisig_1_1approval}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` level` | 
`public time_point time` | 

## Members

### `public `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` level` {#structeosio_1_1multisig_1_1approval_1a7de164e0abd4d7ecec9da2f67fe57ece}





### `public time_point time` {#structeosio_1_1multisig_1_1approval_1a07e19daf20f6ca5a96251a0c590cbe31}






# struct `approvals_info` {#structeosio_1_1multisig_1_1approvals__info}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public name proposal_name` | 
`public std::vector< `[`approval`](#structeosio_1_1multisig_1_1approval)` > requested_approvals` | 
`public std::vector< `[`approval`](#structeosio_1_1multisig_1_1approval)` > provided_approvals` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public uint8_t version` {#structeosio_1_1multisig_1_1approvals__info_1a7067d083de3933cab8fa1b961e1d810d}





### `public name proposal_name` {#structeosio_1_1multisig_1_1approvals__info_1a76bf340c4c8c42d573664bd0fab91675}





### `public std::vector< `[`approval`](#structeosio_1_1multisig_1_1approval)` > requested_approvals` {#structeosio_1_1multisig_1_1approvals__info_1ad173253fe8f9e34c17117db4baeb41ae}





### `public std::vector< `[`approval`](#structeosio_1_1multisig_1_1approval)` > provided_approvals` {#structeosio_1_1multisig_1_1approvals__info_1a6d57f9792fe5bc8b2cacbf071e1059f8}





### `public inline uint64_t primary_key() const` {#structeosio_1_1multisig_1_1approvals__info_1ac7ec9b713d3a499006ea9ba9030e10b4}






# struct `invalidation` {#structeosio_1_1multisig_1_1invalidation}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name account` | 
`public time_point last_invalidation_time` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public name account` {#structeosio_1_1multisig_1_1invalidation_1af732aa933c30257e90b28db376af4461}





### `public time_point last_invalidation_time` {#structeosio_1_1multisig_1_1invalidation_1a767f677a40d58d61189e2bfd2bbdff1f}





### `public inline uint64_t primary_key() const` {#structeosio_1_1multisig_1_1invalidation_1a8222535d8511a2cd9667a7c816a169b8}






# struct `old_approvals_info` {#structeosio_1_1multisig_1_1old__approvals__info}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name proposal_name` | 
`public std::vector< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > requested_approvals` | 
`public std::vector< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > provided_approvals` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public name proposal_name` {#structeosio_1_1multisig_1_1old__approvals__info_1ababd8996161ac79d6889b81a2f1755af}





### `public std::vector< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > requested_approvals` {#structeosio_1_1multisig_1_1old__approvals__info_1ae499fbd3582721ecd3caa4d0ff71737f}





### `public std::vector< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > provided_approvals` {#structeosio_1_1multisig_1_1old__approvals__info_1a1f9c8bcc263e6a6d324c81e1cbbd49f1}





### `public inline uint64_t primary_key() const` {#structeosio_1_1multisig_1_1old__approvals__info_1a3a8558018b8d987b48ae8d0d0935611e}






# struct `proposal` {#structeosio_1_1multisig_1_1proposal}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name proposal_name` | 
`public std::vector< char > packed_transaction` | 
`public eosio::binary_extension< std::optional< time_point > > earliest_exec_time` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public name proposal_name` {#structeosio_1_1multisig_1_1proposal_1a231b1043a7721d508c07ca6c6b20385b}





### `public std::vector< char > packed_transaction` {#structeosio_1_1multisig_1_1proposal_1af9a7406b371dbf10a78ce56f9f921f84}





### `public eosio::binary_extension< std::optional< time_point > > earliest_exec_time` {#structeosio_1_1multisig_1_1proposal_1ac8b4f63052c9089874b1a0be48bcef07}





### `public inline uint64_t primary_key() const` {#structeosio_1_1multisig_1_1proposal_1ae459219bcd83cd451771b633277519db}






# class `soviet` {#classeosio_1_1soviet}

```
class soviet
  : public eosio::contract
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void exec(eosio::name executer,eosio::name coop_username,uint64_t decision_id)` | 
`public void newid(uint64_t decision_id)` | 
`public void addstaff(eosio::name coop_username,uint64_t board_id,eosio::name chairman,eosio::name username,std::vector< `[`right`](#structright)` > rights,std::string meta)` | 
`public void rmstaff(eosio::name coop_username,uint64_t board_id,eosio::name chairman,eosio::name username)` | 
`public void setrights(eosio::name coop_username,uint64_t board_id,eosio::name chairman,eosio::name username,std::vector< `[`right`](#structright)` > rights)` | 
`public void validate(eosio::name coop_username,uint64_t board_id,eosio::name username,uint64_t decision_id)` | 
`public void joincoop(eosio::name coop_username,eosio::name username,std::string position_title,eosio::name position)` | 
`public void automate(eosio::name coop_username,uint64_t board_id,eosio::name member,eosio::name action_type,eosio::name provider,std::string encrypted_private_key)` | 
`public void disautomate(eosio::name coop_username,uint64_t board_id,eosio::name member,uint64_t automation_id)` | 
`public void authorize(eosio::name coop_username,eosio::name chairman,uint64_t decision_id)` | 
`public void createboard(eosio::name coop_username,eosio::name chairman,eosio::name type,std::vector< `[`board_member`](#structboard__member)` > members,std::string name,std::string description)` | 
`public void votefor(eosio::name coop_username,eosio::name member,uint64_t decision_id)` | 
`public void voteagainst(eosio::name coop_username,eosio::name member,uint64_t decision_id)` | 
`public void cancelvote(eosio::name coop_username,eosio::name member,uint64_t decision_id)` | 
`public void change(eosio::name coop_username,uint64_t exchange_id)` | 

## Members

### `public void exec(eosio::name executer,eosio::name coop_username,uint64_t decision_id)` {#classeosio_1_1soviet_1a56d446612345f60629154447e0b8e108}





### `public void newid(uint64_t decision_id)` {#classeosio_1_1soviet_1ab866b3027630a8c43f307387bcaad687}





### `public void addstaff(eosio::name coop_username,uint64_t board_id,eosio::name chairman,eosio::name username,std::vector< `[`right`](#structright)` > rights,std::string meta)` {#classeosio_1_1soviet_1a00c952b8cc000504ae105c82014217e8}





### `public void rmstaff(eosio::name coop_username,uint64_t board_id,eosio::name chairman,eosio::name username)` {#classeosio_1_1soviet_1aff2ccc480f8674e7b2f1592ccff4f17b}





### `public void setrights(eosio::name coop_username,uint64_t board_id,eosio::name chairman,eosio::name username,std::vector< `[`right`](#structright)` > rights)` {#classeosio_1_1soviet_1ab568d02a607f4a7c8310a4387ef2a37e}





### `public void validate(eosio::name coop_username,uint64_t board_id,eosio::name username,uint64_t decision_id)` {#classeosio_1_1soviet_1a3c28fb6fe494d72ba1a0de8d8eb7e930}





### `public void joincoop(eosio::name coop_username,eosio::name username,std::string position_title,eosio::name position)` {#classeosio_1_1soviet_1ab5f3356c48b5d4ed1c048125137568e5}





### `public void automate(eosio::name coop_username,uint64_t board_id,eosio::name member,eosio::name action_type,eosio::name provider,std::string encrypted_private_key)` {#classeosio_1_1soviet_1a3b326646392cc5dbccf6f76b5710d7bd}





### `public void disautomate(eosio::name coop_username,uint64_t board_id,eosio::name member,uint64_t automation_id)` {#classeosio_1_1soviet_1ae253ba528c69482ca3370ce5fcc02f61}





### `public void authorize(eosio::name coop_username,eosio::name chairman,uint64_t decision_id)` {#classeosio_1_1soviet_1a6ff3916db9519e3558e3576e47055dc0}





### `public void createboard(eosio::name coop_username,eosio::name chairman,eosio::name type,std::vector< `[`board_member`](#structboard__member)` > members,std::string name,std::string description)` {#classeosio_1_1soviet_1ad1fc0777d9b64aeaeb1cde7f413222cb}





### `public void votefor(eosio::name coop_username,eosio::name member,uint64_t decision_id)` {#classeosio_1_1soviet_1a497f15fa085d12b2638cbc96ce85ddd9}





### `public void voteagainst(eosio::name coop_username,eosio::name member,uint64_t decision_id)` {#classeosio_1_1soviet_1ac3d33694508208c379e18cb958a312c1}





### `public void cancelvote(eosio::name coop_username,eosio::name member,uint64_t decision_id)` {#classeosio_1_1soviet_1ac53e1df4741d4e54d05fefbcdd8612b7}





### `public void change(eosio::name coop_username,uint64_t exchange_id)` {#classeosio_1_1soviet_1a51caad33b4bf87669059fe0314d674be}






# class `wrap` {#classeosio_1_1wrap}

```
class wrap
  : public eosio::contract
```  



The `[eosio.wrap](#classeosio_1_1wrap)` system contract allows block producers to bypass authorization checks or run privileged actions with 15/21 producer approval and thus simplifies block producers superuser actions. It also makes these actions easier to audit.

It does not give block producers any additional powers or privileges that do not already exist within the EOSIO based blockchains. As it is implemented, in an EOSIO based blockchain, 15/21 block producers can change an account's permissions or modify an account's contract code if they decided it is beneficial for the blockchain and community. However, the current method is opaque and leaves undesirable side effects on specific system accounts, and thus the `[eosio.wrap](#classeosio_1_1wrap)`contract solves this matter by providing an easier method of executing important governance actions.

The only action implemented by the `[eosio.wrap](#classeosio_1_1wrap)` system contract is the `exec` action. This action allows for execution of a transaction, which is passed to the `exec` method in the form of a packed transaction in json format via the 'trx' parameter and the `executer` account that executes the transaction. The same `executer` account will also be used to pay the RAM and CPU fees needed to execute the transaction.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void exec(ignore< name > executer,ignore< transaction > trx)` | 

## Members

### `public void exec(ignore< name > executer,ignore< transaction > trx)` {#classeosio_1_1wrap_1a62a9871067de866d265fd69a5a4eac60}



Execute action.

Execute a transaction while bypassing regular authorization checks.

Preconditions:

* Requires authorization of [eosio.wrap](#classeosio_1_1wrap) which needs to be a privileged account.





Postconditions:

* Deferred transaction RAM usage is billed to 'executer' *






#### Parameters
* `executer` - account executing the transaction, 


* `trx` - the transaction to be executed.


# struct `automator` {#structeosio_1_1automator}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint64_t id` | 
`public eosio::name coop_username` | 
`public uint64_t board_id` | 
`public eosio::name member` | 
`public eosio::name action_type` | 
`public eosio::name permission_name` | 
`public std::string encrypted_private_key` | 
`public inline uint64_t primary_key() const` | 
`public inline uint128_t by_member_and_action_type() const` | 
`public inline uint64_t by_action() const` | 

## Members

### `public uint64_t id` {#structeosio_1_1automator_1a71904acdde50a9e49b8cd4e65074cfc1}





### `public eosio::name coop_username` {#structeosio_1_1automator_1ab35f7c3b638441dac34949ec340499a2}





### `public uint64_t board_id` {#structeosio_1_1automator_1a3e9167336a434487762cffd8af1db0da}





### `public eosio::name member` {#structeosio_1_1automator_1a00ee4d8eb850b5a594e7fe5bc2f37252}





### `public eosio::name action_type` {#structeosio_1_1automator_1abe089e463b8844e42be72e2c95f7212a}





### `public eosio::name permission_name` {#structeosio_1_1automator_1aae93d7e6be417bf12838a1b3a0871bfe}





### `public std::string encrypted_private_key` {#structeosio_1_1automator_1ade7fc5cbbffb9701d6d29dad8b70576e}





### `public inline uint64_t primary_key() const` {#structeosio_1_1automator_1afc7c424a0d473897ef4e9e76f17e8d0c}





### `public inline uint128_t by_member_and_action_type() const` {#structeosio_1_1automator_1a726d6fcdfc8f0e84c96f7abda1020a69}





### `public inline uint64_t by_action() const` {#structeosio_1_1automator_1a59d3a964fe9d7205a93f453f5ce70eb7}






# struct `autosigner` {#structeosio_1_1autosigner}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint64_t decision_id` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public uint64_t decision_id` {#structeosio_1_1autosigner_1ae723c9212461794be834a55e0169a6c9}





### `public inline uint64_t primary_key() const` {#structeosio_1_1autosigner_1af66f2d083d71f9b93c9bebbb827612b7}






# struct `changes` {#structeosio_1_1changes}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint64_t exchange_id` | 
`public bool is_paid` | 
`public bool is_recieved` | 
`public bool is_withdrawed` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public uint64_t exchange_id` {#structeosio_1_1changes_1a1da338e5afbafe3f9e58b71a521653d4}





### `public bool is_paid` {#structeosio_1_1changes_1a4884a28fe0214a60358b488618b942b5}





### `public bool is_recieved` {#structeosio_1_1changes_1add264769c554aed739ee82a27d555118}





### `public bool is_withdrawed` {#structeosio_1_1changes_1a1cf86a750b9919c95c922bee629928ac}





### `public inline uint64_t primary_key() const` {#structeosio_1_1changes_1a14ed5cf6a920654a31391657b46ae6a6}






# struct `counts` {#structeosio_1_1counts}

```
struct counts
  : public counts_base
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members


# struct `joincoops` {#structeosio_1_1joincoops}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint64_t id` | 
`public eosio::name username` | 
`public bool is_paid` | 
`public std::string notice` | 
`public inline uint64_t primary_key() const` | 

## Members

### `public uint64_t id` {#structeosio_1_1joincoops_1a2400b81922f344fbfa41dda06c2caa4d}





### `public eosio::name username` {#structeosio_1_1joincoops_1ad0a709dbb47d3d94d1b4bafe335bd05c}





### `public bool is_paid` {#structeosio_1_1joincoops_1ab3b0842b664a04a69858d83714845dca}





### `public std::string notice` {#structeosio_1_1joincoops_1a198fbc9e86daba2b45e29ff0f5fd7704}





### `public inline uint64_t primary_key() const` {#structeosio_1_1joincoops_1ad9376fa463217ba4416efb37b9ac3919}






# namespace `anonymous_namespace{eosio.system_blockinfo_tests.cpp}`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[``block_info_record``](#structanonymous__namespace_02eosio_8system__blockinfo__tests_8cpp_03_1_1block__info__record)    | 

# struct `block_info_record` {#structanonymous__namespace_02eosio_8system__blockinfo__tests_8cpp_03_1_1block__info__record}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint8_t version` | 
`public uint32_t block_height` | 
`public fc::time_point block_timestamp` | 

## Members

### `public uint8_t version` {#structanonymous__namespace_02eosio_8system__blockinfo__tests_8cpp_03_1_1block__info__record_1a9b175e30fcaf561319e39ee48d014602}





### `public uint32_t block_height` {#structanonymous__namespace_02eosio_8system__blockinfo__tests_8cpp_03_1_1block__info__record_1ab1c2e57742392fbba0afae1d1331dcc5}





### `public fc::time_point block_timestamp` {#structanonymous__namespace_02eosio_8system__blockinfo__tests_8cpp_03_1_1block__info__record_1aac121c92ab118a1eeae949d180eda364}






# namespace `eosio_system`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``eosio_system_tester``](#classeosio__system_1_1eosio__system__tester)    | 

# class `eosio_system_tester` {#classeosio__system_1_1eosio__system__tester}

```
class eosio_system_tester
  : public TESTER
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public abi_serializer abi_ser` | 
`public abi_serializer token_abi_ser` | 
`public inline void basic_setup()` | 
`public inline void create_core_token(symbol core_symbol)` | 
`public inline void deploy_contract(bool call_init)` | 
`public inline void remaining_setup()` | 
`public inline  eosio_system_tester(`[`setup_level`](#classeosio__system_1_1eosio__system__tester_1ae7e0ff4e2ebe321e9508b432c8d1ca35)` l)` | 
`public template<typename Lambda>`  <br/>`inline  eosio_system_tester(Lambda setup)` | 
`public inline void create_accounts_with_resources(vector< account_name > accounts,account_name creator)` | 
`public inline transaction_trace_ptr create_account_with_resources(account_name a,account_name creator,uint32_t ram_bytes)` | 
`public inline transaction_trace_ptr create_account_with_resources(account_name a,account_name creator,asset ramfunds,bool multisig,asset net,asset cpu)` | 
`public inline transaction_trace_ptr setup_producer_accounts(const std::vector< account_name > & accounts,asset ram,asset cpu,asset net)` | 
`public inline action_result buyram(const account_name & payer,account_name receiver,const asset & eosin)` | 
`public inline action_result buyram(std::string_view payer,std::string_view receiver,const asset & eosin)` | 
`public inline action_result buyrambytes(const account_name & payer,account_name receiver,uint32_t numbytes)` | 
`public inline action_result buyrambytes(std::string_view payer,std::string_view receiver,uint32_t numbytes)` | 
`public inline action_result sellram(const account_name & account,uint64_t numbytes)` | 
`public inline action_result sellram(std::string_view account,uint64_t numbytes)` | 
`public inline action_result push_action(const account_name & signer,const action_name & name,const variant_object & data,bool auth)` | 
`public inline action_result stake(const account_name & from,const account_name & to,const asset & net,const asset & cpu)` | 
`public inline action_result stake(std::string_view from,std::string_view to,const asset & net,const asset & cpu)` | 
`public inline action_result stake(const account_name & acnt,const asset & net,const asset & cpu)` | 
`public inline action_result stake(std::string_view acnt,const asset & net,const asset & cpu)` | 
`public inline action_result stake_with_transfer(const account_name & from,const account_name & to,const asset & net,const asset & cpu)` | 
`public inline action_result stake_with_transfer(std::string_view from,std::string_view to,const asset & net,const asset & cpu)` | 
`public inline action_result stake_with_transfer(const account_name & acnt,const asset & net,const asset & cpu)` | 
`public inline action_result stake_with_transfer(std::string_view acnt,const asset & net,const asset & cpu)` | 
`public inline action_result unstake(const account_name & from,const account_name & to,const asset & net,const asset & cpu)` | 
`public inline action_result unstake(std::string_view from,std::string_view to,const asset & net,const asset & cpu)` | 
`public inline action_result unstake(const account_name & acnt,const asset & net,const asset & cpu)` | 
`public inline action_result unstake(std::string_view acnt,const asset & net,const asset & cpu)` | 
`public inline int64_t bancor_convert(int64_t S,int64_t R,int64_t T)` | 
`public inline int64_t get_net_limit(account_name a)` | 
`public inline int64_t get_cpu_limit(account_name a)` | 
`public inline action_result deposit(const account_name & owner,const asset & amount)` | 
`public inline action_result withdraw(const account_name & owner,const asset & amount)` | 
`public inline action_result buyrex(const account_name & from,const asset & amount)` | 
`public inline asset get_buyrex_result(const account_name & from,const asset & amount)` | 
`public inline action_result unstaketorex(const account_name & owner,const account_name & receiver,const asset & from_net,const asset & from_cpu)` | 
`public inline asset get_unstaketorex_result(const account_name & owner,const account_name & receiver,const asset & from_net,const asset & from_cpu)` | 
`public inline action_result sellrex(const account_name & from,const asset & rex)` | 
`public inline asset get_sellrex_result(const account_name & from,const asset & rex)` | 
`public inline auto get_rexorder_result(const transaction_trace_ptr & trace)` | 
`public inline action_result cancelrexorder(const account_name & owner)` | 
`public inline action_result rentcpu(const account_name & from,const account_name & receiver,const asset & payment,const asset & fund)` | 
`public inline action_result rentnet(const account_name & from,const account_name & receiver,const asset & payment,const asset & fund)` | 
`public inline asset _get_rentrex_result(const account_name & from,const account_name & receiver,const asset & payment,bool cpu)` | 
`public inline asset get_rentcpu_result(const account_name & from,const account_name & receiver,const asset & payment)` | 
`public inline asset get_rentnet_result(const account_name & from,const account_name & receiver,const asset & payment)` | 
`public inline action_result fundcpuloan(const account_name & from,const uint64_t loan_num,const asset & payment)` | 
`public inline action_result fundnetloan(const account_name & from,const uint64_t loan_num,const asset & payment)` | 
`public inline action_result defundcpuloan(const account_name & from,const uint64_t loan_num,const asset & amount)` | 
`public inline action_result defundnetloan(const account_name & from,const uint64_t loan_num,const asset & amount)` | 
`public inline action_result updaterex(const account_name & owner)` | 
`public inline action_result rexexec(const account_name & user,uint16_t max)` | 
`public inline action_result consolidate(const account_name & owner)` | 
`public inline action_result mvtosavings(const account_name & owner,const asset & rex)` | 
`public inline action_result mvfrsavings(const account_name & owner,const asset & rex)` | 
`public inline action_result closerex(const account_name & owner)` | 
`public inline fc::variant get_last_loan(bool cpu)` | 
`public inline fc::variant get_last_cpu_loan()` | 
`public inline fc::variant get_last_net_loan()` | 
`public inline fc::variant get_loan_info(const uint64_t & loan_num,bool cpu) const` | 
`public inline fc::variant get_cpu_loan(const uint64_t loan_num) const` | 
`public inline fc::variant get_net_loan(const uint64_t loan_num) const` | 
`public inline fc::variant get_dbw_obj(const account_name & from,const account_name & receiver) const` | 
`public inline asset get_rex_balance(const account_name & act) const` | 
`public inline fc::variant get_rex_balance_obj(const account_name & act) const` | 
`public inline asset get_rex_fund(const account_name & act) const` | 
`public inline fc::variant get_rex_fund_obj(const account_name & act) const` | 
`public inline asset get_rex_vote_stake(const account_name & act) const` | 
`public inline fc::variant get_rex_order(const account_name & act)` | 
`public inline fc::variant get_rex_order_obj(const account_name & act)` | 
`public inline fc::variant get_rex_pool() const` | 
`public inline fc::variant get_rex_return_pool() const` | 
`public inline fc::variant get_rex_return_buckets() const` | 
`public inline void setup_rex_accounts(const std::vector< account_name > & accounts,const asset & init_balance,const asset & net,const asset & cpu,bool deposit_into_rex_fund)` | 
`public inline action_result bidname(const account_name & bidder,const account_name & newname,const asset & bid)` | 
`public inline action_result bidname(std::string_view bidder,std::string_view newname,const asset & bid)` | 
`public inline action_result regproducer(const account_name & acnt,int params_fixture)` | 
`public inline action_result vote(const account_name & voter,const std::vector< account_name > & producers,const account_name & proxy)` | 
`public inline action_result vote(const account_name & voter,const std::vector< account_name > & producers,std::string_view proxy)` | 
`public inline uint32_t last_block_time() const` | 
`public inline asset get_balance(const account_name & act,symbol balance_symbol)` | 
`public inline asset get_balance(std::string_view act,symbol balance_symbol)` | 
`public inline fc::variant get_total_stake(const account_name & act)` | 
`public inline fc::variant get_total_stake(std::string_view act)` | 
`public inline fc::variant get_voter_info(const account_name & act)` | 
`public inline fc::variant get_voter_info(std::string_view act)` | 
`public inline fc::variant get_producer_info(const account_name & act)` | 
`public inline fc::variant get_producer_info(std::string_view act)` | 
`public inline fc::variant get_producer_info2(const account_name & act)` | 
`public inline fc::variant get_producer_info2(std::string_view act)` | 
`public inline void create_currency(name contract,name manager,asset maxsupply)` | 
`public inline void issue(const asset & amount,const name & manager)` | 
`public inline void transfer(const name & from,const name & to,const asset & amount,const name & manager)` | 
`public inline void transfer(const name & from,std::string_view to,const asset & amount,const name & manager)` | 
`public inline void transfer(std::string_view from,std::string_view to,const asset & amount,std::string_view manager)` | 
`public inline void transfer(std::string_view from,std::string_view to,const asset & amount)` | 
`public inline void issue_and_transfer(const name & to,const asset & amount,const name & manager)` | 
`public inline void issue_and_transfer(std::string_view to,const asset & amount,std::string_view manager)` | 
`public inline void issue_and_transfer(std::string_view to,const asset & amount,const name & manager)` | 
`public inline void issue_and_transfer(std::string_view to,const asset & amount)` | 
`public inline double stake2votes(asset stake)` | 
`public inline double stake2votes(const string & s)` | 
`public inline fc::variant get_stats(const string & symbolname)` | 
`public inline asset get_token_supply()` | 
`public inline uint64_t microseconds_since_epoch_of_iso_string(const fc::variant & v)` | 
`public inline fc::variant get_global_state()` | 
`public inline fc::variant get_global_state2()` | 
`public inline fc::variant get_global_state3()` | 
`public inline fc::variant get_refund_request(name account)` | 
`public inline abi_serializer initialize_multisig()` | 
`public inline vector< name > active_and_vote_producers()` | 
`public inline void cross_15_percent_threshold()` | 
`public inline action_result setinflation(int64_t annual_rate,int64_t inflation_pay_factor,int64_t votepay_factor)` | 

## Members

### `public abi_serializer abi_ser` {#classeosio__system_1_1eosio__system__tester_1a6553b790e5c86a895a17ba6d2b208913}





### `public abi_serializer token_abi_ser` {#classeosio__system_1_1eosio__system__tester_1ad27754cc7a6376a9734d05efe5d0baac}





### `public inline void basic_setup()` {#classeosio__system_1_1eosio__system__tester_1a4fab2c1ab589a64cbb4cb1db0c1f704e}





### `public inline void create_core_token(symbol core_symbol)` {#classeosio__system_1_1eosio__system__tester_1a0f053efff5f77dea7072b6df3e84190f}





### `public inline void deploy_contract(bool call_init)` {#classeosio__system_1_1eosio__system__tester_1a3cdcde139935536e87a548266069913b}





### `public inline void remaining_setup()` {#classeosio__system_1_1eosio__system__tester_1ada855d88294b713e445bba7dc594dd7c}





### `public inline  eosio_system_tester(`[`setup_level`](#classeosio__system_1_1eosio__system__tester_1ae7e0ff4e2ebe321e9508b432c8d1ca35)` l)` {#classeosio__system_1_1eosio__system__tester_1a44a0c6df9b49d9894c436eca2cfad07e}





### `public template<typename Lambda>`  <br/>`inline  eosio_system_tester(Lambda setup)` {#classeosio__system_1_1eosio__system__tester_1a3499991ede5f1d3619b54b2837c9c257}





### `public inline void create_accounts_with_resources(vector< account_name > accounts,account_name creator)` {#classeosio__system_1_1eosio__system__tester_1a0c60c30078a54826d8a28ea286f655ce}





### `public inline transaction_trace_ptr create_account_with_resources(account_name a,account_name creator,uint32_t ram_bytes)` {#classeosio__system_1_1eosio__system__tester_1a63919e0d46756f9f4aa372a98778fcbd}





### `public inline transaction_trace_ptr create_account_with_resources(account_name a,account_name creator,asset ramfunds,bool multisig,asset net,asset cpu)` {#classeosio__system_1_1eosio__system__tester_1a8bf65a4197f989e95359bf25418d7659}





### `public inline transaction_trace_ptr setup_producer_accounts(const std::vector< account_name > & accounts,asset ram,asset cpu,asset net)` {#classeosio__system_1_1eosio__system__tester_1ac8c7bd56d14a558e005bbf8acd350a95}





### `public inline action_result buyram(const account_name & payer,account_name receiver,const asset & eosin)` {#classeosio__system_1_1eosio__system__tester_1a03ead0f2dcc36130ff17afca29b727ca}





### `public inline action_result buyram(std::string_view payer,std::string_view receiver,const asset & eosin)` {#classeosio__system_1_1eosio__system__tester_1ab1b188663acb238700a26239b5ae2ad9}





### `public inline action_result buyrambytes(const account_name & payer,account_name receiver,uint32_t numbytes)` {#classeosio__system_1_1eosio__system__tester_1a315a10ead6b384340ce31fea858ca73a}





### `public inline action_result buyrambytes(std::string_view payer,std::string_view receiver,uint32_t numbytes)` {#classeosio__system_1_1eosio__system__tester_1af1989a5eea49e6fecafd1e5afb244f95}





### `public inline action_result sellram(const account_name & account,uint64_t numbytes)` {#classeosio__system_1_1eosio__system__tester_1a7a53705cef5f0c4c880dc3a65aa3a8ec}





### `public inline action_result sellram(std::string_view account,uint64_t numbytes)` {#classeosio__system_1_1eosio__system__tester_1a407908b657e28f5ad7e9ba1904539614}





### `public inline action_result push_action(const account_name & signer,const action_name & name,const variant_object & data,bool auth)` {#classeosio__system_1_1eosio__system__tester_1a294d15bfc4b915bd36cffb8154faabaf}





### `public inline action_result stake(const account_name & from,const account_name & to,const asset & net,const asset & cpu)` {#classeosio__system_1_1eosio__system__tester_1a19dfc7a9435a9d40c54f8933c088e5b2}





### `public inline action_result stake(std::string_view from,std::string_view to,const asset & net,const asset & cpu)` {#classeosio__system_1_1eosio__system__tester_1ad79507eaf003aff54ec3e6b3b91b2c11}





### `public inline action_result stake(const account_name & acnt,const asset & net,const asset & cpu)` {#classeosio__system_1_1eosio__system__tester_1ad6573013c72ff4f563acf10eea34600a}





### `public inline action_result stake(std::string_view acnt,const asset & net,const asset & cpu)` {#classeosio__system_1_1eosio__system__tester_1a9e4c0f8412ef9b1ca29b3967d76668ba}





### `public inline action_result stake_with_transfer(const account_name & from,const account_name & to,const asset & net,const asset & cpu)` {#classeosio__system_1_1eosio__system__tester_1acb43ec38190c09b97f0774f9e1ed0dba}





### `public inline action_result stake_with_transfer(std::string_view from,std::string_view to,const asset & net,const asset & cpu)` {#classeosio__system_1_1eosio__system__tester_1aa25b8e3716cac55da717db56bbf60e37}





### `public inline action_result stake_with_transfer(const account_name & acnt,const asset & net,const asset & cpu)` {#classeosio__system_1_1eosio__system__tester_1afea1622cde89b08f2f44c0c378b95d8f}





### `public inline action_result stake_with_transfer(std::string_view acnt,const asset & net,const asset & cpu)` {#classeosio__system_1_1eosio__system__tester_1a36a9d6ced4c4da301b21f4a91aae0fb6}





### `public inline action_result unstake(const account_name & from,const account_name & to,const asset & net,const asset & cpu)` {#classeosio__system_1_1eosio__system__tester_1aa400d0654037644e9ea13fc81b521b7b}





### `public inline action_result unstake(std::string_view from,std::string_view to,const asset & net,const asset & cpu)` {#classeosio__system_1_1eosio__system__tester_1a41eb069ce6a684c14f7a59d162e2cc1e}





### `public inline action_result unstake(const account_name & acnt,const asset & net,const asset & cpu)` {#classeosio__system_1_1eosio__system__tester_1a81069dea0d351098baa1c5ff362b5cda}





### `public inline action_result unstake(std::string_view acnt,const asset & net,const asset & cpu)` {#classeosio__system_1_1eosio__system__tester_1a4e80fb07f345d7d8429c12e877f41a0c}





### `public inline int64_t bancor_convert(int64_t S,int64_t R,int64_t T)` {#classeosio__system_1_1eosio__system__tester_1acfbdb6caf2b2828f1a61c0df1cc5a81e}





### `public inline int64_t get_net_limit(account_name a)` {#classeosio__system_1_1eosio__system__tester_1a345d24aec3753991e6717200b1223a68}





### `public inline int64_t get_cpu_limit(account_name a)` {#classeosio__system_1_1eosio__system__tester_1a41e42475b0d1c27804519cac227fb3bc}





### `public inline action_result deposit(const account_name & owner,const asset & amount)` {#classeosio__system_1_1eosio__system__tester_1a6a38854c1eb66a4ac172e7d3b555de19}





### `public inline action_result withdraw(const account_name & owner,const asset & amount)` {#classeosio__system_1_1eosio__system__tester_1a4146e614926727ff74b52c2cd2cf033f}





### `public inline action_result buyrex(const account_name & from,const asset & amount)` {#classeosio__system_1_1eosio__system__tester_1a3916c7408e4609e84dd7f3ffdaef489e}





### `public inline asset get_buyrex_result(const account_name & from,const asset & amount)` {#classeosio__system_1_1eosio__system__tester_1aaccfeda8eca71df19e4c0a355f5a4312}





### `public inline action_result unstaketorex(const account_name & owner,const account_name & receiver,const asset & from_net,const asset & from_cpu)` {#classeosio__system_1_1eosio__system__tester_1ae777944b5826fc95680df4a7b3fd2141}





### `public inline asset get_unstaketorex_result(const account_name & owner,const account_name & receiver,const asset & from_net,const asset & from_cpu)` {#classeosio__system_1_1eosio__system__tester_1a63acf9f8042be1845a31634ae8595615}





### `public inline action_result sellrex(const account_name & from,const asset & rex)` {#classeosio__system_1_1eosio__system__tester_1a978b8c24bf75f9f4de486cd5e09a25a8}





### `public inline asset get_sellrex_result(const account_name & from,const asset & rex)` {#classeosio__system_1_1eosio__system__tester_1a4f531d0c87d0b495a2fa0286fe8f5f21}





### `public inline auto get_rexorder_result(const transaction_trace_ptr & trace)` {#classeosio__system_1_1eosio__system__tester_1af5c3274d9dff9741985165ee52f9345d}





### `public inline action_result cancelrexorder(const account_name & owner)` {#classeosio__system_1_1eosio__system__tester_1a771ce588f7187ed5c4795e3d26c8233c}





### `public inline action_result rentcpu(const account_name & from,const account_name & receiver,const asset & payment,const asset & fund)` {#classeosio__system_1_1eosio__system__tester_1a18713af89a1654090a0516a60f25249f}





### `public inline action_result rentnet(const account_name & from,const account_name & receiver,const asset & payment,const asset & fund)` {#classeosio__system_1_1eosio__system__tester_1a0da15d442da5b99268330d5e12f8d572}





### `public inline asset _get_rentrex_result(const account_name & from,const account_name & receiver,const asset & payment,bool cpu)` {#classeosio__system_1_1eosio__system__tester_1a678d5b9ffe4f1273ed95cf404d5aa1d2}





### `public inline asset get_rentcpu_result(const account_name & from,const account_name & receiver,const asset & payment)` {#classeosio__system_1_1eosio__system__tester_1a90323c47bf67962f5c1a4ece3e22746f}





### `public inline asset get_rentnet_result(const account_name & from,const account_name & receiver,const asset & payment)` {#classeosio__system_1_1eosio__system__tester_1a5cc198ce96cfc9ec7ed26a75c3161eda}





### `public inline action_result fundcpuloan(const account_name & from,const uint64_t loan_num,const asset & payment)` {#classeosio__system_1_1eosio__system__tester_1a5e44f744e1a7f992c30b146d568d68b1}





### `public inline action_result fundnetloan(const account_name & from,const uint64_t loan_num,const asset & payment)` {#classeosio__system_1_1eosio__system__tester_1ae42010c2c7f512916fcfa573d5ef1f66}





### `public inline action_result defundcpuloan(const account_name & from,const uint64_t loan_num,const asset & amount)` {#classeosio__system_1_1eosio__system__tester_1a579e18d603498db516e244989d227270}





### `public inline action_result defundnetloan(const account_name & from,const uint64_t loan_num,const asset & amount)` {#classeosio__system_1_1eosio__system__tester_1a4e16e243a83e9d92148d3fff49f745b0}





### `public inline action_result updaterex(const account_name & owner)` {#classeosio__system_1_1eosio__system__tester_1aed0dc358ed43d15be3a778d80c55410f}





### `public inline action_result rexexec(const account_name & user,uint16_t max)` {#classeosio__system_1_1eosio__system__tester_1a39bf21779fbf0d6e860a583f8df64649}





### `public inline action_result consolidate(const account_name & owner)` {#classeosio__system_1_1eosio__system__tester_1a1bf1c4522b527bb365e808fc4c6aab9e}





### `public inline action_result mvtosavings(const account_name & owner,const asset & rex)` {#classeosio__system_1_1eosio__system__tester_1a9a36b004fef8c3a6d0facfc51c6a0d9a}





### `public inline action_result mvfrsavings(const account_name & owner,const asset & rex)` {#classeosio__system_1_1eosio__system__tester_1ad77b290540b7cd6790ad04ce7811a8fb}





### `public inline action_result closerex(const account_name & owner)` {#classeosio__system_1_1eosio__system__tester_1a51502ee7653a2cee8779e3804f271316}





### `public inline fc::variant get_last_loan(bool cpu)` {#classeosio__system_1_1eosio__system__tester_1a143113b4d08c88fdb8a013e944bd1928}





### `public inline fc::variant get_last_cpu_loan()` {#classeosio__system_1_1eosio__system__tester_1a65881b461203722d223743a6e86cdc63}





### `public inline fc::variant get_last_net_loan()` {#classeosio__system_1_1eosio__system__tester_1a2845d60e62059778773ee26f4c6249af}





### `public inline fc::variant get_loan_info(const uint64_t & loan_num,bool cpu) const` {#classeosio__system_1_1eosio__system__tester_1a14cb532b8b85ab96fd902ce4818ce104}





### `public inline fc::variant get_cpu_loan(const uint64_t loan_num) const` {#classeosio__system_1_1eosio__system__tester_1aab8f376e45d2051fdd817ffe9f9369e2}





### `public inline fc::variant get_net_loan(const uint64_t loan_num) const` {#classeosio__system_1_1eosio__system__tester_1a93d2a1cb0cfcd3cbd8bd7458e73992c7}





### `public inline fc::variant get_dbw_obj(const account_name & from,const account_name & receiver) const` {#classeosio__system_1_1eosio__system__tester_1a6e1bc6f4e832ceb842498c56c9075f15}





### `public inline asset get_rex_balance(const account_name & act) const` {#classeosio__system_1_1eosio__system__tester_1ac461b0845c0909670ea63557bc0b66fb}





### `public inline fc::variant get_rex_balance_obj(const account_name & act) const` {#classeosio__system_1_1eosio__system__tester_1a709b0f5fcf87b2efef2971a0c15d9a0d}





### `public inline asset get_rex_fund(const account_name & act) const` {#classeosio__system_1_1eosio__system__tester_1a9bf2f95b82dd447cbe00da9ac35edad6}





### `public inline fc::variant get_rex_fund_obj(const account_name & act) const` {#classeosio__system_1_1eosio__system__tester_1a006d8169fcce2262295ceeb50b2c644d}





### `public inline asset get_rex_vote_stake(const account_name & act) const` {#classeosio__system_1_1eosio__system__tester_1a5e64a18345f786e4231c9282aa087f20}





### `public inline fc::variant get_rex_order(const account_name & act)` {#classeosio__system_1_1eosio__system__tester_1a22162fc47dbf43df1b10cd696637d3e9}





### `public inline fc::variant get_rex_order_obj(const account_name & act)` {#classeosio__system_1_1eosio__system__tester_1ae639446b1000581d5404a2470ccac800}





### `public inline fc::variant get_rex_pool() const` {#classeosio__system_1_1eosio__system__tester_1adc8d15f66b51953b31471ae431203bfb}





### `public inline fc::variant get_rex_return_pool() const` {#classeosio__system_1_1eosio__system__tester_1a2a0f287afd099062caa6c41ccbd04bd0}





### `public inline fc::variant get_rex_return_buckets() const` {#classeosio__system_1_1eosio__system__tester_1af68fb8acfdccaec2b30ce2554cf87d89}





### `public inline void setup_rex_accounts(const std::vector< account_name > & accounts,const asset & init_balance,const asset & net,const asset & cpu,bool deposit_into_rex_fund)` {#classeosio__system_1_1eosio__system__tester_1adfc053b0749db71a4da569903f384379}





### `public inline action_result bidname(const account_name & bidder,const account_name & newname,const asset & bid)` {#classeosio__system_1_1eosio__system__tester_1ad41862f086e9bed7443a2b38b292e8a3}





### `public inline action_result bidname(std::string_view bidder,std::string_view newname,const asset & bid)` {#classeosio__system_1_1eosio__system__tester_1a6fb41f7d875e2730d4d88b4eb2e656bf}





### `public inline action_result regproducer(const account_name & acnt,int params_fixture)` {#classeosio__system_1_1eosio__system__tester_1a5c4a1ddae7b062d0a5864820638e62b4}





### `public inline action_result vote(const account_name & voter,const std::vector< account_name > & producers,const account_name & proxy)` {#classeosio__system_1_1eosio__system__tester_1a843ab97e6090ad56369f85749542be5e}





### `public inline action_result vote(const account_name & voter,const std::vector< account_name > & producers,std::string_view proxy)` {#classeosio__system_1_1eosio__system__tester_1abf775b2f5f2422555e886f114f682e89}





### `public inline uint32_t last_block_time() const` {#classeosio__system_1_1eosio__system__tester_1aee1cf394b09c7d3f73ca366d8e7afc79}





### `public inline asset get_balance(const account_name & act,symbol balance_symbol)` {#classeosio__system_1_1eosio__system__tester_1ae5088f57b04b156f822d6ff47681172a}





### `public inline asset get_balance(std::string_view act,symbol balance_symbol)` {#classeosio__system_1_1eosio__system__tester_1a275685caa99eaa12e3ff607531e1edc6}





### `public inline fc::variant get_total_stake(const account_name & act)` {#classeosio__system_1_1eosio__system__tester_1a9539a007f44e41461074f05b1efa9078}





### `public inline fc::variant get_total_stake(std::string_view act)` {#classeosio__system_1_1eosio__system__tester_1a81d67ba19737037e026cad8ee01e24a7}





### `public inline fc::variant get_voter_info(const account_name & act)` {#classeosio__system_1_1eosio__system__tester_1a62935be2581d8b7d6d38f5009f4131b1}





### `public inline fc::variant get_voter_info(std::string_view act)` {#classeosio__system_1_1eosio__system__tester_1a6ff715a6bacc35dfa9327ac2c9b84bca}





### `public inline fc::variant get_producer_info(const account_name & act)` {#classeosio__system_1_1eosio__system__tester_1ab43aee8d11661b443993370901b68e2c}





### `public inline fc::variant get_producer_info(std::string_view act)` {#classeosio__system_1_1eosio__system__tester_1a19f96e654e9e2f1cb809d134d393dbc0}





### `public inline fc::variant get_producer_info2(const account_name & act)` {#classeosio__system_1_1eosio__system__tester_1ab856c77dcef575f37057044e77c7645d}





### `public inline fc::variant get_producer_info2(std::string_view act)` {#classeosio__system_1_1eosio__system__tester_1a56f664849c185ca19acdf55e6d84f357}





### `public inline void create_currency(name contract,name manager,asset maxsupply)` {#classeosio__system_1_1eosio__system__tester_1a7df3e836a238c57f8594b36834d241c4}





### `public inline void issue(const asset & amount,const name & manager)` {#classeosio__system_1_1eosio__system__tester_1a8144e5150722d9565526fe3f5da73bc6}





### `public inline void transfer(const name & from,const name & to,const asset & amount,const name & manager)` {#classeosio__system_1_1eosio__system__tester_1a6ce6277e5545006b0528b09c1c89dec8}





### `public inline void transfer(const name & from,std::string_view to,const asset & amount,const name & manager)` {#classeosio__system_1_1eosio__system__tester_1af0ee9bb3c31aa10a013c7522af1fdba1}





### `public inline void transfer(std::string_view from,std::string_view to,const asset & amount,std::string_view manager)` {#classeosio__system_1_1eosio__system__tester_1a2361caa1339e2dd4a3727b7640730dd9}





### `public inline void transfer(std::string_view from,std::string_view to,const asset & amount)` {#classeosio__system_1_1eosio__system__tester_1abb2933afdcaf7e18a8f526b737aed8cb}





### `public inline void issue_and_transfer(const name & to,const asset & amount,const name & manager)` {#classeosio__system_1_1eosio__system__tester_1ab1401976ac157bfdd31b92dd10a56a54}





### `public inline void issue_and_transfer(std::string_view to,const asset & amount,std::string_view manager)` {#classeosio__system_1_1eosio__system__tester_1a5fbeb0a3214e4e51de3abd29b5b4a59b}





### `public inline void issue_and_transfer(std::string_view to,const asset & amount,const name & manager)` {#classeosio__system_1_1eosio__system__tester_1a4b08957ce831b8b92eb2664c37785213}





### `public inline void issue_and_transfer(std::string_view to,const asset & amount)` {#classeosio__system_1_1eosio__system__tester_1ad665af58abde40741213e8a97a4b49f7}





### `public inline double stake2votes(asset stake)` {#classeosio__system_1_1eosio__system__tester_1a6b99acf015bceecb5efe646e8581f7f1}





### `public inline double stake2votes(const string & s)` {#classeosio__system_1_1eosio__system__tester_1ad1e062371feb52e43cd63f1878340ccb}





### `public inline fc::variant get_stats(const string & symbolname)` {#classeosio__system_1_1eosio__system__tester_1ad373b5b15515f68610dfa0a3f637452e}





### `public inline asset get_token_supply()` {#classeosio__system_1_1eosio__system__tester_1a787b2e1fec87415e568f0ae1350e3404}





### `public inline uint64_t microseconds_since_epoch_of_iso_string(const fc::variant & v)` {#classeosio__system_1_1eosio__system__tester_1a8149fd6ecbd28d8fef0e9773560b8c60}





### `public inline fc::variant get_global_state()` {#classeosio__system_1_1eosio__system__tester_1a0fd6e250611cdb6a1c77fd3bf9dbd430}





### `public inline fc::variant get_global_state2()` {#classeosio__system_1_1eosio__system__tester_1aa9c99ba30baea1a26f7c66cfc49ab0ad}





### `public inline fc::variant get_global_state3()` {#classeosio__system_1_1eosio__system__tester_1a0814dde23aecedb7ad38800784951b13}





### `public inline fc::variant get_refund_request(name account)` {#classeosio__system_1_1eosio__system__tester_1ada1743be54f74d015482cd8909f25c84}





### `public inline abi_serializer initialize_multisig()` {#classeosio__system_1_1eosio__system__tester_1af0e3099fcc062cccac6d268abd8b52ca}





### `public inline vector< name > active_and_vote_producers()` {#classeosio__system_1_1eosio__system__tester_1a768f85f1c86806f972e63c8546dd49d5}





### `public inline void cross_15_percent_threshold()` {#classeosio__system_1_1eosio__system__tester_1ab97524dc86760d07e8fd71eea2d9d6bf}





### `public inline action_result setinflation(int64_t annual_rate,int64_t inflation_pay_factor,int64_t votepay_factor)` {#classeosio__system_1_1eosio__system__tester_1a4bf9437b44cc9514362b25c30500467f}






# namespace `MyLibrary`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``Example``](#class_my_library_1_1_example)    | 
`class `[``SubclassExample``](#class_my_library_1_1_subclass_example)    | 

# class `Example` {#class_my_library_1_1_example}




[Example](#class_my_library_1_1_example) class to demonstrate the features of the custom CSS.

jothepro

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::string test(const std::string & test)` | brief summary
`public int virtualfunc()` | 

## Members

### `public std::string test(const std::string & test)` {#class_my_library_1_1_example_1a1c0046b0674eb4cad09c5d3e943912b8}

brief summary

doxygen test documentation


#### Parameters
* `test` this is the only parameter of this test function. It does nothing!






Supported elementsThese elements have been tested with the custom CSS.

Lists

* element 1


* element 2



* element 1 
```cpp
code in lists
```



* element 2




QuotesThis is an **awesome** design...

...do you agree? 

*- jothepro*

Code block
```cpp
code within md fences (```)
```



```cpp
// code within @code block
if(true) {
   auto example = std::make_shared<Example>(5);
   example->test("test");
}
```
// code within indented code block
auto test = std::shared_ptr<Example(5);


Inline `code` elements in a text. Lorem Ipsum set dolor. This also works within multiline text and does not break the `layout`.

special hintsthis is a warning only for demonstration purposes

this is a note to show that notes work. They can also include `code`: 
```cpp
void this_looks_awesome();
```


Bugthis css has no bugs, it is perfect... NOT!



DeprecatedNone of this will be deprecated, because it's beautiful!



This is an invariant

This is a precondition

TodoThis theme is never finished!



This is awesome!

### `public int virtualfunc()` {#class_my_library_1_1_example_1a8431ef1c10c4e2a36302b8e8556514f6}






# class `SubclassExample` {#class_my_library_1_1_subclass_example}

```
class SubclassExample
  : public MyLibrary::Example
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public virtual int virtualfunc()` | 
`public inline std::shared_ptr< std::string > super_long_function_with_lots_of_parameters(std::shared_ptr< std::string > & text,std::shared_ptr< std::string > & text2)` | 

## Members

### `public virtual int virtualfunc()` {#class_my_library_1_1_subclass_example_1a6c1b7e5c6e56d31a169ddd42e8992300}



Bugsecond bug 


#### Returns

### `public inline std::shared_ptr< std::string > super_long_function_with_lots_of_parameters(std::shared_ptr< std::string > & text,std::shared_ptr< std::string > & text2)` {#class_my_library_1_1_subclass_example_1a8e9bd40c63ccc7b074c2aabf6fecb4f9}






# namespace `blockinfo_tester`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[``get_latest_block_batch_info``](#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1get__latest__block__batch__info)    | Input data structure for `[get_latest_block_batch_info](#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1get__latest__block__batch__info)` RPC.
`struct `[``latest_block_batch_info_result``](#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1latest__block__batch__info__result)    | Output data structure for `[get_latest_block_batch_info](#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1get__latest__block__batch__info)` RPC.

# struct `get_latest_block_batch_info` {#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1get__latest__block__batch__info}


Input data structure for `[get_latest_block_batch_info](#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1get__latest__block__batch__info)` RPC.

Use this struct as the input for a call to the `[get_latest_block_batch_info](#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1get__latest__block__batch__info)` RPC. That call will return the result as the `[latest_block_batch_info_result](#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1latest__block__batch__info__result)` struct.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint32_t batch_start_height_offset` | 
`public uint32_t batch_size` | 

## Members

### `public uint32_t batch_start_height_offset` {#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1get__latest__block__batch__info_1ac601553260c24e5fe6ed17828e4a41ef}





### `public uint32_t batch_size` {#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1get__latest__block__batch__info_1a82ebd86affa47e2f8024b9083374ed8a}






# struct `latest_block_batch_info_result` {#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1latest__block__batch__info__result}


Output data structure for `[get_latest_block_batch_info](#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1get__latest__block__batch__info)` RPC.



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::optional< `[`block_batch_info`](#structeosiosystem_1_1block__info_1_1block__batch__info)` > result` | 
`public `[`varint`](#namespacesystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1a3b3bb00116a9d1c649c8cd6b9d8eb43b)` error_code` | 
`public inline bool has_error() const` | 
`public inline `[`error_code_enum`](#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1latest__block__batch__info__result_1aeb9f839d5c51488952f8f1381f89a64a)` get_error() const` | 

## Members

### `public std::optional< `[`block_batch_info`](#structeosiosystem_1_1block__info_1_1block__batch__info)` > result` {#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1latest__block__batch__info__result_1a6bef31839eb6c99ff3bb5f69bbb8b7a5}





### `public `[`varint`](#namespacesystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1a3b3bb00116a9d1c649c8cd6b9d8eb43b)` error_code` {#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1latest__block__batch__info__result_1aa3bf20610c6a68ed0a5e3261cbdb5808}





### `public inline bool has_error() const` {#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1latest__block__batch__info__result_1a8c36a77acb6436c335c075939e5ffc0d}





### `public inline `[`error_code_enum`](#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1latest__block__batch__info__result_1aeb9f839d5c51488952f8f1381f89a64a)` get_error() const` {#structsystem__contracts_1_1testing_1_1test__contracts_1_1blockinfo__tester_1_1latest__block__batch__info__result_1a98a9efbd6bbda91e666bd57e16095adb}






# namespace `anonymous_namespace{block_info.cpp}`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

# namespace `anonymous_namespace{blockinfo_tester.cpp}`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

# namespace `fc`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

# namespace `std`



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

# class `eosio_msig_tester` {#classeosio__msig__tester}

```
class eosio_msig_tester
  : public tester
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public abi_serializer abi_ser` | 
`public inline  eosio_msig_tester()` | 
`public inline transaction_trace_ptr create_account_with_resources(account_name a,account_name creator,asset ramfunds,bool multisig,asset net,asset cpu)` | 
`public inline void create_currency(name contract,name manager,asset maxsupply)` | 
`public inline void issue(name to,const asset & amount,name manager)` | 
`public inline void transfer(name from,name to,const string & amount,name manager)` | 
`public inline asset get_balance(const account_name & act)` | 
`public inline transaction_trace_ptr push_action(const account_name & signer,const action_name & name,const variant_object & data,bool auth)` | 
`public transaction reqauth(account_name from,const vector< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > & auths,const fc::microseconds & max_serialization_time)` | 
`public void check_traces(transaction_trace_ptr trace,std::vector< std::map< std::string, name > > res)` | 

## Members

### `public abi_serializer abi_ser` {#classeosio__msig__tester_1a9efbc12e7c9c1af0cbdf720d001ece21}





### `public inline  eosio_msig_tester()` {#classeosio__msig__tester_1aa85fb06f88b529a259bcee1e44b39c6e}





### `public inline transaction_trace_ptr create_account_with_resources(account_name a,account_name creator,asset ramfunds,bool multisig,asset net,asset cpu)` {#classeosio__msig__tester_1a35d3eb428ee15ec4872b9c5de7c69b7c}





### `public inline void create_currency(name contract,name manager,asset maxsupply)` {#classeosio__msig__tester_1aec0f68b4b38258dcaa16a56cbd5df981}





### `public inline void issue(name to,const asset & amount,name manager)` {#classeosio__msig__tester_1afbc2c6b54ca89e23f38c69c17a7614e1}





### `public inline void transfer(name from,name to,const string & amount,name manager)` {#classeosio__msig__tester_1a36777e1be270e12da6820c5ced36a7cf}





### `public inline asset get_balance(const account_name & act)` {#classeosio__msig__tester_1a5e829b6d3bbc790950a6b6975569ecba}





### `public inline transaction_trace_ptr push_action(const account_name & signer,const action_name & name,const variant_object & data,bool auth)` {#classeosio__msig__tester_1a347f829125d7ae438a4cb83ef97d4127}





### `public transaction reqauth(account_name from,const vector< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > & auths,const fc::microseconds & max_serialization_time)` {#classeosio__msig__tester_1ad4ab30dbfdd5474e435f18b529c3adbb}





### `public void check_traces(transaction_trace_ptr trace,std::vector< std::map< std::string, name > > res)` {#classeosio__msig__tester_1ac643f42b775707bd1f9817b367ba976d}






# class `eosio_token_tester` {#classeosio__token__tester}

```
class eosio_token_tester
  : public tester
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public abi_serializer abi_ser` | 
`public inline  eosio_token_tester()` | 
`public inline action_result push_action(const account_name & signer,const action_name & name,const variant_object & data)` | 
`public inline fc::variant get_stats(const string & symbolname)` | 
`public inline fc::variant get_account(account_name acc,const string & symbolname)` | 
`public inline action_result create(account_name issuer,asset maximum_supply)` | 
`public inline action_result issue(account_name issuer,asset quantity,string memo)` | 
`public inline action_result retire(account_name issuer,asset quantity,string memo)` | 
`public inline action_result transfer(account_name from,account_name to,asset quantity,string memo)` | 
`public inline action_result open(account_name owner,const string & symbolname,account_name ram_payer)` | 
`public inline action_result close(account_name owner,const string & symbolname)` | 

## Members

### `public abi_serializer abi_ser` {#classeosio__token__tester_1ac4ebd75f3bdd60e208b92dad3103c964}





### `public inline  eosio_token_tester()` {#classeosio__token__tester_1aa5097dd3c31132c8011d419553a96c5e}





### `public inline action_result push_action(const account_name & signer,const action_name & name,const variant_object & data)` {#classeosio__token__tester_1ad56ce6aae361094e9aa64abcfe1f254d}





### `public inline fc::variant get_stats(const string & symbolname)` {#classeosio__token__tester_1a62cd9713d91f9439f7c44c7d1389dd9c}





### `public inline fc::variant get_account(account_name acc,const string & symbolname)` {#classeosio__token__tester_1a06dbdfcb390193a94f9c9913bb27b320}





### `public inline action_result create(account_name issuer,asset maximum_supply)` {#classeosio__token__tester_1a54c6aa3f1eba3bd1050d395eea68cfc4}





### `public inline action_result issue(account_name issuer,asset quantity,string memo)` {#classeosio__token__tester_1a5d64656235d5704c14b002a69e8a19ec}





### `public inline action_result retire(account_name issuer,asset quantity,string memo)` {#classeosio__token__tester_1ad32d6698c6e65beba5973abd80345136}





### `public inline action_result transfer(account_name from,account_name to,asset quantity,string memo)` {#classeosio__token__tester_1aeaf06091429936efca40ec64a1c2add6}





### `public inline action_result open(account_name owner,const string & symbolname,account_name ram_payer)` {#classeosio__token__tester_1a9af35c072de8203b1b6edc3cec95b922}





### `public inline action_result close(account_name owner,const string & symbolname)` {#classeosio__token__tester_1aae88a895aa2c9d3d4b479740db234ee7}






# class `eosio_wrap_tester` {#classeosio__wrap__tester}

```
class eosio_wrap_tester
  : public tester
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  eosio_wrap_tester()` | 
`public inline void propose(name proposer,name proposal_name,vector< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > requested_permissions,const transaction & trx)` | 
`public inline void approve(name proposer,name proposal_name,name approver)` | 
`public inline void unapprove(name proposer,name proposal_name,name unapprover)` | 
`public transaction wrap_exec(account_name executer,const transaction & trx,uint32_t expiration)` | 
`public transaction reqauth(account_name from,const vector< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > & auths,uint32_t expiration)` | 
`public void check_traces(transaction_trace_ptr trace,std::vector< std::map< std::string, name > > res)` | 

## Members

### `public inline  eosio_wrap_tester()` {#classeosio__wrap__tester_1a16769250ac07aefd4a9799dbd3888155}





### `public inline void propose(name proposer,name proposal_name,vector< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > requested_permissions,const transaction & trx)` {#classeosio__wrap__tester_1a5f6d2856669577e22f3f1f2cff71030f}





### `public inline void approve(name proposer,name proposal_name,name approver)` {#classeosio__wrap__tester_1af293cc197550f4a892eb96ffca162b48}





### `public inline void unapprove(name proposer,name proposal_name,name unapprover)` {#classeosio__wrap__tester_1a640df1c8559085b577c7350a38cb171b}





### `public transaction wrap_exec(account_name executer,const transaction & trx,uint32_t expiration)` {#classeosio__wrap__tester_1a0e0a3b21a115f1416b098fcc1627e9ba}





### `public transaction reqauth(account_name from,const vector< `[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > & auths,uint32_t expiration)` {#classeosio__wrap__tester_1a0db68a2a12036459525e4d52dc820027}





### `public void check_traces(transaction_trace_ptr trace,std::vector< std::map< std::string, name > > res)` {#classeosio__wrap__tester_1a3bc694e07173b6c0815a5ffeabcd5d4c}






# class `powup_results` {#classpowup__results}

```
class powup_results
  : private eosio::contract
```  



The action `powupresult` is a no-op. It is added as an inline convenience action to `powerup` reservation. This inline convenience action does not have any effect, however, its data includes the result of the parent action and appears in its trace.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void powupresult(const asset & fee,const int64_t powup_net,const int64_t powup_cpu)` | 

## Members

### `public void powupresult(const asset & fee,const int64_t powup_net,const int64_t powup_cpu)` {#classpowup__results_1a92bf8a4505d35524f2708a7984d5df59}



powupresult action.


#### Parameters
* `fee` - powerup fee amount 


* `powup_net` - amount of powup NET tokens 


* `powup_cpu` - amount of powup CPU tokens


# class `rex_results` {#classrex__results}

```
class rex_results
  : private eosio::contract
```  



The actions `buyresult`, `sellresult`, `rentresult`, and `orderresult` of `rex.results` are all no-ops. They are added as inline convenience actions to `rentnet`, `rentcpu`, `buyrex`, `unstaketorex`, and `sellrex`. An inline convenience action does not have any effect, however, its data includes the result of the parent action and appears in its trace.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void buyresult(const asset & rex_received)` | 
`public void sellresult(const asset & proceeds)` | 
`public void orderresult(const name & owner,const asset & proceeds)` | 
`public void rentresult(const asset & rented_tokens)` | 

## Members

### `public void buyresult(const asset & rex_received)` {#classrex__results_1a955ccff2c80578de034ee8c16bb29b47}



Buyresult action.


#### Parameters
* `rex_received` - amount of tokens used in buy order

### `public void sellresult(const asset & proceeds)` {#classrex__results_1a2fdb9897a541ee103c618e8b311afab9}



Sellresult action.


#### Parameters
* `proceeds` - amount of tokens used in sell order

### `public void orderresult(const name & owner,const asset & proceeds)` {#classrex__results_1aadee1538b7d17cbbe6efd8438fa46ae1}



Orderresult action.


#### Parameters
* `owner` - the owner of the order 


* `proceeds` - amount of tokens used in order

### `public void rentresult(const asset & rented_tokens)` {#classrex__results_1ab9cb69866c17d4344e0d50ea810ecef4}



Rentresult action.


#### Parameters
* `rented_tokens` - amount of rented tokens


# class `sendinline` {#classsendinline}

```
class sendinline
  : public eosio::contract
```  



`eosio.code` is a virtual permission (there is no private or public key associated with it). Therefore, this test tests how `eosio.msig` contract reacts to a smart contract submitting a proposal and approving/unnapproving itself.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline void send(eosio::name contract,eosio::name action_name,std::vector< `[`eosio::permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > auths,std::vector< char > payload)` | 

## Members

### `public inline void send(eosio::name contract,eosio::name action_name,std::vector< `[`eosio::permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` > auths,std::vector< char > payload)` {#classsendinline_1a9302e043cf61d0320016d60788389ac8}






# struct `_abi_hash` {#struct__abi__hash}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public name owner` | 
`public fc::sha256 hash` | 

## Members

### `public name owner` {#struct__abi__hash_1a47247c544376bfdebcf841bacaebc84c}





### `public fc::sha256 hash` {#struct__abi__hash_1a003f02528a5370378b9e6d497116030a}






# struct `powerup_tester` {#structpowerup__tester}

```
struct powerup_tester
  : public eosio_system_tester
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[``account_info``](#structpowerup__tester_1_1account__info)        | 
`public inline  powerup_tester()` | 
`public inline void start_rex()` | 
`public template<typename F>`  <br/>`inline powerup_config make_config(F f)` | 
`public inline powerup_config make_config()` | 
`public template<typename F>`  <br/>`inline powerup_config make_default_config(F f)` | 
`public inline action_result configbw(const powerup_config & config)` | 
`public inline action_result powerupexec(name user,uint16_t max)` | 
`public inline action_result powerup(const name & payer,const name & receiver,uint32_t days,int64_t net_frac,int64_t cpu_frac,const asset & max_payment)` | 
`public inline powerup_state get_state()` | 
`public inline `[`account_info`](#structpowerup__tester_1_1account__info)` get_account_info(account_name acc)` | 
`public inline void check_powerup(const name & payer,const name & receiver,uint32_t days,int64_t net_frac,int64_t cpu_frac,const asset & expected_fee,int64_t expected_net,int64_t expected_cpu)` | 

## Members

### `struct `[``account_info``](#structpowerup__tester_1_1account__info) {#structpowerup__tester_1_1account__info}




### `public inline  powerup_tester()` {#structpowerup__tester_1a33ccf16b67058add5ae3498a8daafe89}





### `public inline void start_rex()` {#structpowerup__tester_1a34191f1e526e0ab51ca1bc9381588894}





### `public template<typename F>`  <br/>`inline powerup_config make_config(F f)` {#structpowerup__tester_1aa65da2bd4e108cad3bffe0447af2a849}





### `public inline powerup_config make_config()` {#structpowerup__tester_1a116a2cb3c9800da6a1a4ca152ec23a38}





### `public template<typename F>`  <br/>`inline powerup_config make_default_config(F f)` {#structpowerup__tester_1a256c4944a0d87e3a5c15710911024ebc}





### `public inline action_result configbw(const powerup_config & config)` {#structpowerup__tester_1ac8ebf6926b91d8dd32755741563dd2ab}





### `public inline action_result powerupexec(name user,uint16_t max)` {#structpowerup__tester_1adb1bb77a9818531036e201e025624fd4}





### `public inline action_result powerup(const name & payer,const name & receiver,uint32_t days,int64_t net_frac,int64_t cpu_frac,const asset & max_payment)` {#structpowerup__tester_1ab94c81014001e6f92967751217b731c0}





### `public inline powerup_state get_state()` {#structpowerup__tester_1a953eee68bfc1ab4ac7784449cd15fba1}





### `public inline `[`account_info`](#structpowerup__tester_1_1account__info)` get_account_info(account_name acc)` {#structpowerup__tester_1aac4bc9c1d11daddcbe11c942a3c33415}





### `public inline void check_powerup(const name & payer,const name & receiver,uint32_t days,int64_t net_frac,int64_t cpu_frac,const asset & expected_fee,int64_t expected_net,int64_t expected_cpu)` {#structpowerup__tester_1af816263ed2ef2c17188e500e99738e53}






# struct `account_info` {#structpowerup__tester_1_1account__info}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int64_t ram` | 
`public int64_t net` | 
`public int64_t cpu` | 
`public asset liquid` | 

## Members

### `public int64_t ram` {#structpowerup__tester_1_1account__info_1ae209834e350c97f89e61d129a421fb16}





### `public int64_t net` {#structpowerup__tester_1_1account__info_1ab26e90733905a912078c48ac3421a797}





### `public int64_t cpu` {#structpowerup__tester_1_1account__info_1a632159a928c93f8df3ffc79eb9be654b}





### `public asset liquid` {#structpowerup__tester_1_1account__info_1ab3c1cbaed3d1313b93370edf46ed8178}






# struct `accounts` {#structaccounts}


Таблица хранения отозванных аккаунтов гостей

@table newaccounts @contract _me @scope _me.

Хранит аккаунты, отозванные у гостей путём замены их активного ключа на ключ регистратора за истечением срока давности без поступления оплаты.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::name username` | 
`public eosio::name status` | 
`public uint64_t reputation` | 
`public std::string uid` | 
`public eosio::checksum256 uid_hash` | 
`public eosio::name type` | 
`public eosio::name registrator` | 
`public eosio::name referer` | 
`public eosio::asset registration_amount` | 
`public std::string meta` | 
`public eosio::time_point_sec registered_at` | 
`public eosio::time_point_sec last_update` | 
`public eosio::time_point_sec signature_expires_at` | 
`public eosio::time_point_sec signature_last_update` | 
`public inline uint64_t primary_key() const` | 
`public inline uint64_t by_referer() const` | 
`public inline uint64_t by_type() const` | 
`public inline uint64_t by_status() const` | 
`public inline uint64_t by_registr() const` | 
`public inline eosio::checksum256 byuidhash() const` | 

## Members

### `public eosio::name username` {#structaccounts_1a05876c5415522c3ff8a3d8e8a783d6a7}



имя аккаунта гостя

### `public eosio::name status` {#structaccounts_1a0498f8a07ad571d52548a076370d9253}



статус аккаунта: "pending" - ожидание утверждения советом, "active" - активный аккаунт; "blocked" - заблокированный аккаунт; "deleted" - удален пользователем;

### `public uint64_t reputation` {#structaccounts_1aaa9631adef3e542db5ddc1e2388dfd61}





### `public std::string uid` {#structaccounts_1af38528c6fa35cb2763035b76af1a8189}





### `public eosio::checksum256 uid_hash` {#structaccounts_1ae973d8ff759b32dc26bb3b5e1174619d}





### `public eosio::name type` {#structaccounts_1af1bfc2d1e94ebb71271c0ce836558160}





### `public eosio::name registrator` {#structaccounts_1a432b7b14e9da714d2de1546dbbd74a7e}



имя аккаунта регистратора

### `public eosio::name referer` {#structaccounts_1a42c6052506d3b2d89bbbb95913591809}





### `public eosio::asset registration_amount` {#structaccounts_1a9aa73b3535b162d4dbcdb5c581146ce2}



количество токенов к оплате

### `public std::string meta` {#structaccounts_1aeecfd8c0939c8e7de20db6126b965bd9}





### `public eosio::time_point_sec registered_at` {#structaccounts_1a5ab584c673fa71b1aebd8eb3ec4e69e5}





### `public eosio::time_point_sec last_update` {#structaccounts_1a84633a253175f02bb81c1260645780ea}





### `public eosio::time_point_sec signature_expires_at` {#structaccounts_1a38b262d4ca61e4cecb3f1eab1a5d3887}





### `public eosio::time_point_sec signature_last_update` {#structaccounts_1a00f7df522967257d7bf5fd065d942241}





### `public inline uint64_t primary_key() const` {#structaccounts_1ac5356720544cfbfc9b82d829f4fa4f37}



return username - primary_key

### `public inline uint64_t by_referer() const` {#structaccounts_1a779b22d35ce6564c3b2e34e03b77aa29}





### `public inline uint64_t by_type() const` {#structaccounts_1a336640e99b5ae6106b3715cae302ff46}





### `public inline uint64_t by_status() const` {#structaccounts_1ae34d3eff438789f8e09b1fef2eed2af2}





### `public inline uint64_t by_registr() const` {#structaccounts_1a88ed8c7045efdf796cfadb54e91ef284}





### `public inline eosio::checksum256 byuidhash() const` {#structaccounts_1a15da9b51d8a9d7acaff45fdeaa80c5a4}






# struct `authority` {#structauthority}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint32_t threshold` | 
`public std::vector< `[`key_weight`](#structkey__weight)` > keys` | 
`public std::vector< `[`permission_level_weight`](#structpermission__level__weight)` > accounts` | 
`public std::vector< `[`wait_weight`](#structwait__weight)` > waits` | 

## Members

### `public uint32_t threshold` {#structauthority_1ab9fbc4a419012844e80ffebb57d76971}





### `public std::vector< `[`key_weight`](#structkey__weight)` > keys` {#structauthority_1a7538d1edffef8dd8ebe41758fbc4fdd8}





### `public std::vector< `[`permission_level_weight`](#structpermission__level__weight)` > accounts` {#structauthority_1a0929cd72740ad0953b59fdc1df188b60}





### `public std::vector< `[`wait_weight`](#structwait__weight)` > waits` {#structauthority_1a809a2560b802fdd64dab31f7193a045b}






# struct `balances_base` {#structbalances__base}


Таблица балансов

Эта таблица используется для хранения информации о балансах пользователей в системе.


#### Parameters
* `id` Идентификатор баланса, используемый как первичный ключ 


* `contract` Имя контракта токена 


* `quantity` Количество токенов на балансе





Дополнительный индекс по комбинации contract и symbol позволяет искать баланс по этим двум полям.

Пример использования: 
```cpp
[balances_index](#balances_8hpp_1a2f044097a1d44c2a73b8f5bd7719439e) balances(_me, username.value);
auto [balance](#eosio_8token__tests_8cpp_1a1e7ef09ce66d09456a55c47a8c42f3dc) = balances.find(id);
```

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint64_t id` | 
`public eosio::name contract` | 
`public eosio::asset quantity` | 
`public inline uint64_t primary_key() const` | 
`public inline uint128_t byconsym() const` | 

## Members

### `public uint64_t id` {#structbalances__base_1a2069a54454c59cae6ac2a977002bc8ce}



идентификатор баланса

### `public eosio::name contract` {#structbalances__base_1acebf235da280f8d16533b6913912da41}



имя контракта токена

### `public eosio::asset quantity` {#structbalances__base_1a1c3e3dfd8436a6e847dfbe620ba26c23}



количество токенов на балансе

### `public inline uint64_t primary_key() const` {#structbalances__base_1a242d9cbeea53e487eff7eb9349327931}



return id - primary_key

### `public inline uint128_t byconsym() const` {#structbalances__base_1af43d841c9f521f6fbbed7c943d4fd366}



возвращает уникальный индекс, сформированный из значения contract и символа токена


# struct `bank` {#structbank}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::string account` | 
`public eosio::time_point_sec created_at` | 
`public eosio::time_point_sec last_update` | 
`public bool is_active` | 

## Members

### `public std::string account` {#structbank_1ac222eff37f2528232734f3c6b4425b67}





### `public eosio::time_point_sec created_at` {#structbank_1a20b362142d5c764f45432e0efd1f36e0}





### `public eosio::time_point_sec last_update` {#structbank_1a9d3a91fdf7922097c93148ffdf4c815d}





### `public bool is_active` {#structbank_1a5364d9937ea115f7b721270e942505b0}






# struct `board_member` {#structboard__member}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::name username` | 
`public bool is_voting` | 
`public std::string position_title` | 
`public eosio::name position` | 

## Members

### `public eosio::name username` {#structboard__member_1adf5286ff237471ceabc65d4d091972d0}





### `public bool is_voting` {#structboard__member_1a20b8902343fc67a6f8a0665a4e40b330}





### `public std::string position_title` {#structboard__member_1a2961218c9a14c7125a53ade0c15e5598}





### `public eosio::name position` {#structboard__member_1a10fea881563dbbbbee4ad11c3756e7ec}






# struct `boards` {#structboards}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint64_t id` | 
`public eosio::name type` | 
`public std::string name` | 
`public std::string description` | 
`public std::vector< `[`board_member`](#structboard__member)` > members` | 
`public eosio::time_point_sec created_at` | 
`public eosio::time_point_sec last_update` | 
`public inline uint64_t primary_key() const` | 
`public inline uint64_t by_type() const` | 
`public inline bool is_valid_member(eosio::name member) const` | 
`public inline bool is_voting_member(eosio::name member) const` | 
`public inline bool is_valid_chairman(eosio::name chairman) const` | 
`public inline bool has_voting_right(eosio::name member) const` | 
`public inline uint64_t get_members_count() const` | 

## Members

### `public uint64_t id` {#structboards_1a4902e87f13247db8f837629544f12a6a}





### `public eosio::name type` {#structboards_1a277bb2ea397a8b6076584f07f2c4432f}





### `public std::string name` {#structboards_1ad9a12ccbc9bdbabfe1dbd5f7cffdb06f}





### `public std::string description` {#structboards_1ae8f0825aa67789f638169abf513ce674}





### `public std::vector< `[`board_member`](#structboard__member)` > members` {#structboards_1a784be337829b64e7caaa6c6657f5c262}





### `public eosio::time_point_sec created_at` {#structboards_1add47e6975c343415f278a0414c714066}





### `public eosio::time_point_sec last_update` {#structboards_1acaad31053c6dc00a9b99faaece7213bc}





### `public inline uint64_t primary_key() const` {#structboards_1a8a887a056d41000b8183975cc5fe0c91}





### `public inline uint64_t by_type() const` {#structboards_1a62601ce5131f1d2be8f17c3df5866f38}





### `public inline bool is_valid_member(eosio::name member) const` {#structboards_1a3108c80a73de20b8ad7a776e108abe26}





### `public inline bool is_voting_member(eosio::name member) const` {#structboards_1acfe79079ce96ef59fea0f86c95506cb8}





### `public inline bool is_valid_chairman(eosio::name chairman) const` {#structboards_1ad1e613d161e0dfb3bee0b043b71c13db}





### `public inline bool has_voting_right(eosio::name member) const` {#structboards_1a151ec00b76ae9f7c7fdc1e4dee7f0412}





### `public inline uint64_t get_members_count() const` {#structboards_1a3eb726cb1d52d85288567c3e5848828e}






# struct `connector` {#structconnector}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public asset balance` | 
`public double weight` | 

## Members

### `public asset balance` {#structconnector_1a7ccbf3db174c260f734d246d0a9cf3bd}





### `public double weight` {#structconnector_1ae1cde74f51c69400d187292f1c1a1b32}






# struct `core_sym` {#structcore__sym}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members


# struct `counts_base` {#structcounts__base}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::name key` | 
`public eosio::name secondary_key` | 
`public uint64_t value` | 
`public inline uint64_t primary_key() const` | 
`public inline uint128_t keyskey() const` | 
`public inline uint128_t keyvalue() const` | 

## Members

### `public eosio::name key` {#structcounts__base_1a190877bf5f40a7a357007574c5ecc1d7}





### `public eosio::name secondary_key` {#structcounts__base_1a54989b6bb7004b9dce497350707fce21}





### `public uint64_t value` {#structcounts__base_1a7e8ded653625d24a13ae3b651c42dd5a}





### `public inline uint64_t primary_key() const` {#structcounts__base_1a776ade72cbcce230ac5dd0c5d45b3578}



return id - primary_key

### `public inline uint128_t keyskey() const` {#structcounts__base_1acabcbd93c1b35dca98c77646bbfda21d}



(contract, blocked_now.symbol) - комбинированный secondary_key для получения курса по имени выходного контракта и символу

### `public inline uint128_t keyvalue() const` {#structcounts__base_1a79af91982641a07988d9cf8f01dc1fd1}



(contract, blocked_now.symbol) - комбинированный secondary_key для получения курса по имени выходного контракта и символу


# struct `decisions` {#structdecisions}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint64_t id` | 
`public eosio::name coop_username` | 
`public eosio::name type` | 
`public uint64_t card_id` | 
`public std::vector< eosio::name > votes_for` | 
`public std::vector< eosio::name > votes_against` | 
`public bool approved` | 
`public bool validated` | 
`public bool authorized` | 
`public bool certified` | 
`public bool executed` | 
`public inline uint64_t primary_key() const` | 
`public inline uint64_t by_coop() const` | 
`public inline uint64_t by_card() const` | 
`public inline uint64_t bytype() const` | 
`public inline uint64_t byapproved() const` | 
`public inline uint64_t byvalidated() const` | 
`public inline uint64_t byauthorized() const` | 
`public inline uint64_t bycertified() const` | 
`public inline uint64_t byexecuted() const` | 
`public inline void check_for_any_vote_exist(eosio::name member) const` | 
`public inline std::pair< uint64_t, uint64_t > get_votes_count() const` | 

## Members

### `public uint64_t id` {#structdecisions_1aa61841427ff58ac67bf67d16c00c0250}





### `public eosio::name coop_username` {#structdecisions_1a099935f67b922b218fb1087cced67665}





### `public eosio::name type` {#structdecisions_1a7a8e39491d6be766cd3c4fa1fadafbc0}





### `public uint64_t card_id` {#structdecisions_1a6dc4138b1457997c4b4b5f493b36a57d}





### `public std::vector< eosio::name > votes_for` {#structdecisions_1a8b734c20fd41967766efcd38cf7c0580}





### `public std::vector< eosio::name > votes_against` {#structdecisions_1a944df451a915494bc936415e24d39abe}





### `public bool approved` {#structdecisions_1a302e21ff37fe798e2b908a4fdd1bb7bb}





### `public bool validated` {#structdecisions_1adface34e69e2468b2986e6d395794a1a}





### `public bool authorized` {#structdecisions_1a980288ea11bd9b954357ddf4a094b4f3}





### `public bool certified` {#structdecisions_1a7132f2b0fb3d19396b176b64fc3e61a5}





### `public bool executed` {#structdecisions_1a6f62beae35e1d904de6888858368b432}





### `public inline uint64_t primary_key() const` {#structdecisions_1a7393d2d0ce88224d46edaa7973fb41dd}





### `public inline uint64_t by_coop() const` {#structdecisions_1a3084ac29d2db98d8b9bb1ad7a600c586}





### `public inline uint64_t by_card() const` {#structdecisions_1a63ad193a9e3448b1c03f6d91853b2589}





### `public inline uint64_t bytype() const` {#structdecisions_1a87937d6b4c5c378d3e3ac77141b11394}





### `public inline uint64_t byapproved() const` {#structdecisions_1a6cadd228516907f8eb55f915eb03d4b8}





### `public inline uint64_t byvalidated() const` {#structdecisions_1a9661d6706d87e72e74ad3590620e5009}





### `public inline uint64_t byauthorized() const` {#structdecisions_1ab166604702a060e0a03e885efa8c14b9}





### `public inline uint64_t bycertified() const` {#structdecisions_1abe34bd92cb25994c8c6f83df4e0a21cc}





### `public inline uint64_t byexecuted() const` {#structdecisions_1aa6bcc23d78063077e66c58c7feed46a7}





### `public inline void check_for_any_vote_exist(eosio::name member) const` {#structdecisions_1abe41b47952071a0589bf968b5f9cc6f6}





### `public inline std::pair< uint64_t, uint64_t > get_votes_count() const` {#structdecisions_1a23e686cd085c2be8cf671d55ffc8a20c}






# struct `drafts` {#structdrafts}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint64_t id` | 
`public eosio::name lang` | 
`public eosio::name action_name` | 
`public std::string name` | 
`public std::string description` | 
`public std::string context` | 
`public std::string data` | 
`public bool is_active` | 
`public bool is_approved` | 
`public bool is_standart` | 
`public eosio::time_point_sec created_at` | 
`public eosio::time_point_sec last_update` | 
`public uint64_t doc_version` | 
`public inline uint64_t primary_key() const` | 
`public inline uint64_t by_action() const` | 
`public inline uint128_t by_action_lang() const` | 

## Members

### `public uint64_t id` {#structdrafts_1ae4f6a2e4ba90a7043096bd4e794d6bf3}





### `public eosio::name lang` {#structdrafts_1a9f0325c5ceef01e0a024fb5d757fb9e5}





### `public eosio::name action_name` {#structdrafts_1a2edb5ab1ee9ecf41129e25aafab79833}





### `public std::string name` {#structdrafts_1ac5a7f4466437cdb95da8ecec0aee269a}





### `public std::string description` {#structdrafts_1a2272b3e60f6641b0d1da65099f765c25}





### `public std::string context` {#structdrafts_1aa55f776ebd674d1c19cb20e4b8643aef}





### `public std::string data` {#structdrafts_1a7b0471d233cac54714ebd5f4a2b3ff56}





### `public bool is_active` {#structdrafts_1a2635b469e8f53252badbb81c06e0edc0}





### `public bool is_approved` {#structdrafts_1a87cb78e1b3cb1e251752b42b5a3f2deb}





### `public bool is_standart` {#structdrafts_1a6654276273aa6f2624ea41188c5e7c9b}





### `public eosio::time_point_sec created_at` {#structdrafts_1ac59692d8dc164d2c514c6f2470752a38}





### `public eosio::time_point_sec last_update` {#structdrafts_1a9d670530c00e8a4e1dd824630a3be354}





### `public uint64_t doc_version` {#structdrafts_1a65adaeac3fa026ab46d407bb8a255e96}





### `public inline uint64_t primary_key() const` {#structdrafts_1a9fd3017e1f4512f4d43dcc432b761d70}





### `public inline uint64_t by_action() const` {#structdrafts_1adf0781b4b068725e00357d6ddca4da65}





### `public inline uint128_t by_action_lang() const` {#structdrafts_1a637f14ff2b136a0744523dda31611a34}






# struct `exchange` {#structexchange}


Таблица обменов для контракта "marketplace".

Эта таблица используется для хранения информации об обменных заявках в системе.


#### Parameters
* `id` Идентификатор обмена, используемый как первичный ключ 


* `parent_id` Идентификатор родительской заявки (если есть) 


* `type` Тип обмена (покупка, продажа и т.д.) 


* `status` Статус обмена (например, "опубликовано", "на модерации" и т.д.) 


* `username` Имя пользователя, создавшего заявку 


* `contract` Имя контракта токена 


* `price_for_piece` Цена за единицу товара в заявке 


* `remain_pieces` Оставшееся количество товара 


* `blocked_pieces` Заблокированное количество товара 


* `delivered_pieces` Количество доставленного товара 


* `data` Дополнительные данные, связанные с заявкой 


* `meta` Метаданные заявки





Дополнительные индексы по status, type и parent_id позволяют искать заявки по этим полям.

Пример использования: 
```cpp
[exchange_index](#common_2marketplace_8hpp_1a55235a3802ae31bc4c340a496b506d6f) [exchange](#structexchange)(_me, _me.value);
auto exchange_order = [exchange](#structexchange).find(id);
```

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint64_t id` | 
`public uint64_t parent_id` | 
`public eosio::name coop_username` | 
`public eosio::name type` | 
`public eosio::name status` | 
`public eosio::name username` | 
`public eosio::name contract` | 
`public eosio::asset price_for_piece` | 
`public uint64_t remain_pieces` | 
`public uint64_t blocked_pieces` | 
`public uint64_t delivered_pieces` | 
`public std::string data` | 
`public std::string meta` | 
`public inline uint64_t primary_key() const` | 
`public inline uint64_t by_coop() const` | 
`public inline uint64_t by_status() const` | 
`public inline uint64_t by_type() const` | 
`public inline uint64_t by_parent() const` | 

## Members

### `public uint64_t id` {#structexchange_1a8e84e7623af395f8d56d3689b997bc92}



идентификатор обмена

### `public uint64_t parent_id` {#structexchange_1a6ddc83225c4f9279f07e103d353b93e5}



идентификатор родительской заявки

### `public eosio::name coop_username` {#structexchange_1abff4e8a374497e677c49ecbddd10f2da}



имя аккаунта кооператива

### `public eosio::name type` {#structexchange_1acaa2e38908cc4759522a519ab4e5b020}



тип обмена

### `public eosio::name status` {#structexchange_1aa0662d5405ca80e5ff7ecde0f44f3245}



статус обмена

### `public eosio::name username` {#structexchange_1aeeddb9da07fc4c3abb417e4c5ce4f5d9}



имя пользователя

### `public eosio::name contract` {#structexchange_1ac91a681db1b7c3fefde2ffea19f2c36f}



имя контракта токена

### `public eosio::asset price_for_piece` {#structexchange_1aa55de52fe23c589fa161933eca54e1eb}



цена за единицу товара

### `public uint64_t remain_pieces` {#structexchange_1a5e0edd89a689c143a9b3b890808b88a6}



оставшееся количество товара

### `public uint64_t blocked_pieces` {#structexchange_1ae7df4bbffa11cd7102b591f0dff45ede}



заблокированное количество товара

### `public uint64_t delivered_pieces` {#structexchange_1a425a1dc5b79cb40849e9ff1cfe24d2d1}



количество доставленного товара

### `public std::string data` {#structexchange_1add5daca8e65c7bdfc41163844bb1d07a}



дополнительные данные

### `public std::string meta` {#structexchange_1a5febab5dc90693a173066e1c190bbb80}



метаданные заявки

### `public inline uint64_t primary_key() const` {#structexchange_1a3cd67e59b84642a2b8b834ec897967fa}



return id - primary_key

### `public inline uint64_t by_coop() const` {#structexchange_1aad91922434c8226846d393a6960a343b}



кооператив

### `public inline uint64_t by_status() const` {#structexchange_1af6641a816f36ce6af1c7c3a9e7ee78c2}



индекс по статусу

### `public inline uint64_t by_type() const` {#structexchange_1ab6ecb17793b182ce81385431fc597573}



индекс по типу

### `public inline uint64_t by_parent() const` {#structexchange_1addeb8bcc639717b6e95f9e792fd2aa0e}



индекс по родительскому ID


# struct `key_weight` {#structkey__weight}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::public_key key` | 
`public uint16_t weight` | 

## Members

### `public eosio::public_key key` {#structkey__weight_1a1c32ddbfc4c0d307c1f25503dfccd796}





### `public uint16_t weight` {#structkey__weight_1ac78b3460df5fe852385da3629d2a64e6}






# struct `limitauth_tester` {#structlimitauth__tester}

```
struct limitauth_tester
  : public eosio_system::eosio_system_tester
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline action_result push_action(name code,name action,`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` auth,const variant_object & data)` | 
`public inline action_result limitauthchg(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,const name & account,const std::vector< name > & allow_perms,const std::vector< name > & disallow_perms)` | 
`public template<typename... Ts>`  <br/>`inline action_result push_action_raw(name code,name act,`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,const Ts &... data)` | 
`public inline action_result updateauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name permission,name parent,`[`authority`](#structauthority)` auth)` | 
`public inline action_result deleteauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name permission)` | 
`public inline action_result linkauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name code,name type,name requirement)` | 
`public inline action_result unlinkauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name code,name type)` | 
`public inline action_result updateauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name permission,name parent,`[`authority`](#structauthority)` auth,name authorized_by)` | 
`public inline action_result deleteauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name permission,name authorized_by)` | 
`public inline action_result linkauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name code,name type,name requirement,name authorized_by)` | 
`public inline action_result unlinkauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name code,name type,name authorized_by)` | 

## Members

### `public inline action_result push_action(name code,name action,`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` auth,const variant_object & data)` {#structlimitauth__tester_1a9f9b15b3aef2d2f91fdd7ec62d3fb191}





### `public inline action_result limitauthchg(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,const name & account,const std::vector< name > & allow_perms,const std::vector< name > & disallow_perms)` {#structlimitauth__tester_1a57f6f3a0dd109d723b604295322e4153}





### `public template<typename... Ts>`  <br/>`inline action_result push_action_raw(name code,name act,`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,const Ts &... data)` {#structlimitauth__tester_1a3943a870f12d4b04dc52dc2ae33c3556}





### `public inline action_result updateauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name permission,name parent,`[`authority`](#structauthority)` auth)` {#structlimitauth__tester_1ac34749f47c30b019811674f343168b74}





### `public inline action_result deleteauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name permission)` {#structlimitauth__tester_1acab77918e0a1dfd7d6d56264caf48744}





### `public inline action_result linkauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name code,name type,name requirement)` {#structlimitauth__tester_1a96ab61f1706d45ca80aba62f0e3c9ed3}





### `public inline action_result unlinkauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name code,name type)` {#structlimitauth__tester_1a623c70d06ecf636b1766db2183bdcf65}





### `public inline action_result updateauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name permission,name parent,`[`authority`](#structauthority)` auth,name authorized_by)` {#structlimitauth__tester_1a578874d43b7e212b5d80475326ad1dcb}





### `public inline action_result deleteauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name permission,name authorized_by)` {#structlimitauth__tester_1a1d3d4a12de030f88f727e3b92a18ff1c}





### `public inline action_result linkauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name code,name type,name requirement,name authorized_by)` {#structlimitauth__tester_1a01f7e73d4fc080011508a350b2b3e02b}





### `public inline action_result unlinkauth(`[`permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` pl,name account,name code,name type,name authorized_by)` {#structlimitauth__tester_1a64730dbef72a36ac6059b3100d0844a1}






# struct `members` {#structmembers}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::name username` | 
`public eosio::time_point_sec created_at` | 
`public eosio::time_point_sec last_update` | 
`public eosio::time_point_sec last_min_pay` | 
`public std::string position_title` | 
`public eosio::name position` | 
`public bool is_accepted` | 
`public bool is_initial` | 
`public bool is_minimum` | 
`public bool is_voting` | 
`public inline uint64_t primary_key() const` | 
`public inline uint64_t bylastpay() const` | 

## Members

### `public eosio::name username` {#structmembers_1acd8704216796cd0c8bcf568f6c061a36}





### `public eosio::time_point_sec created_at` {#structmembers_1a0a998eeaf1a01f48301c8ab90355891f}





### `public eosio::time_point_sec last_update` {#structmembers_1a5b35eec3e9a4c95b0fa41528817913ca}





### `public eosio::time_point_sec last_min_pay` {#structmembers_1acae55fdc8bdd745b39e2ec2633f4f2a6}





### `public std::string position_title` {#structmembers_1ad6efc0ce9b6e84d34196df651a0e591a}





### `public eosio::name position` {#structmembers_1ab238fb2ca6164b2e355f341ea39b6178}





### `public bool is_accepted` {#structmembers_1af5d60936223bc846d2ec5814e6ffeff1}





### `public bool is_initial` {#structmembers_1a2f5e873854edba0bf3571dbaab59507b}





### `public bool is_minimum` {#structmembers_1aa96a971d1a0387c007951780417248be}





### `public bool is_voting` {#structmembers_1ae8725768e25ad2331e36549792566f73}





### `public inline uint64_t primary_key() const` {#structmembers_1a3c3b2e39c103c29aa2627e865dc1a6a1}



return username - primary_key

### `public inline uint64_t bylastpay() const` {#structmembers_1a5bba6bdb3df9e9c0546e9e81c1e2115d}






# struct `new_org_struct` {#structnew__org__struct}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::name username` | 
`public std::string name` | 
`public std::string short_name` | 
`public std::string address` | 
`public std::string ogrn` | 
`public std::string inn` | 
`public std::string logo` | 
`public std::string phone` | 
`public std::string email` | 
`public std::string registration` | 
`public std::string website` | 
`public std::vector< `[`bank`](#structbank)` > accounts` | 
`public bool is_cooperative` | 
`public std::optional< eosio::name > coop_type` | 
`public std::optional< eosio::name > token_contract` | 
`public std::optional< std::string > slug` | 
`public std::optional< std::string > announce` | 
`public std::optional< std::string > description` | 
`public std::optional< eosio::asset > initial` | 
`public std::optional< eosio::asset > minimum` | 
`public std::optional< eosio::asset > membership` | 
`public std::optional< eosio::name > period` | 

## Members

### `public eosio::name username` {#structnew__org__struct_1afe286ce31a0f6a948c3dfd3fa41f6868}





### `public std::string name` {#structnew__org__struct_1a142d7d656f9b6c79f484aa2c8a9cb013}





### `public std::string short_name` {#structnew__org__struct_1aab5defee125df439ce319d34df29b493}





### `public std::string address` {#structnew__org__struct_1ac697f1c505b3f86a6602afe8ee157302}





### `public std::string ogrn` {#structnew__org__struct_1a9e04e042f5a843d9956773a6d366dc4e}





### `public std::string inn` {#structnew__org__struct_1a0a19491ed30f535b8c72bf939412f37f}





### `public std::string logo` {#structnew__org__struct_1a12e61b3e7538ce17a6ed9aac35bfdd6b}





### `public std::string phone` {#structnew__org__struct_1a9cd8be190fa2b64609ac7cac26a21342}





### `public std::string email` {#structnew__org__struct_1a409085989c8b065f4c5da0aa6ddae2f4}





### `public std::string registration` {#structnew__org__struct_1ae9daef33b6eb5c7223306d0a548ab23d}





### `public std::string website` {#structnew__org__struct_1a3f8e257edac1ce91daefed2723a39a78}





### `public std::vector< `[`bank`](#structbank)` > accounts` {#structnew__org__struct_1a7de03d51e6daf27fbeb7af18ec0ba2a0}





### `public bool is_cooperative` {#structnew__org__struct_1a3edd482029472600f8110abb63f22ec0}





### `public std::optional< eosio::name > coop_type` {#structnew__org__struct_1a1b14a3b368d0465f82424936395c1d96}





### `public std::optional< eosio::name > token_contract` {#structnew__org__struct_1a52312c0249272b4eebc1257feda0b3b2}





### `public std::optional< std::string > slug` {#structnew__org__struct_1a6b41c286066648df700ccaf77c2d3163}





### `public std::optional< std::string > announce` {#structnew__org__struct_1a273ba05baf96911cc6e2170ba54d8b31}





### `public std::optional< std::string > description` {#structnew__org__struct_1ae6c0df340a6544bb31867f376d2b6e96}





### `public std::optional< eosio::asset > initial` {#structnew__org__struct_1aa523837eadf48d60a5fa372af4915249}





### `public std::optional< eosio::asset > minimum` {#structnew__org__struct_1aa74e5df96c7174dfaca6075913279605}





### `public std::optional< eosio::asset > membership` {#structnew__org__struct_1a0bd62e85c853697a7b4207648d515ae9}





### `public std::optional< eosio::name > period` {#structnew__org__struct_1a296dc59f88491363bb011f6424361e12}






# struct `orgs` {#structorgs}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::name username` | 
`public eosio::name parent_username` | 
`public `[`verification`](#structverification)` verification` | 
`public std::string name` | 
`public std::string short_name` | 
`public std::string address` | 
`public std::string ogrn` | 
`public std::string inn` | 
`public std::string logo` | 
`public std::string phone` | 
`public std::string email` | 
`public std::string registration` | 
`public std::string website` | 
`public std::vector< `[`bank`](#structbank)` > accounts` | 
`public bool is_cooperative` | 
`public std::optional< eosio::name > coop_type` | 
`public std::optional< eosio::name > token_contract` | 
`public std::optional< std::string > slug` | 
`public std::optional< std::string > announce` | 
`public std::optional< std::string > description` | 
`public std::optional< uint64_t > members_count` | 
`public std::optional< uint64_t > users_count` | 
`public std::optional< uint64_t > orgs_counts` | 
`public std::optional< eosio::asset > initial` | 
`public std::optional< eosio::asset > minimum` | 
`public std::optional< eosio::asset > membership` | 
`public std::optional< eosio::name > period` | 
`public inline uint64_t primary_key() const` | 
`public inline uint64_t by_parent() const` | 
`public inline uint128_t by_coop_childs() const` | 
`public inline uint64_t is_coop_index() const` | 
`public inline uint64_t bycooptype() const` | 
`public inline uint64_t is_verified_index() const` | 
`public inline bool is_coop() const` | 
`public inline bool is_verified() const` | 

## Members

### `public eosio::name username` {#structorgs_1a30bd763b06c88e2db7fe63b7829448c8}





### `public eosio::name parent_username` {#structorgs_1ae6431f4f421b347e828673c17c11016a}





### `public `[`verification`](#structverification)` verification` {#structorgs_1a7f2292b35d32249116fbabc45ee29f90}





### `public std::string name` {#structorgs_1ae3e89e39dc1dac2fa382f52c7dfa1499}





### `public std::string short_name` {#structorgs_1a2856436e3f095cf78cf6d6a617c79d61}





### `public std::string address` {#structorgs_1a756f0d831a24d9a4f9f52e51106f135d}





### `public std::string ogrn` {#structorgs_1a3da6502bd383a53b200b7db125575b5d}





### `public std::string inn` {#structorgs_1affc82d5743aea6b5f69b447f36537cb5}





### `public std::string logo` {#structorgs_1aa2163b8b2c75dd675de51c6e44ded60c}





### `public std::string phone` {#structorgs_1abbe8d02b45decc5efbe76645d07588b7}





### `public std::string email` {#structorgs_1a959f11805a84c42797f8acdde30adecd}





### `public std::string registration` {#structorgs_1aef9dd189590bfe100c957ce5bde967e1}





### `public std::string website` {#structorgs_1a704ac67823483cb07bb24fa5245b19aa}





### `public std::vector< `[`bank`](#structbank)` > accounts` {#structorgs_1a773b57c51cda33e3e474defc180d0e7d}





### `public bool is_cooperative` {#structorgs_1a7e106134eb289da6034239f59f8c8b00}





### `public std::optional< eosio::name > coop_type` {#structorgs_1a5d2790457eea86c9e0e0df2afacdb52e}





### `public std::optional< eosio::name > token_contract` {#structorgs_1a135a3014d3e21024a2eb16b775d46a2f}





### `public std::optional< std::string > slug` {#structorgs_1a33846e60c8725628db622e8f5a2511dc}





### `public std::optional< std::string > announce` {#structorgs_1a3f04706245d1ce159961028fe3ea8265}





### `public std::optional< std::string > description` {#structorgs_1a9fc7273b84ea89d7e3be8189bb7de823}





### `public std::optional< uint64_t > members_count` {#structorgs_1a36a73688848c389a2f2626df93ce9d0d}





### `public std::optional< uint64_t > users_count` {#structorgs_1ae939c459ab38616d44ad9544fc499512}





### `public std::optional< uint64_t > orgs_counts` {#structorgs_1ac0049e14ff707d167f0484cea9b6740c}





### `public std::optional< eosio::asset > initial` {#structorgs_1ad2dd42d38888aadcd9b212d26dfd4b8e}





### `public std::optional< eosio::asset > minimum` {#structorgs_1abdf961fb24a7135fd0a2eba44ed0d0cb}





### `public std::optional< eosio::asset > membership` {#structorgs_1a4983389f1ef9ec6b722a1471031a83c7}





### `public std::optional< eosio::name > period` {#structorgs_1a93ab1b5c27d0b55d80651a72353beec5}





### `public inline uint64_t primary_key() const` {#structorgs_1ad63f7f770daeaf11e9960f0bb3413257}





### `public inline uint64_t by_parent() const` {#structorgs_1ab88eb6ded8ef4609e0d0a013d4fcd19f}





### `public inline uint128_t by_coop_childs() const` {#structorgs_1aaf7a07b7ede42be8755e8dab89b68273}





### `public inline uint64_t is_coop_index() const` {#structorgs_1a62e31444747797512f25c736d36e8ad3}





### `public inline uint64_t bycooptype() const` {#structorgs_1a9c08ac2829263b63bcf3cb773855691a}





### `public inline uint64_t is_verified_index() const` {#structorgs_1ab93e3b210063838c61fdc01849e93124}





### `public inline bool is_coop() const` {#structorgs_1a56f3d02c014cc9448b0dc2e771c99f10}





### `public inline bool is_verified() const` {#structorgs_1a153188e5dd5b21d491fd733feb6e8ff5}






# struct `permission_level_weight` {#structpermission__level__weight}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`eosio::permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` permission` | 
`public uint16_t weight` | 

## Members

### `public `[`eosio::permission_level`](#eosio_8msig__tests_8cpp_1adb5a7af6f4a8319d70ccf6363031f4dc)` permission` {#structpermission__level__weight_1a8e66350534de3fc26309013f5ade74b8}





### `public uint16_t weight` {#structpermission__level__weight_1a8a90481461f59afdd92875d0caa6959f}






# struct `powerup_config_resource` {#structpowerup__config__resource}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::optional< int64_t > current_weight_ratio` | 
`public std::optional< int64_t > target_weight_ratio` | 
`public std::optional< int64_t > assumed_stake_weight` | 
`public std::optional< time_point_sec > target_timestamp` | 
`public std::optional< double > exponent` | 
`public std::optional< uint32_t > decay_secs` | 
`public std::optional< asset > min_price` | 
`public std::optional< asset > max_price` | 

## Members

### `public std::optional< int64_t > current_weight_ratio` {#structpowerup__config__resource_1a3b0a2733b02834af5fe7332032a1a799}





### `public std::optional< int64_t > target_weight_ratio` {#structpowerup__config__resource_1a4ad04a2a051c39d150502cbb3067ecb7}





### `public std::optional< int64_t > assumed_stake_weight` {#structpowerup__config__resource_1a8381fd20dcaf1ca9e278080886a406c7}





### `public std::optional< time_point_sec > target_timestamp` {#structpowerup__config__resource_1a67e6b4587c647502c37535f2b91cf744}





### `public std::optional< double > exponent` {#structpowerup__config__resource_1ad5d3c64bc34f81425b635c8883f17b9b}





### `public std::optional< uint32_t > decay_secs` {#structpowerup__config__resource_1af07fa74064c8e58ca0c0da4972aebce1}





### `public std::optional< asset > min_price` {#structpowerup__config__resource_1abc3aec7fb0b1d9ad24e3e5d0f4cb9430}





### `public std::optional< asset > max_price` {#structpowerup__config__resource_1aef7aad68a4cf14bb529951e05185f2ab}






# struct `right` {#structright}


Таблица администраторов для контракта "soviet".

Эта таблица используется для хранения информации об администраторах и их правах в системе.


#### Parameters
* `username` Имя администратора, используемое как первичный ключ 


* `rights` Вектор прав, которыми обладает администратор 


* `meta` Дополнительная метаинформация, связанная с администратором





Пример использования: 
```cpp
admins_index admins(_me, _me.value);
auto [admin](#eosio_8limitauth__tests_8cpp_1a9ce601efdf60929be15c98a3f8ae514a) = admins.find(username.value);
```

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::name contract` | 
`public eosio::name action_name` | 

## Members

### `public eosio::name contract` {#structright_1a72bb88ed7a935b2652edd7c01ed9cbfb}





### `public eosio::name action_name` {#structright_1a7b8447f641a5a31a5c77b23ab3d97dd3}






# struct `staff` {#structstaff}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::name username` | Уникальное имя администратора
`public std::string position_title` | 
`public std::vector< `[`right`](#structright)` > rights` | Список прав администратора
`public eosio::time_point_sec created_at` | 
`public eosio::time_point_sec updated_at` | 
`public inline uint64_t primary_key() const` | Первичный ключ для индексации по имени администратора
`public inline bool has_right(eosio::name contract,eosio::name action_name) const` | 

## Members

### `public eosio::name username` {#structstaff_1aa67b206d474a4f87453bca87fda2f01b}

Уникальное имя администратора



### `public std::string position_title` {#structstaff_1a8fa0fdaf003c7588f9f1185a087785ba}





### `public std::vector< `[`right`](#structright)` > rights` {#structstaff_1a935eee764193e5796da146fedfc465e5}

Список прав администратора



### `public eosio::time_point_sec created_at` {#structstaff_1ab46bbfc312f86ec081fead61e3d01a10}





### `public eosio::time_point_sec updated_at` {#structstaff_1a2079dc310b3faf4112d9046e54a72ab7}





### `public inline uint64_t primary_key() const` {#structstaff_1a907194daa8db9aee9629350891757d22}

Первичный ключ для индексации по имени администратора



### `public inline bool has_right(eosio::name contract,eosio::name action_name) const` {#structstaff_1a72d9d9dac115d8379e3afa76ff712c98}






# struct `users` {#structusers}


Таблица хранения объектов гостей

@table individuals @contract _me @scope _me.



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::name username` | 
`public std::string profile_hash` | 
`public `[`verification`](#structverification)` verification` | 
`public inline uint64_t primary_key() const` | 
`public inline uint64_t by_verified() const` | 

## Members

### `public eosio::name username` {#structusers_1a737eae3ed6e76f98919b26b20288164b}



имя аккаунта

### `public std::string profile_hash` {#structusers_1ae07b933da6c46eb7dfe70f5c95ade143}





### `public `[`verification`](#structverification)` verification` {#structusers_1ac39df2d81bcbcf04648eab679a910044}





### `public inline uint64_t primary_key() const` {#structusers_1a6894c358dbcce05a63de742f2b5fbd8e}



return username - primary_key

### `public inline uint64_t by_verified() const` {#structusers_1a0aef32204b2b1f86902c63150d4f230c}






# struct `verification` {#structverification}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public eosio::name verificator` | 
`public bool is_verified` | 
`public uint64_t procedure` | 
`public eosio::time_point_sec created_at` | 
`public eosio::time_point_sec last_update` | 
`public std::string notice` | 

## Members

### `public eosio::name verificator` {#structverification_1a7fb3c0fd447a28ad0919859e3ccb5aa7}





### `public bool is_verified` {#structverification_1aeb6702bd4b7903963252735d6f760c50}





### `public uint64_t procedure` {#structverification_1a70dd1f70e9c4cd9683dfd0c7203051b5}





### `public eosio::time_point_sec created_at` {#structverification_1aa7d19ca745ac2729d841ff65548622e6}





### `public eosio::time_point_sec last_update` {#structverification_1a674206f7442d3ba3319ce4b22d542b04}





### `public std::string notice` {#structverification_1a231be135ab1c6c218ca0ed86383d043c}






# struct `wait_weight` {#structwait__weight}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint32_t wait_sec` | 
`public uint16_t weight` | 

## Members

### `public uint32_t wait_sec` {#structwait__weight_1a3286af83356d29e62a35ccb650d92c98}





### `public uint16_t weight` {#structwait__weight_1a41ebcf1f6076155456429094e7db0d2f}






