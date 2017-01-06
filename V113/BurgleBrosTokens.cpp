#include <map>

#include "BurgleBrosTokens.h"
string token2Str(Token token)
{
	switch (token)
	{
	case STEALTH_TOKEN:return "Stealth";
	case ALARM_TOKEN:return "Alarm";
	case SAFE_TOKEN:return "Safe";
	case PERSIAN_KITTY_TOKEN:return "Persian kitty";
	case HACK_TOKEN:return "Hack";
	case KEYPAD_TOKEN:return "Keypad open";
	default: return "Error";
	}
}


BurgleBrosTokens::BurgleBrosTokens()
{
    pair<CardName, unsigned int> aux1(COMPUTER_ROOM_FINGERPRINT,0);
    pair<CardName, unsigned int> aux2(COMPUTER_ROOM_LASER,0);
    pair<CardName, unsigned int> aux3(COMPUTER_ROOM_MOTION,0);
    computerRoomsInfo.insert(aux1);
    computerRoomsInfo.insert(aux2);
    computerRoomsInfo.insert(aux3);
    downstairs.reserve(MAX_DOWNSTAIRS_TOKENS);
}

list<CardLocation> BurgleBrosTokens::getAlarmsList()
{
    return alarms;
}
vector<CardLocation> BurgleBrosTokens::getDownstairs()
{
    return downstairs;
}

list<CardLocation> BurgleBrosTokens::getCrackedCards()
{
    return crackedCards;
}
list<CardLocation> BurgleBrosTokens::getStealthTokensOnFloor()
{
    return stealthTokensOnFloor;
}
unsigned int BurgleBrosTokens::howManyTokensOnCPURoom(CardName cpuRoom)
{
    return computerRoomsInfo[cpuRoom];
}
bool BurgleBrosTokens::isKeypadOpen()
{
    return keypadOpen;
}
CardLocation BurgleBrosTokens::getKeypadOpenLocation()
{
    return keypadOpenLocation;
}
bool BurgleBrosTokens::isThereAToken(CardLocation location, Token whichToken)
{
    bool retVal=false;
    switch(whichToken)
    {
        case DOWNSTAIRS_TOKEN:
            retVal=isThereADownstairToken(location);
            break;
    }
    return retVal;
}


bool BurgleBrosTokens::isThereADownstairToken(CardLocation location)
{
    bool retVal=false;
    for(unsigned int i = 0; i < MAX_DOWNSTAIRS_TOKENS; i++)
    {
        if(downstairs[i] == location)
            retVal=true;
    }
    return retVal;
}


BurgleBrosTokens::~BurgleBrosTokens()
{
}
