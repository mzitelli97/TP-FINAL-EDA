/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BurgleBrosDices.cpp
 * Author: javier
 * 
 * Created on January 10, 2017, 12:50 PM
 */

#include <map>

#include "BurgleBrosDices.h"


#define DIE_MIN_VAL 1
#define DIE_MAX_VAL 6

#define INIT_SAFE_DICE_COUNT 0      //Empieza con 0 solo dado para el safe
#define INIT_KEYPAD_DICE_COUNT 1 


BurgleBrosDices::BurgleBrosDices() {
    for(unsigned int i=0; i<MAX_NMBR_OF_EXTRA_DICES ; i++)
        dice.push_back(NO_DIE);
    for(unsigned int i=0; i<BOARD_STANDARD_FLOORS ; i++)
        diceForSafe[i]=INIT_SAFE_DICE_COUNT;
}

BurgleBrosDices::BurgleBrosDices(const BurgleBrosDices& orig) {
}
unsigned int BurgleBrosDices::getSafeDiceCount(unsigned int safeFloor)
{
    if(safeFloor<BOARD_STANDARD_FLOORS)
        return diceForSafe[safeFloor];
    else
        return 0;
}

vector<unsigned int> BurgleBrosDices::throwDiceForSafe(unsigned int safeFloor)
{
    for(unsigned int i=0; i<diceForSafe[safeFloor] ; i++)
        dice[i]=DIE_MIN_VAL+rand()%DIE_MAX_VAL;
    for(unsigned int i=diceForSafe[safeFloor]; i<MAX_NMBR_OF_EXTRA_DICES  ; i++)
        dice[i]=NO_DIE;
    return dice;
}
vector<unsigned int> BurgleBrosDices::throwDiceForSafeWithExtraDie(unsigned int safeFloor)
{
    if(diceForSafe[safeFloor]<MAX_NMBR_OF_EXTRA_DICES)
    {
        for(unsigned int i=0; i<diceForSafe[safeFloor]+1 ; i++)
            dice[i]=DIE_MIN_VAL+rand()%DIE_MAX_VAL;
        for(unsigned int i=diceForSafe[safeFloor]+1; i<MAX_NMBR_OF_EXTRA_DICES  ; i++)
            dice[i]=NO_DIE;
    }
    else 
        throwDiceForSafe(safeFloor);
    return dice;
}
void BurgleBrosDices::addDieToKeypad(CardLocation keypadLocation)
{
    if(diceForKeypad.find(keypadLocation) == diceForKeypad.end())   //Si no se había registrado un keypad en esa posición, lo creo
        diceForKeypad[keypadLocation]=INIT_KEYPAD_DICE_COUNT;
    diceForKeypad[keypadLocation]++;
}
void BurgleBrosDices::addDieToSafe(unsigned int safeFloor)
{
    if(diceForSafe[safeFloor] < MAX_NMBR_OF_EXTRA_DICES)
    {   diceForSafe[safeFloor]++;
        dice[diceForSafe[safeFloor]-1]= DIE_MIN_VAL;       //Para que aparezca en la pantalla
        for(unsigned int i=diceForSafe[safeFloor]; i<MAX_NMBR_OF_EXTRA_DICES  ; i++)
            dice[i]=NO_DIE;
    }
}
void BurgleBrosDices::resetKeypadsDice()
{
    for(map<CardLocation,unsigned int>::iterator it = diceForKeypad.begin(); it != diceForKeypad.end(); it++)
        it->second=INIT_KEYPAD_DICE_COUNT;
    for(unsigned int i=0; i<MAX_NMBR_OF_EXTRA_DICES  ; i++)
        dice[i]=NO_DIE;
}


bool BurgleBrosDices::throwDiceForKeypad(CardLocation keypadLocation)
{
    bool retVal=false;
    if(diceForKeypad.find(keypadLocation) == diceForKeypad.end())   //Si no se había registrado un keypad en esa posición, lo creo
        diceForKeypad[keypadLocation]=INIT_KEYPAD_DICE_COUNT;
    for(unsigned int i=0; i<diceForKeypad[keypadLocation] ; i++)
        dice[i]=DIE_MIN_VAL+rand()%DIE_MAX_VAL;
    for(unsigned int i=diceForKeypad[keypadLocation]; i<MAX_NMBR_OF_EXTRA_DICES  ; i++)
        dice[i]=NO_DIE;
    for(unsigned int i=0; i<MAX_NMBR_OF_EXTRA_DICES ; i++)
    {
        if(dice[i]==NMBR_TO_UNLOCK_KEYPAD)
            retVal=true;
    }
    return retVal;
}
bool BurgleBrosDices::throwDiceForKeypadWithExtraDie(CardLocation keypadLocation)
{
    bool retVal=false;
    if(diceForKeypad.find(keypadLocation) == diceForKeypad.end())   //Si no se había registrado un keypad en esa posición, lo creo
        diceForKeypad[keypadLocation]=INIT_KEYPAD_DICE_COUNT;
    for(unsigned int i=0; i<diceForKeypad[keypadLocation]+1 ; i++)
        dice[i]=DIE_MIN_VAL+rand()%DIE_MAX_VAL;
    for(unsigned int i=diceForKeypad[keypadLocation]+1; i<MAX_NMBR_OF_EXTRA_DICES  ; i++)
        dice[i]=NO_DIE;
    for(unsigned int i=0; i<MAX_NMBR_OF_EXTRA_DICES ; i++)
    {
        if(dice[i]==NMBR_TO_UNLOCK_KEYPAD)
            retVal=true;
    }
    return retVal;
}
bool BurgleBrosDices::persianKittyShallMove()
{
    bool retVal=false;
    dice[0]=DIE_MIN_VAL+rand()%DIE_MAX_VAL;
    for(unsigned int i=1; i<MAX_NMBR_OF_EXTRA_DICES  ; i++)
            dice[i]=NO_DIE;
    if(dice[0] < 3)
        retVal=true;
    return retVal;
}
bool BurgleBrosDices::chihuahuaBarks()
{
    bool retVal=false;
    dice[0]=DIE_MIN_VAL+rand()%DIE_MAX_VAL;
    for(unsigned int i=1; i<MAX_NMBR_OF_EXTRA_DICES  ; i++)
            dice[i]=NO_DIE;
    if(dice[0] == 6)
        retVal=true;
    return retVal;
}

vector<unsigned int> BurgleBrosDices::getCurrDice()
{
    return dice;
}
BurgleBrosDices::~BurgleBrosDices() {
}

