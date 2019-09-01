//
// Created by Raymond Chan on 3/1/18.
//

#ifndef MONOPOLY_4_PAY_BANK_H
#define MONOPOLY_4_PAY_BANK_H

#include <iostream>

#include "Space.h"
#include "GameState.h"
#include "Free Parking.h"

namespace Monopoly {
  class Pay_Bank : public Space{
   public:
    explicit Pay_Bank(CSVReader& boardFile, const int spaceNumber, GameState& gameState);

    virtual int getSalary() const override;
    virtual int getCost() const override;
    virtual int getSetId() const override;
    virtual int getIntraSetId() const override;
    virtual int getBasicRent() const override;
    virtual int getFree_Parking_money() const override;
    virtual int getJail_Fine() const override ;
    virtual int getJail_turn() const override ;
    virtual int getsent_to() const override;

    int getpay_amount() const override;

    void display() const override;
    void activate(Player& activatingPlayer) override;
    const std::string& getName() const override;

    void Pay_To_Bank(Player &activatingPlayer);

   private:
    std::string name;
    int pay_amount;
    GameState& gameState;
  };
}

#endif //MONOPOLY_4_PAY_BANK_H
