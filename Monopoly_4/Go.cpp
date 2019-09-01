//
// Created by mfbut on 1/20/2018.
//

#include "Go.h"
#include "GameState.h"
#include <iostream>

//The default Go landing_multiplier is 1
//The next number is salary so it will become salary value of GO
//The line after is the name of Go, so it will be put into the name value of GO

Monopoly::Go::Go(CSVReader &boardFile, const int spaceNumber, GameState& gameState)
    : Space(spaceNumber), landing_multiplier(1), gameState(gameState){
  salary = boardFile.get_next_field_as_int();
  name = boardFile.get_next_field();
}

void Monopoly::Go::display() const {
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

void Monopoly::Go::activate(Player &activatingPlayer) {
  activatingPlayer.giveCash(getSalary() * (gameState.getrule().getSalary_multiplier_for_landing_on_go() - 1));
}

int Monopoly::Go::getSalary() const {
  return salary;
}

const std::string& Monopoly::Go::getName() const {
  return name;
}

int Monopoly::Go::getLanding_multiplier() const {
  return landing_multiplier;
}

void Monopoly::Go::setLanding_multiplier(int landing_multiplier) {
  this->landing_multiplier = landing_multiplier;
}

int Monopoly::Go::getCost() const {
  return 99999;
}
int Monopoly::Go::getSetId() const {
  return 99999;
}
int Monopoly::Go::getIntraSetId() const {
  return 99999;
}
int Monopoly::Go::getBasicRent() const {
  return 99999;
}
int Monopoly::Go::getFree_Parking_money() const {
  return 99999;
}
int Monopoly::Go::getpay_amount() const {
  return 99999;
}
int Monopoly::Go::getJail_Fine() const {
  return 99999;
}
int Monopoly::Go::getJail_turn() const {
  return 99999;
}
int Monopoly::Go::getsent_to() const {
  return 99999;
}



/*
void Monopoly::Go::display() const {
  std::cout << name << " | None | ";
}
*/