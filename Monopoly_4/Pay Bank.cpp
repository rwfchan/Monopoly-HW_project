//
// Created by Raymond Chan on 3/1/18.
//

#include "Pay Bank.h"

Monopoly::Pay_Bank::Pay_Bank(CSVReader &boardFile, const int spaceNumber, GameState& gameState)
    : Space(spaceNumber), gameState(gameState) {
  name = boardFile.get_next_field();
  pay_amount = boardFile.get_next_field_as_int();
}

void Monopoly::Pay_Bank::display() const {
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

void Monopoly::Pay_Bank::Pay_To_Bank(Player &activatingPlayer) {
  unsigned long sell_num;

  std::vector<Property*> downgradeableProperties = activatingPlayer.getDowngradeableProperties(gameState.getrule());
  while(activatingPlayer.getCash() < pay_amount && downgradeableProperties.size() > 0){

    //FIXME print out the Message for selling property
    std::cout << "You have $" << activatingPlayer.getCash() << " but you owe $" << pay_amount << std::endl;
    std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;
    for (unsigned long i = 0; i < downgradeableProperties.size(); ++i) {
      std::cout << i << ". " << downgradeableProperties.at(i)->getName() << " [$"
                << downgradeableProperties.at(i)->getUpgradeCost()  / 2<< "]" << std::endl;
    }
    std::cout << "Your choice: ";
    std::cin >> sell_num;
    downgradeableProperties.at(sell_num)->downgrade();
    downgradeableProperties = activatingPlayer.getDowngradeableProperties(gameState.getrule());
  }
}

void Monopoly::Pay_Bank::activate(Player &activatingPlayer) {

  //If Free Parking is active, add money into Free Parking
  if(gameState.getrule().isPut_money_in_free_parking()) {
    gameState.addfree_parking_money(pay_amount);
  }

  //Check if the Player have enough to pay the bank
  //If they doesn't, sell their upgrade until they have enough
  Pay_To_Bank(activatingPlayer);

  //If they got out of the loop and still have no money, remove them from game
  if(activatingPlayer.getCash() < pay_amount) {
    std::cout << activatingPlayer.getName() << " went bankrupt by landing on " << getName();

    gameState.removeFromGame(activatingPlayer);
  } else { //Else, take money away from player
    std::cout << activatingPlayer.getName() << " paid the bank $" << pay_amount << " for landing on " << getName();
    activatingPlayer.setCash(activatingPlayer.getCash() - pay_amount);
  }
}

const std::string& Monopoly::Pay_Bank::getName() const {
  return name;
}
int Monopoly::Pay_Bank::getpay_amount() const {
  return pay_amount;
}

int Monopoly::Pay_Bank::getSalary() const {
  return 99999;
}
int Monopoly::Pay_Bank::getCost() const {
  return 99999;
}
int Monopoly::Pay_Bank::getSetId() const {
  return 99999;
}
int Monopoly::Pay_Bank::getIntraSetId() const {
  return 99999;
}
int Monopoly::Pay_Bank::getBasicRent() const {
  return 99999;
}
int Monopoly::Pay_Bank::getFree_Parking_money() const {
  return 99999;
}
int Monopoly::Pay_Bank::getJail_Fine() const {
  return 99999;
}
int Monopoly::Pay_Bank::getJail_turn() const {
  return 99999;
}
int Monopoly::Pay_Bank::getsent_to() const {
  return 99999;
}


