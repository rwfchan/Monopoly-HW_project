//
// Created by mfbut on 1/20/2018.
//
#include <iostream>
#include "Space.h"
#include "MonopolyUtility.h"
#include "Player.h"
#include "GameState.h"
#include "Rules.h"

unsigned long Monopoly::Space::length_of_longest_space_name;

//Let's make a space, directed from Board.cpp

//This is to initialize the space
//To do so, the boardFile is needed, as well as the number of space
//Appearly the instance gameState is also needed
Monopoly::Space::Space(const int spaceNumber)
    : spaceNumber(spaceNumber) {}

/*void Monopoly::Space::display() const {
  const auto frmt_flags = std::cout.flags();

  //display space name
  std::cout.width(length_of_longest_space_name);
  std::cout << getName() << " | ";

  //display owner
  std::cout.width(Monopoly::Player::length_of_longest_player_name);

  //FIXME Try not to use this type of space checking to do the space type
  //This can be achieve since Space will be the the parent of other space type
  //How to print these space out should be indicated in the class of the corresponding space type
  if (spaceType == SpaceType::goSpace) {
    const std::string temp = "None";
    std::cout << temp << " | ";
    std::cout << "         | ";
  } else if (spaceType == SpaceType::propertySpace) {
    std::cout << propertyPtr->getOwnerName() << " | ";
    std::cout << propertyPtr->getUpgradesString() << " | ";
  } else {
    std::cout << " This space has an unknown type" << std::endl;
  }
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

}*/

//This is to add the Player onto the space
//Notice it should be in the order of their id
void Monopoly::Space::addPlayer(Monopoly::Player& player) {

  //Start form the beginning of the list of player on this space
  auto playerIt = playersOnSpace.cbegin();

  //Find the player who have the least id
  for (; playerIt != playersOnSpace.cend(); ++playerIt) {
    if (player.getId() < (*playerIt)->getId()) {
      break;
    }
  }

  //Add player onto the playersOnSpace list
  playersOnSpace.insert(playerIt, &player);
}

void Monopoly::Space::removePlayer(const Monopoly::Player& player) {
  for (auto playerIt = playersOnSpace.cbegin(); playerIt != playersOnSpace.cend(); ++playerIt) {

    //This is to remove a player from space
    if ((*playerIt)->getId() == player.getId()) {
      playersOnSpace.erase(playerIt);
      return;
    }
  }
}

//This is to reassign the player's id
//Useful whenever a player got removed
void Monopoly::Space::removeAllPlayers() {
  playersOnSpace.clear();
}

int Monopoly::Space::getSpaceNumber() const {
  return spaceNumber;
}






