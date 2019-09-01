//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_GAMESTATE_H
#define HOARDINGCPPVERSION_GAMESTATE_H
#include <vector>
#include <string>
#include <fstream>
#include <memory>

#include "Player.h"
#include "DiceRoller.h"
#include "Board.h"

namespace Monopoly {
  class Free_Parking;

  class GameState {
    friend Space;
    friend Board;
   public:
    static std::vector<std::string> get_player_names();
    GameState(const std::string& RulesFileName,
              const std::string& BoardFileName,
              const std::string& RandomFileName,
              const std::vector<std::string>& playerNames);

    void playGame();
    bool isGameOver() const;
    Player& getCurrentPlayer();
    void make_move(Player& player, Move& move);
    void declareWinner();
    void changeTurn();
    void removeFromGame(Player& player);
    void auction(Property& property);

    void display() const;

    Rules getrule() const;
    int getfree_parking_money() const;
    void addfree_parking_money(int amount);
    void resetfree_parking_money();

   private:
    void buyUpgrade();
    void sellUpgrade();
    void rollDice(Monopoly::Player& player);

    Rules rules;
    Board board;
    DiceRoller diceRoller;

    int free_parking_money;
    int turn_count;
    unsigned long player_turn;
    std::vector<std::unique_ptr<Player>> players;
  };
}

#endif //HOARDINGCPPVERSION_GAMESTATE_H
