//
// Created by Raymond Chan on 3/1/18.
//

#include "GameState.h"
#include "Go to jail.h"

//board.getSpace(getsent_to()) == the space that have the index indicated by GOTOJAIL

Monopoly::Go_to_jail::Go_to_jail(CSVReader &boardFile, const int spaceNumber, Board& board)
    : Space(spaceNumber), board(board){
  name = boardFile.get_next_field();
  sent_to = boardFile.get_next_field_as_int();
}

void Monopoly::Go_to_jail::display() const {
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

void Monopoly::Go_to_jail::activate(Player &activatingPlayer) {
  Space* space = &board.getSpace(getsent_to());
  Jail* jail = dynamic_cast<Jail*>(&(*space));

  jail->filpSent_From_Jail();
  activatingPlayer.moveTo(this->board.getSpace(sent_to));
}



const std::string& Monopoly::Go_to_jail::getName() const {
  return name;
}
int Monopoly::Go_to_jail::getsent_to() const {
  return sent_to;
}

int Monopoly::Go_to_jail::getJail_Fine() const {
  return 99999;
}
int Monopoly::Go_to_jail::getJail_turn() const {
  return 99999;
}
int Monopoly::Go_to_jail::getFree_Parking_money() const {
  return 99999;
}
int Monopoly::Go_to_jail::getSalary() const {
  return 99999;
}
int Monopoly::Go_to_jail::getCost() const {
  return 99999;
}
int Monopoly::Go_to_jail::getSetId() const {
  return 99999;
}
int Monopoly::Go_to_jail::getIntraSetId() const {
  return 99999;
}
int Monopoly::Go_to_jail::getBasicRent() const {
  return 99999;
}
int Monopoly::Go_to_jail::getpay_amount() const {
  return 99999;
}
