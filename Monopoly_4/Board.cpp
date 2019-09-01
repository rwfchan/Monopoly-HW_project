//
// Created by mfbut on 1/20/2018.
//

#include "Board.h"
#include <iostream>
#include "MonopolyUtility.h"
#include "Player.h"
#include "GameState.h"
#include "Go.h"
#include "Property.h"
#include "Free Parking.h"
#include "Pay Bank.h"
#include "Go to jail.h"

//Utility is just to make the board look nice and pretty

//This is where the information from CSV convert to the information for the board
Monopoly::Board::Board(const std::string& boardFileName, GameState& gameState) {
  CSVReader boardFile(boardFileName);
  constexpr int num_lines_to_skip = 4;

  //This is to check if the broadFile is readable
  //If it is, then start reading the file
  //Else, don't read the file

  //The function of boardFile are all in CSVReader
  if (boardFile.good()) {

    //Keep skipping until the first ',' is reach
    boardFile.skip_field();

    //Read in the Number of Spaces on the first line
    //The number of spaces in this case is the int right after the ','
    const int numSpaces = boardFile.get_next_field_as_int();

    //Number of lines to skip is always 4, in theory
    for (int i = 0; i < num_lines_to_skip; ++i) {

      //This skips line
      boardFile.skip_line();
    }

    //Get into the vector of Spaces, named "space", and start getting information into the board
    //In order to make ONE space, the input of the FILE, the INDEX of the space, and the gameState INSTANCE is needed
    /*for (int i = 0; i < numSpaces; ++i) {
      spaces.emplace_back(boardFile, i, gameState);
    }*/

    for (int i = 0; i < numSpaces; ++i) {
      std::string space_type_string = boardFile.get_next_field();

      if (space_type_string == "Go") {
        spaces.push_back(std::make_unique<Go>(boardFile, i, gameState));
        boardFile.skip_line();
      } else if (space_type_string == "Property") {
        spaces.push_back(std::make_unique<Property>(boardFile, i, gameState.getrule(), gameState));
      } else if (space_type_string == "FreeParking") {
        spaces.push_back(std::make_unique<Free_Parking>(boardFile, i, gameState));
        boardFile.skip_line();
      } else if (space_type_string == "Pay") {
        spaces.push_back(std::make_unique<Pay_Bank>(boardFile, i, gameState));
        boardFile.skip_line();
      } else if (space_type_string == "Jail") {
        spaces.push_back(std::make_unique<Jail>(boardFile, i, gameState));
        boardFile.skip_line();
      } else if (space_type_string == "GoToJail"){
        spaces.push_back(std::make_unique<Go_to_jail>(boardFile, i, *this));
        boardFile.skip_line();
      }
    }

    //This is just making the board look good
    Monopoly::Space::length_of_longest_space_name = calc_length_of_longest_space_name();
    Monopoly::Space::length_of_longest_space_name =
        Utility::max(Monopoly::Space::length_of_longest_space_name, std::string("Space Name").size());

  } else {
    std::cout << "Failed to open board file: " << boardFileName << std::endl;
  }
}

void Monopoly::Board::display() const {

  //const std::string header("Space Number | Space Name | Owner | Upgrades | Players");

  //std::cout << header << std::endl;
  const std::string spaceNumber("Space Number");
  const std::string spaceName("Space Name");
  const std::string owner("Owner");
  const std::string Upgrades("Upgrades");
  const std::string playersString("Players");
  const auto frmt_flags = std::cout.flags();
  std::cout.setf(std::ios::left);

  std::cout << spaceNumber; std::cout << " | ";
  std::cout.width(Space::length_of_longest_space_name);
  std::cout << spaceName; std::cout << " | ";

  std::cout.width(Player::length_of_longest_player_name);
  std::cout << owner; std::cout << " | ";

  std::cout.width(Upgrades.size());
  std::cout << Upgrades << " | ";

  std::cout.width(Player::length_of_longest_player_name);
  std::cout << playersString; std::cout << std::endl;

  int i = 0;
  for (const auto& space : spaces) {
    std::cout.width(spaceNumber.size());
    std::cout << i << " | ";
    space->display();
    std::cout << std::endl;
    ++i;
  }
  std::cout.flags(frmt_flags);


}

unsigned long Monopoly::Board::calc_length_of_longest_space_name() const {
  std::vector<std::string> space_names;
  for (const auto& space : spaces) {
    space_names.emplace_back(space->getName());
  }
  return Utility::get_max_string_length(space_names);
}

Monopoly::Space& Monopoly::Board::getSpace(int spaceNum) {
  return *spaces[spaceNum];
}

Monopoly::Space& Monopoly::Board::getGoSpace() {
  //this line should never execute
  return static_cast<Monopoly::Go&>(*spaces[0]);
}

int Monopoly::Board::getNumSpaces() const {
  return static_cast<int>(spaces.size());
}

const std::vector<std::unique_ptr<Monopoly::Space>>& Monopoly::Board::getSpaces() const {
  return spaces;
}

void Monopoly::Board::removeAllPlayers() {
  for (auto& space : spaces) {
    space->removeAllPlayers();
  }
}
