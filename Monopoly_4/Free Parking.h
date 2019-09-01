//
// Created by Raymond Chan on 3/1/18.
//

#ifndef MONOPOLY_4_FREE_PARKING_H
#define MONOPOLY_4_FREE_PARKING_H

#include <iostream>

#include "Space.h"
#include "GameState.h"

namespace Monopoly {

  class Free_Parking : public Space{
   public:
    explicit Free_Parking(CSVReader& boardFile, const int spaceNumber, GameState& gameState);

    virtual int getSalary() const override;
    virtual int getCost() const override;
    virtual int getSetId() const override;
    virtual int getIntraSetId() const override;
    virtual int getBasicRent() const override;
    virtual int getpay_amount() const override;
    virtual int getJail_Fine() const override;
    virtual int getJail_turn() const override ;
    virtual int getsent_to() const override;


    int getFree_Parking_money() const override;

    void add_Free_Parking_money(int add_amount);

    void display() const override;
    void activate(Player& activatingPlayer) override;
    const std::string& getName() const override;

   private:
    std::string name;
    int Free_Parking_money;
    GameState& gameState;
  };
}

#endif //MONOPOLY_4_FREE_PARKING_H
