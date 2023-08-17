#include "bet.hpp"
#include <ctime>
#include <eosio/transaction.hpp>
using namespace eosio;


void bet::creategame(uint64_t id, std::string caption) {
  require_auth(_me);

  games_index games(_me, _me.value);
  auto game = games.find(id);

  eosio::check(game == games.end(), "Игра уже существует с этим идентификатором");

  games.emplace(_me, [&](auto &g) {
    g.id = id;
    g.caption = caption;
    g.contract = _root_contract;
    g.prize_fund = asset(0, _root_symbol);
    g.reserve_fund = asset(0, _root_symbol);
  });
};

void bet::makebet(eosio::name username, uint64_t game_id,
              std::string encrypted_data, std::string hash_for_check,
              eosio::asset amount, eosio::time_point timepoint) {

  require_auth(username);

  bets_index bets(_me, _me.value);
  auto bets_by_timepoint = bets.template get_index<"bytimepoint"_n>();
  
  eosio::check(current_time_point().time_since_epoch().count() < timepoint.time_since_epoch().count(), "Принимаются только ставки на будущее");
  auto exist = bets_by_timepoint.find(timepoint.time_since_epoch().count());

  eosio::check(exist == bets_by_timepoint.end(),
               "Извините, ставка на указанный вами момент времени уже "
               "существует. Попробуйте еще раз;");

  games_index games(_me, _me.value);
  auto game = games.find(game_id);
  eosio::check(game != games.end(), "Игра не найдена");

  sub_balance(username, amount, game->contract);
  uint64_t bet_id = bet::get_global_id("bet"_n);

  bets.emplace(username, [&](auto &b) {
    b.id = bet_id;
    b.game_id = game_id;
    b.username = username;
    b.timepoint = timepoint;
    b.amount = amount;
  });

  games.modify(game, username, [&](auto &g){
    g.reserve_fund += amount;
  });

  action(permission_level{_me, "active"_n}, _me, "newid"_n,
         std::make_tuple(bet_id))
  .send();

}

void bet::addhypo(uint64_t game_id, uint64_t hypo_id, std::string title) {
  require_auth(_me);

  games_index games(_me, _me.value);
  auto game = games.find(game_id);

  eosio::check(game != games.end(), "Игра не найдена");

  hypo_index hypos(_me, _me.value);
  auto hypo = hypos.find(hypo_id);
  
  eosio::check(hypo == hypos.end(), "Гипотеза уже существует");

  hypos.emplace(_me, [&](auto &h) {
    h.id = hypo_id;
    h.title = title;
    h.game_id = game_id;
  });

};


void bet::pushfeed(uint64_t game_id, uint64_t win_hypo_id) {
  require_auth(_me);

  feed_index feed(_me, _me.value);
  hypo_index hypos(_me, _me.value);
  games_index games(_me, _me.value);

  auto game = games.find(game_id);
  eosio::check(game != games.end(), "Игра не найдена");

  auto hypo = hypos.find(win_hypo_id);
  eosio::check(hypo != hypos.end(), "Гипотеза не найдена");
  uint64_t feed_id = bet::get_global_id("feed"_n);

  feed.emplace(_me, [&](auto &f) {
    f.id = feed_id;
    f.prev_feed_id = game -> current_feed_id;
    f.game_id = game_id;
    f.win_hypothesis_id = win_hypo_id;
    f.timepoint = current_time_point();
  });

  games.modify(game, _me, [&](auto &g) {
    g.current_feed_id = feed_id;
  });

};

void bet::notify(uint64_t bet_id, eosio::name status, eosio::asset amount){};
void bet::newid(uint64_t id){};

void bet::back(uint64_t game_id, eosio::name username, uint64_t bet_id, eosio::asset amount) {
  games_index games(_me, _me.value);
  auto game = games.find(game_id);
  eosio::check(game != games.end(), "Игра не найдена");
  
  games.modify(game, _me, [&](auto &g) {
      g.reserve_fund -= amount;
  });

  action(permission_level{_me, "active"_n}, game->contract, "transfer"_n,
         std::make_tuple(_me, username, amount,
                         std::string("Возврат ставки: ") + std::to_string(bet_id)))
  .send();

  
  action(permission_level{_me, "active"_n}, _me, "notify"_n,
         std::make_tuple(bet_id, "back"_n, amount))
  .send();
};


void bet::win(uint64_t game_id, eosio::name username, uint64_t bet_id, eosio::asset amount) {
  games_index games(_me, _me.value);
  auto game = games.find(game_id);
  eosio::check(game != games.end(), "Игра не найдена");
  
  eosio::asset win_amount = amount + game->prize_fund;

  games.modify(game, _me, [&](auto &g) {
    g.reserve_fund -= amount;
    g.prize_fund = asset(0, _root_symbol);
  });

  action(permission_level{_me, "active"_n}, game->contract, "transfer"_n,
         std::make_tuple(_me, username, win_amount,
                         std::string("Выигрыш по ставке: ") + std::to_string(bet_id)))
  .send();

  action(permission_level{_me, "active"_n}, _me, "notify"_n,
         std::make_tuple(bet_id, "win"_n, win_amount))
  .send();
};


void bet::lose(uint64_t game_id, eosio::name username, uint64_t bet_id, eosio::asset amount) {
  games_index games(_me, _me.value);
  auto game = games.find(game_id);
  eosio::check(game != games.end(), "Игра не найдена");

  games.modify(game, _me, [&](auto &g) { g.prize_fund += amount; });


  action(permission_level{_me, "active"_n}, _me, "notify"_n,
         std::make_tuple(bet_id, "lose"_n, asset(0, _root_symbol)))
  .send();
};



void bet::settle(uint64_t bet_id, uint64_t hypo_id,
                std::string decrypted_data) {
  require_auth(_me);
  
  bets_index bets(_me, _me.value);
  auto bet = bets.find(bet_id);

  eosio::check(bet != bets.end(), "Ставка не найдена");
  
  //проверяем ставку на первоочередность
  auto bets_by_game = bets.template get_index<"bygame"_n>();
  auto first_bet = bets_by_game.lower_bound(bet -> game_id);

  eosio::check(bet -> id == first_bet -> id, "Ставки могут закрываться только в порядке их экспирации. Это не крайняя ставка сейчас");

  eosio::check(bet -> timepoint.time_since_epoch().count() <= current_time_point().time_since_epoch().count(), "Время экспирации ставки еще не наступило");

  hypo_index hypos(_me, _me.value);
  auto hypo = hypos.find(hypo_id);
  
  if (hypo == hypos.end()){
    //гипотеза не найдена, делаем возврат ставки (ошибка оператора)
    bet::back(bet -> game_id, bet->username, bet -> id, bet -> amount);
    bets.erase(bet);
    return;
  } 
 

  feed_index feed(_me, _me.value);
  auto feed_by_timepoint = feed.template get_index<"bygamemtime"_n>();
  uint128_t search_key = combine_ids(bet -> game_id, bet -> timepoint.time_since_epoch().count());

  auto next = feed_by_timepoint.lower_bound(search_key);
  eosio::name status = ""_n;

  print(" bet timepoint: ", bet -> timepoint.time_since_epoch().count());
  print(" next_timepoint: ", next -> timepoint.time_since_epoch().count());
  print(" bet > feed: ", bet -> timepoint.time_since_epoch().count() > next -> timepoint.time_since_epoch().count());
  
  print(" next feed id: ", next -> id, " game_id: ", next -> game_id);
  

  if (next != feed_by_timepoint.begin()) {
    auto prev = next;
    --prev;

    print(" pref feed id: ", prev -> id);
  
    // Проверяем, что предыдущий фид все еще соответствует game_id
    if (prev->game_id == bet->game_id) {
      status = prev->win_hypothesis_id == hypo_id ? "win"_n : "lose"_n;
    } else {
      print("Крайний фид: ", next->id, " Предыдущий: ", prev->id);
      status = "back"_n;
      // ставка была сделана до первого фида?
    }
  } else {
    // обработайте ситуацию, когда нет ни одного фида, который меньше заданного времени
    print("Нет фидов меньше заданного времени");
    print("Крайний фид: ", next->id);
    status = "back"_n;
      
  }

  
  eosio::asset win_amount = asset(0, _root_symbol);

  if (status == "back"_n) {

    bet::back(bet -> game_id, bet->username, bet -> id, bet -> amount);

  } else if (status == "win"_n) {

    bet::win(bet -> game_id, bet->username, bet -> id, bet -> amount);

  } else {

    bet::lose(bet -> game_id, bet->username, bet -> id, bet -> amount);
    
  }

  bets.erase(bet);

}

extern "C" {

/// The apply method implements the dispatch of events to this contract
void apply(uint64_t receiver, uint64_t code, uint64_t action) {
  if (code == _me.value) {
    switch (action) {
      EOSIO_DISPATCH_HELPER(
          bet, (makebet)(settle)(pushfeed)(creategame)(addhypo)
          //service actions
            (notify)(newid)
          )
    }
  } else {
    if (action == "transfer"_n.value) {
      struct transfer {
        eosio::name from;
        eosio::name to;
        eosio::asset quantity;
        std::string memo;
      };

      auto op = eosio::unpack_action_data<transfer>();

      if (op.to == _me) {
        bet::add_balance(op.from, op.quantity, name(code));
      }
    }
  }
};
};
