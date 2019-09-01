//
// Created by Raymond Chan on 3/1/18.
//

#include "GameState.h"
#include "Jail.h"

Monopoly::Jail::Jail(CSVReader &boardFile, const int spaceNumber, GameState& gameState)
    : Space(spaceNumber), Jail_Fine(0), Jail_turn(1), Sent_From_Jail(false), gameState(gameState){
  name = boardFile.get_next_field();
  Jail_turn = boardFile.get_next_field_as_int();
  Jail_Fine = boardFile.get_next_field_as_int();
}

void Monopoly::Jail::display() const {
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

void Monopoly::Jail::activate(Player &activatingPlayer) {
  if(!Sent_From_Jail) {
    return;
  } else {
    activatingPlayer.setRemaining_sentence(Jail_turn);
    activatingPlayer.setJail_fine(Jail_Fine);
    activatingPlayer.setJail_Cell(spaceNumber);
    std::cout << activatingPlayer.getName() << ", you were sent to " << getName() << " for " << getJail_turn() << " turns" << std::endl;

    filpSent_From_Jail();
  }
}
void Monopoly::Jail::Pay_for_jail(Player &immate) {
  unsigned long sell_num;

  std::vector<Property*> downgradeableProperties = immate.getDowngradeableProperties(gameState.getrule());
  while(immate.getCash() < Jail_Fine && downgradeableProperties.size() > 0){

    //FIXME print out the Message for selling property
    std::cout << "You have $" << immate.getCash() << " but you owe $" << Jail_Fine << std::endl;
    std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;
    for (unsigned long i = 0; i < downgradeableProperties.size(); ++i) {
      std::cout << i << ". " << downgradeableProperties.at(i)->getName() << " [$"
                << downgradeableProperties.at(i)->getUpgradeCost()  / 2<< "]" << std::endl;
    }
    std::cout << "Your choice: ";
    std::cin >> sell_num;
    downgradeableProperties.at(sell_num)->downgrade();
    downgradeableProperties = immate.getDowngradeableProperties(gameState.getrule());
  }

}

//This is to ask if the player want to pay jil_fine at the beginning of their turn
//This is also where player were forced to pay the fine
void Monopoly::Jail::Player_Move_in_jail(Player &immate) {

  //If the player is serving jail sentence
  //Ask them if they want to pay the fine
  if(immate.getJail_sentence() > 0) {

    std::cout << immate.getName() << " you are in jail for " << immate.getJail_sentence() << " turns." << std::endl;

    //Ask the player to pay if they have enough to pay
    //This one do not need else statement since we only need to do something if player have money
    if(immate.getCash() > Jail_Fine) {
      std::cout << "Would you like to pay $" << Jail_Fine << " to leave jail early?" << std::endl;
      std::cout << "y for yes and n for no: " << std::endl;

      char player_input;
      std::cin >> player_input;
      //If the player pay the fine, bank or free parking takes the money
      //Then set the player's sentence to 0
      //Everything will now run like normal
      if (player_input == 'y') {
        immate.setRemaining_sentence(-1);
        immate.setCash(immate.getCash() - Jail_Fine);

        //Put money in free parking if active
        if(gameState.getrule().isPut_money_in_free_parking()) {
          gameState.addfree_parking_money(Jail_Fine);
        }
      } else if (player_input == 'n') {
        //We don't need to do anything if the player answer no
      } else {
        //Error checking line
        std::cout << "Something's wrong on Jail asking line" << std::endl;
      }
    }

    //Else if player's serving jail sentence is up
    //Force the player to pay for jail fine
    //If the player don't have enough to pay, force them to sell upgrade
  } else if(immate.getJail_sentence() == 0) {

    //Make player sell upgrade if they don't have enough money
    Pay_for_jail(immate);

    //Force player to pay if they have enough money
    //If they have money after the loop, then they have money to pay
    //After they pay, set remaining sentence to -1
    if(immate.getCash() >= Jail_Fine) {
      std::cout << immate.getName() << ", you had to pay $" << Jail_Fine << " to get out of jail" << std::endl;
      immate.setCash(immate.getCash() - Jail_Fine);
      if(gameState.getrule().isPut_money_in_free_parking()) {
        gameState.addfree_parking_money(Jail_Fine);
      }
      immate.setRemaining_sentence(-1);
    } else {
      //If they got out of the loop and still have no money, remove player
      std::cout << immate.getName() << "went bankrupt when paying to leave jail" << std::endl;
      immate.setJail_rupted(true);
    }
  }
}

const std::string& Monopoly::Jail::getName() const {
  return name;
}
int Monopoly::Jail::getJail_Fine() const {
  return Jail_Fine;
}
int Monopoly::Jail::getJail_turn() const {
  return Jail_turn;
}
bool Monopoly::Jail::getSent_From_Jail() const{
  return Sent_From_Jail;
}
void Monopoly::Jail::filpSent_From_Jail() {
  this->Sent_From_Jail = !Sent_From_Jail;
}

int Monopoly::Jail::getFree_Parking_money() const {
  return 99999;
}
int Monopoly::Jail::getSalary() const {
  return 99999;
}
int Monopoly::Jail::getCost() const {
  return 99999;
}
int Monopoly::Jail::getSetId() const {
  return 99999;
}
int Monopoly::Jail::getIntraSetId() const {
  return 99999;
}
int Monopoly::Jail::getBasicRent() const {
  return 99999;
}
int Monopoly::Jail::getpay_amount() const {
  return 99999;
}
int Monopoly::Jail::getsent_to() const {
  return 99999;
}

