//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_PROPERTY_H
#define HOARDINGCPPVERSION_PROPERTY_H
#include <string>
#include "Rules.h"
#include "Space.h"

namespace Monopoly {
  class GameState;
  class Player;

  class Property : public Space{
   public:
    explicit Property(CSVReader& boardFile, const int spaceNumber, const Rules& rules, GameState &gameState);

    void setOwner(Player* owner);
    void activate(Player& activatingPlayer) override;

    int getSetId() const override;
    int getIntraSetId() const override;
    const std::string& getName() const override;
    int getCost() const override;
    int getHouse_cost() const;
    int getHotel_cost() const;
    int getBasicRent() const override;
    int getRent() const;
    int getRent_with_house() const;
    int getRent_with_hotel() const;
    Player* getOwner() const;
    std::string getOwnerName() const;
    int calculateRent(const Rules& rules) const;
    int getNumHousesOn() const;
    int getNumHotelsOn() const;
    int getNumUpgrades() const;
    int getValue() const;
    int getLanding_multiplier() const;
    void setLanding_multiplier(int landing_multiplier);
    void display() const override;
    bool isFullyUpgraded() const;
    bool nextUpgradeIsHouse() const;
    bool nextUpgradeIsHotel() const;
    void upgrade();
    void downgrade();
    std::string getUpgradesString() const;
    int getUpgradeCost() const;
    void setNumHousesOn(int numHousesOn);
    void setNumHotelsOn(int numHotelsOn);

    virtual int getSalary() const override;
    virtual int getFree_Parking_money() const override;
    virtual int getpay_amount() const override;
    virtual int getJail_Fine() const override;
    virtual int getJail_turn() const override ;
    virtual int getsent_to() const override;


   private:
    int setId;
    int intraSetId;
    std::string name;
    int cost;
    int house_cost;
    int hotel_cost;
    int rent;
    int rent_with_house;
    int rent_with_hotel;
    Player* owner;
    int landing_multiplier;
    int numHousesOn;
    int numHotelsOn;
    const Rules& rules;
    GameState& gameState;
  };
}

#endif //HOARDINGCPPVERSION_PROPERTY_H
