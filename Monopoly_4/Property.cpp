//
// Created by mfbut on 1/20/2018.
//

#include <iostream>
#include <cmath>
#include "Property.h"
#include "Player.h"
#include "GameState.h"

Monopoly::Property::Property(CSVReader &boardFile, const int spaceNumber, const Rules &rules, GameState &gameState)
    : Space (spaceNumber), owner(nullptr), numHousesOn(0), numHotelsOn(0), rules(rules), gameState(gameState) {
  setId = boardFile.get_next_field_as_int();
  intraSetId = boardFile.get_next_field_as_int();
  name = boardFile.get_next_field();
  cost = boardFile.get_next_field_as_int();
  house_cost = boardFile.get_next_field_as_int();
  hotel_cost = boardFile.get_next_field_as_int();
  rent = boardFile.get_next_field_as_int();
  rent_with_house = boardFile.get_next_field_as_int();
  rent_with_hotel = boardFile.get_next_field_as_int();
}

void Monopoly::Property::display() const {
  const auto frmt_flags = std::cout.flags();

  //display space name
  std::cout.width(length_of_longest_space_name);
  std::cout << getName() << " | ";

  //display owner
  std::cout.width(Monopoly::Player::length_of_longest_player_name);

  std::cout << getOwnerName() << " | ";
  std::cout << getUpgradesString() << " | ";
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

void Monopoly::Property::activate(Player &activatingPlayer) {
  Player* owner = getOwner();

  //If there's no owner of this space, do purchase check and maybe auction check
  if (owner == nullptr) {
    if (activatingPlayer.getCash() >= getCost()) { //can afford the property
      bool toBuy = activatingPlayer.getBuyDecision(*this);
      if (toBuy) {
        std::cout << activatingPlayer.getName() << " bought " << getName() << " for $" << getCost()
                  << std::endl;
        activatingPlayer.purchase(*this, getCost());
      } else if(gameState.getrule().isAuction_properties()){
        gameState.auction(*this);
      }
    } else { // not enough money to buy property
      std::cout << activatingPlayer.getName() << ", you don't have enough money to afford " << getName() << ". "
                << getName() << " costs $" << getCost() << " but you only have $" << activatingPlayer.getCash()
                << std::endl;
      if(gameState.getrule().isAuction_properties()){
        gameState.auction(*this);
      }
    }

    //Player land on their own property
  } else if (owner->getId() == activatingPlayer.getId()) {
    std::cout << activatingPlayer.getName() << ", you landed on " << getName() << " which you already own" <<
              std::endl;
    //landed on a space another player owes
  } else { //landed on a space another player owes
    activatingPlayer.payPlayer(*owner, *this, gameState.getrule());
  }
}

int Monopoly::Property::getSetId() const {
  return setId;
}

int Monopoly::Property::getIntraSetId() const {
  return intraSetId;
}

const std::string& Monopoly::Property::getName() const {
  return name;
}

int Monopoly::Property::getCost() const {
  return cost;
}

int Monopoly::Property::getHouse_cost() const {
  return house_cost;
}

int Monopoly::Property::getHotel_cost() const {
  return hotel_cost;
}

int Monopoly::Property::getRent() const {
  return rent;
}

int Monopoly::Property::getRent_with_house() const {
  return rent_with_house;
}

int Monopoly::Property::getRent_with_hotel() const {
  return rent_with_hotel;
}

Monopoly::Player* Monopoly::Property::getOwner() const {
  return owner;
}

int Monopoly::Property::getLanding_multiplier() const {
  return landing_multiplier;
}

void Monopoly::Property::setLanding_multiplier(int landing_multiplier) {
  this->landing_multiplier = landing_multiplier;
}

std::string Monopoly::Property::getOwnerName() const {
  if (owner != nullptr) {
    return owner->getName();
  } else {
    return "None";
  }
}

void Monopoly::Property::setOwner(Monopoly::Player* owner) {
  Property::owner = owner;
}

int Monopoly::Property::calculateRent(const Rules& rules) const {

  if (getNumHotelsOn() > 0) {
    return getRent_with_hotel() * getNumHotelsOn();
  } else if (getNumHousesOn() > 0) {
    return static_cast<int>(getRent_with_house() * pow(2, getNumHousesOn() - 1));
  } else if (owner->ownsAllPropertiesInSet(setId)) {
    return rent * gameState.getrule().getProperty_set_multiplier();
  } else {
    return rent;
  }
}

int Monopoly::Property::getNumHousesOn() const {
  return numHousesOn;
}

int Monopoly::Property::getNumHotelsOn() const {
  return numHotelsOn;
}

bool Monopoly::Property::isFullyUpgraded() const {
  return getNumHotelsOn() == gameState.getrule().getMaxHotels();
}

bool Monopoly::Property::nextUpgradeIsHouse() const {
  return getNumHousesOn() < gameState.getrule().getNum_houses_before_hotel();
}

bool Monopoly::Property::nextUpgradeIsHotel() const {
  return getNumHousesOn() == gameState.getrule().getNum_houses_before_hotel();
}

void Monopoly::Property::upgrade() {
  if (nextUpgradeIsHouse()) {
    numHousesOn++;
    owner->payBank(getHouse_cost());
  } else if (nextUpgradeIsHotel()) {
    numHotelsOn++;
    numHousesOn = 0;
    owner->payBank(getHotel_cost());
  } else {
    std::cout << "Something impossible happened when trying to upgrade " << getName() << std::endl;
  }
}

void Monopoly::Property::downgrade() {
  if(getNumHotelsOn() > 0){
    numHotelsOn--;
    numHousesOn+= gameState.getrule().getNum_houses_before_hotel();
    owner->giveCash(getHotel_cost() / 2);
  } else if(getNumHousesOn() > 0){
    numHousesOn--;
    owner->giveCash(getHotel_cost() / 2);
  } else{
    std::cout << "Something impossible happened when trying to downgrade " << getName() << std::endl;
  }
}

std::string Monopoly::Property::getUpgradesString() const {
  const std::string upgrade("Upgrades");
  std::string upgradeString;
  for (int i = 0; i < getNumHousesOn(); ++i) {
    upgradeString.push_back('h');
  }
  for (int i = 0; i < getNumHotelsOn(); ++i) {
    upgradeString.push_back('H');
  }

  unsigned long upgradeLength = upgradeString.size();
  for (unsigned long i = 0; i < upgrade.size() - upgradeLength; ++i) {
    upgradeString.push_back(' ');
  }
  return upgradeString;
}

int Monopoly::Property::getUpgradeCost() const {

  if (nextUpgradeIsHouse()) {
    return getHouse_cost();
  } else if (nextUpgradeIsHotel()) {
    return getHouse_cost();
  } else {
    std::cout << "Problem getting upgrade cost for " << getName() << std::endl;
    return -99;
  }
}

void Monopoly::Property::setNumHousesOn(int numHousesOn) {
  Property::numHousesOn = numHousesOn;
}

void Monopoly::Property::setNumHotelsOn(int numHotelsOn) {
  Property::numHotelsOn = numHotelsOn;
}

int Monopoly::Property::getNumUpgrades() const {
  if(getNumHotelsOn() > 0){
    return getNumHotelsOn() + gameState.getrule().getNum_houses_before_hotel();
  } else{
    return getNumHousesOn();
  }
}

int Monopoly::Property::getValue() const {
  return cost + getNumHotelsOn() * getHotel_cost() + getNumHousesOn() * getHotel_cost();
}

int Monopoly::Property::getBasicRent() const {
  return getRent();
}

int Monopoly::Property::getSalary() const {
  return 99999;
}
int Monopoly::Property::getFree_Parking_money() const {
  return 99999;
}
int Monopoly::Property::getpay_amount() const {
  return 99999;
}
int Monopoly::Property::getJail_Fine() const {
  return 99999;
}
int Monopoly::Property::getJail_turn() const {
  return 99999;
}
int Monopoly::Property::getsent_to() const {
  return 99999;
}


/*
void Monopoly::Property::display() const {
  std::cout << name << " | ";
  if (owner == nullptr) {
    std::cout << "None | ";
  } else {
    std::cout << owner->getName() << " | ";
  }
}
 */


