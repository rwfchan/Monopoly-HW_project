//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_GO_H
#define HOARDINGCPPVERSION_GO_H

#include <string>
#include "GameState.h"

namespace Monopoly {
  class Player;

  class Go : public Space {
   public:
    explicit Go(CSVReader& boardFile, const int spaceNumber, GameState& gameState);
    //explicit Go(CSVReader& boardFile);
   private:
    int salary;
    int landing_multiplier;
   public:
    int getLanding_multiplier() const;
    void setLanding_multiplier(int landing_multiplier);

    //This is where the pure virtual funcation's method is declared
    void display() const override;
    void activate(Player& activatingPlayer) override;
    const std::string& getName() const override;
    int getSalary() const override;

    virtual int getFree_Parking_money() const override;
    virtual int getCost() const override;
    virtual int getSetId() const override;
    virtual int getIntraSetId() const override;
    virtual int getBasicRent() const override;
    virtual int getpay_amount() const override;
    virtual int getJail_Fine() const override ;
    virtual int getJail_turn() const override ;
    virtual int getsent_to() const override;

   private:
    std::string name;
    GameState& gameState;

  };
}

#endif //HOARDINGCPPVERSION_GO_H
