/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BurgleBrosDices.h
 * Author: javier
 *
 * Created on January 10, 2017, 12:50 PM
 */

#ifndef BURGLEBROSDICES_H
#define BURGLEBROSDICES_H

#include "BurgleBrosBoard.h"

#define MAX_NMBR_OF_EXTRA_DICES 6
#define NO_DIE 0
#define NMBR_TO_UNLOCK_KEYPAD 6

class BurgleBrosDices {
public:
    BurgleBrosDices();
    BurgleBrosDices(const BurgleBrosDices& orig);
    unsigned int getSafeDiceCount(unsigned int safeFloor);
    void setDice(vector<unsigned int> &dice);
    vector<unsigned int> getCurrDice();        //Devuelve un vector con los valores de los dados, 0 es si no fue tirado.
    vector<unsigned int> throwDiceForSafe(unsigned int safeFloor);
    vector<unsigned int> throwDiceForSafeWithExtraDie(unsigned int safeFloor);
    bool throwDiceForKeypad(CardLocation keypadLocation);
    bool didDiceUnlockKeypad();
    bool throwDiceForKeypadWithExtraDie(CardLocation keypadLocation);
    void addDieToSafe(unsigned int safeFloor);
    void addDieToKeypad(CardLocation keypadLocation);
    void resetKeypadsDice();
    bool persianKittyShallMove();
    bool chihuahuaBarks();
    unsigned int throwADie();
    
    virtual ~BurgleBrosDices();
private:
    vector<unsigned int> dice;
    unsigned int diceForSafe[BOARD_STANDARD_FLOORS];
    map<CardLocation,unsigned int> diceForKeypad;

};

#endif /* BURGLEBROSDICES_H */

