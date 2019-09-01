//
// Created by Raymond Chan on 3/1/18.
//

#ifndef MONOPOLY_4_GO_TO_JAIL_H
#define MONOPOLY_4_GO_TO_JAIL_H
#include <iostream>

#include "Space.h"
#include "Jail.h"
#include "GameState.h"

namespace Monopoly {
  class Go_to_jail : public Space{
   public:
    explicit Go_to_jail(CSVReader& boardFile, const int spaceNumber, Board& board);

    virtual int getSalary() const override;
    virtual int getCost() const override;
    virtual int getSetId() const override;
    virtual int getIntraSetId() const override;
    virtual int getBasicRent() const override;
    virtual int getpay_amount() const override;
    virtual int getFree_Parking_money() const override;
    virtual int getJail_Fine() const override;
    virtual int getJail_turn() const override;

    int getsent_to() const override;

    void display() const override;
    void activate(Player& activatingPlayer) override;
    const std::string& getName() const override;

   private:
    std::string name;
    int sent_to;

    Board& board;
  };
}


#endif //MONOPOLY_4_GO_TO_JAIL_H
