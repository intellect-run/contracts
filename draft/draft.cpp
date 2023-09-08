#include "draft.hpp"
#include <ctime>
#include <eosio/transaction.hpp>
using namespace eosio;

void draft::newid(uint64_t id) { require_auth(_draft); };


void draft::create(eosio::name lang, eosio::name action_name, std::string name,
                   std::string description, std::string context,
                   std::string data) {

  require_auth(_ano);

  drafts_index drafts(_draft, _draft.value);

  eosio::check(action_name == "regaccount"_n, "not supported action");

  uint64_t draft_id = get_global_id(_draft, "draft"_n);

  drafts.emplace(_draft, [&](auto &d) {
    d.id = draft_id;
    d.lang = lang;
    d.action_name = action_name;
    d.name = name;
    d.description = description;
    d.context = context;
    d.data = data;
    d.is_active = false;
    d.is_approved = false;
    d.is_standart = false;
    d.created_at = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
    d.last_update = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
    d.doc_version = 1;
  });

  action(permission_level{_draft, "active"_n}, _draft, "newid"_n,
         std::make_tuple(draft_id))
      .send();
};

void draft::publish(uint64_t draft_id) {
  require_auth(_ano);

  drafts_index drafts(_draft, _draft.value);

  auto draft = drafts.find(draft_id);

  eosio::check(draft != drafts.end(), "Шаблон не найден");

  drafts.modify(draft, _ano, [&](auto &d) {
    d.is_active = true;
    d.last_update = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());
  });
};

void draft::use(uint64_t coop_id, uint64_t draft_id){

};

void draft::replace(){

};

void draft::del (){

};

void draft::edit(){

};

extern "C" {

/// The apply method implements the dispatch of events to this contract
void apply(uint64_t receiver, uint64_t code, uint64_t action) {
  if (code == _draft.value) {
    switch (action) { EOSIO_DISPATCH_HELPER(draft, (create)) }
  } else {
    if (action == "transfer"_n.value) {
      struct transfer {
        eosio::name from;
        eosio::name to;
        eosio::asset quantity;
        std::string memo;
      };

      auto op = eosio::unpack_action_data<transfer>();

      if (op.to == _draft) {
        // вызов функции-обработчика пополнения баланса
        // draft::add_balance(op.from, op.quantity, name(code));
      }
    }
  }
};
};
