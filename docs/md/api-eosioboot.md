# group `eosioboot` {#group__eosioboot}

eosio.boot is a extremely minimalistic system contract that only supports the native actions and an activate action that allows activating desired protocol features prior to deploying a system contract with more features such as eosio.bios or eosio.system.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`eosioboot::boot`](#classeosioboot_1_1boot) | 

# class `eosioboot::boot` {#classeosioboot_1_1boot}

```
class eosioboot::boot
  : public eosio::contract
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`onerror`](#classeosioboot_1_1boot_1a91777be02b457df0533db35776387b13)`(ignore< uint128_t > sender_id,ignore< std::vector< char > > sent_trx)` | On error action.
`public void `[`activate`](#classeosioboot_1_1boot_1a8159d04a7a5ca851a1c654594bafba5e)`(const eosio::checksum256 & feature_digest)` | Activates a protocol feature.
`public void `[`reqactivated`](#classeosioboot_1_1boot_1a470f541c80fa910ded5dd8c6ab2f2a18)`(const eosio::checksum256 & feature_digest)` | Asserts that a protocol feature has been activated.
`typedef `[`newaccount_action`](#classeosioboot_1_1boot_1a0ba8ab7685d8e217a383f151c7aaee79) | 
`typedef `[`updateauth_action`](#classeosioboot_1_1boot_1a6d9f1be43138a0ea7e5bdfc568250a82) | 
`typedef `[`deleteauth_action`](#classeosioboot_1_1boot_1a2e9f73ce19159c557d213f27c0e3e43d) | 
`typedef `[`linkauth_action`](#classeosioboot_1_1boot_1a59658ecc01553c951f8d8126c0ec2b7d) | 
`typedef `[`unlinkauth_action`](#classeosioboot_1_1boot_1a542952b4056a0870784df9351afe0e14) | 
`typedef `[`canceldelay_action`](#classeosioboot_1_1boot_1a429ac92bc85444c33f5bbb5045685120) | 
`typedef `[`setcode_action`](#classeosioboot_1_1boot_1a2d0969b28894f32d4ab5e082ffb479ed) | 
`typedef `[`setabi_action`](#classeosioboot_1_1boot_1af978a97907d8980d80a6db9a43de8790) | 
`typedef `[`activate_action`](#classeosioboot_1_1boot_1a4202cf8724db3152de3588aa2834912c) | 
`typedef `[`reqactivated_action`](#classeosioboot_1_1boot_1a5a7f8926f3b21fa1588c86472368903e) | 

## Members

#### `public void `[`onerror`](#classeosioboot_1_1boot_1a91777be02b457df0533db35776387b13)`(ignore< uint128_t > sender_id,ignore< std::vector< char > > sent_trx)` {#classeosioboot_1_1boot_1a91777be02b457df0533db35776387b13}

On error action.

Notification of this action is delivered to the sender of a deferred transaction when an objective error occurs while executing the deferred transaction. This action is not meant to be called directly.

#### Parameters
* `sender_id` - the id for the deferred transaction chosen by the sender, 

* `sent_trx` - the deferred transaction that failed.

#### `public void `[`activate`](#classeosioboot_1_1boot_1a8159d04a7a5ca851a1c654594bafba5e)`(const eosio::checksum256 & feature_digest)` {#classeosioboot_1_1boot_1a8159d04a7a5ca851a1c654594bafba5e}

Activates a protocol feature.

Activates a protocol feature

#### Parameters
* `feature_digest` - hash of the protocol feature to activate.

#### `public void `[`reqactivated`](#classeosioboot_1_1boot_1a470f541c80fa910ded5dd8c6ab2f2a18)`(const eosio::checksum256 & feature_digest)` {#classeosioboot_1_1boot_1a470f541c80fa910ded5dd8c6ab2f2a18}

Asserts that a protocol feature has been activated.

Asserts that a protocol feature has been activated

#### Parameters
* `feature_digest` - hash of the protocol feature to check for activation.

#### `typedef `[`newaccount_action`](#classeosioboot_1_1boot_1a0ba8ab7685d8e217a383f151c7aaee79) {#classeosioboot_1_1boot_1a0ba8ab7685d8e217a383f151c7aaee79}

#### `typedef `[`updateauth_action`](#classeosioboot_1_1boot_1a6d9f1be43138a0ea7e5bdfc568250a82) {#classeosioboot_1_1boot_1a6d9f1be43138a0ea7e5bdfc568250a82}

#### `typedef `[`deleteauth_action`](#classeosioboot_1_1boot_1a2e9f73ce19159c557d213f27c0e3e43d) {#classeosioboot_1_1boot_1a2e9f73ce19159c557d213f27c0e3e43d}

#### `typedef `[`linkauth_action`](#classeosioboot_1_1boot_1a59658ecc01553c951f8d8126c0ec2b7d) {#classeosioboot_1_1boot_1a59658ecc01553c951f8d8126c0ec2b7d}

#### `typedef `[`unlinkauth_action`](#classeosioboot_1_1boot_1a542952b4056a0870784df9351afe0e14) {#classeosioboot_1_1boot_1a542952b4056a0870784df9351afe0e14}

#### `typedef `[`canceldelay_action`](#classeosioboot_1_1boot_1a429ac92bc85444c33f5bbb5045685120) {#classeosioboot_1_1boot_1a429ac92bc85444c33f5bbb5045685120}

#### `typedef `[`setcode_action`](#classeosioboot_1_1boot_1a2d0969b28894f32d4ab5e082ffb479ed) {#classeosioboot_1_1boot_1a2d0969b28894f32d4ab5e082ffb479ed}

#### `typedef `[`setabi_action`](#classeosioboot_1_1boot_1af978a97907d8980d80a6db9a43de8790) {#classeosioboot_1_1boot_1af978a97907d8980d80a6db9a43de8790}

#### `typedef `[`activate_action`](#classeosioboot_1_1boot_1a4202cf8724db3152de3588aa2834912c) {#classeosioboot_1_1boot_1a4202cf8724db3152de3588aa2834912c}

#### `typedef `[`reqactivated_action`](#classeosioboot_1_1boot_1a5a7f8926f3b21fa1588c86472368903e) {#classeosioboot_1_1boot_1a5a7f8926f3b21fa1588c86472368903e}

