//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_SPACE_H
#define HOARDINGCPPVERSION_SPACE_H

#include <memory>
#include <vector>

#include "CSVReader.h"

namespace Monopoly {
  class Player;

  class Space {
   public:
    static unsigned long length_of_longest_space_name;

    //The syntax for this one need not to be change
    //However, do need to add this to other Class
    Space(const int spaceNumber);

    int getSpaceNumber() const;
    void addPlayer(Player& player);
    void removePlayer(const Player& player);
    void removeAllPlayers();

    virtual int getSalary() const = 0;
    virtual int getCost() const = 0;
    virtual int getSetId() const = 0;
    virtual int getIntraSetId() const = 0;
    virtual int getBasicRent() const = 0;
    virtual int getFree_Parking_money() const = 0;
    virtual int getpay_amount() const = 0;
    virtual int getJail_Fine() const = 0;
    virtual int getJail_turn() const = 0;
    virtual int getsent_to() const = 0;

    //FIXME These need to be pure virtual for all the classes
    virtual void display() const = 0;
    virtual void activate(Player& activatingPlayer) = 0;
    virtual const std::string& getName() const = 0;

   protected:
    std::vector<Player*> playersOnSpace;
    int spaceNumber;
  };
}

#endif //HOARDINGCPPVERSION_SPACE_H
