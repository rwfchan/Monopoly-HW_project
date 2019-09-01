//
// Created by Raymond Chan on 3/1/18.
//

#ifndef MONOPOLY_4_JAIL_H
#define MONOPOLY_4_JAIL_H
#include <iostream>

#include "Space.h"
#include "GameState.h"

namespace Monopoly {
  class Jail : public Space{
   public:
    Jail(CSVReader& boardFile, const int spaceNumber, GameState& gameState);

    virtual int getSalary() const override;
    virtual int getCost() const override;
    virtual int getSetId() const override;
    virtual int getIntraSetId() const override;
    virtual int getBasicRent() const override;
    virtual int getpay_amount() const override;
    virtual int getFree_Parking_money() const override;
    virtual int getsent_to() const override;

    int getJail_Fine() const override;
    int getJail_turn() const override;
    bool getSent_From_Jail() const;
    void filpSent_From_Jail();

    void display() const override;
    void activate(Player& activatingPlayer) override;
    const std::string& getName() const override;

    void Player_Move_in_jail(Player& player);
    void Pay_for_jail(Player& immate);

   private:
    std::string name;
    int Jail_Fine;
    int Jail_turn;

    //The filp of from jail switch is controlled by GoToJail class
    bool Sent_From_Jail;

    GameState& gameState;
  };
}

#endif //MONOPOLY_4_JAIL_H
