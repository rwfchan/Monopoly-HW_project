//
// Created by Raymond Chan on 3/1/18.
//

#include "Free Parking.h"

Monopoly::Free_Parking::Free_Parking(CSVReader &boardFile, const int spaceNumber, GameState& gameState)
    : Space(spaceNumber), Free_Parking_money(gameState.getfree_parking_money()), gameState(gameState){
  name = boardFile.get_next_field();
}

void Monopoly::Free_Parking::display() const {
  const auto frmt_flags = std::cout.flags();

  //display space name
  std::cout.width(length_of_longest_space_name);
  std::cout << getName() << " | ";

  //display owner
  std::cout.width(Monopoly::Player::length_of_longest_player_name);

  const std::string temp = "None";
  std::cout << temp << " | ";
  std::cout << "         | ";

  std::cout.flags(frmt_flags);

  //Print out who's on this space
  auto player = playersOnSpace.cbegin();

  //Loop through all the players who are on this space
  for (; player != playersOnSpace.cend(); ++player) {

    //If the next player is the last player on this space, break;
    if (player + 1 == playersOnSpace.cend()) {
      break;
    }

    //Display player's name in certain format
    (*player)->display();
    std::cout << ", ";

  }

  //Print out the last player
  if (player != playersOnSpace.cend()) {
    (*player)->display();
  }
}

void Monopoly::Free_Parking::activate(Player &activatingPlayer) {
  if(gameState.getrule().isPut_money_in_free_parking() && gameState.getfree_parking_money() > 0) {
    std::cout << activatingPlayer.getName() << " got $" << gameState.getfree_parking_money() << " for landing on " << getName() << std::endl;
    activatingPlayer.giveCash(gameState.getfree_parking_money());
    gameState.resetfree_parking_money();
  }
}
void Monopoly::Free_Parking::add_Free_Parking_money(int add_amount) {
  gameState.addfree_parking_money(gameState.getfree_parking_money() + add_amount);
}

const std::string& Monopoly::Free_Parking::getName() const {
  return name;
}
int Monopoly::Free_Parking::getFree_Parking_money() const {
  return gameState.getfree_parking_money();
}
int Monopoly::Free_Parking::getSalary() const {
  return 99999;
}
int Monopoly::Free_Parking::getCost() const {
  return 99999;
}
int Monopoly::Free_Parking::getSetId() const {
  return 99999;
}
int Monopoly::Free_Parking::getIntraSetId() const {
  return 99999;
}
int Monopoly::Free_Parking::getBasicRent() const {
  return 99999;
}
int Monopoly::Free_Parking::getpay_amount() const {
  return 99999;
}
int Monopoly::Free_Parking::getJail_Fine() const {
  return 99999;
}
int Monopoly::Free_Parking::getJail_turn() const {
  return 99999;
}
int Monopoly::Free_Parking::getsent_to() const {
  return 99999;
}

