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
    case DOWNSTAIRS_TOKEN: return "Downstairs";
    case CROW_TOKEN: return "Crow";
    default: return "Error";
    }
}

void BurgleBrosTokens::triggerAlarm(CardLocation location)
{
    cout<<"ALARM!"<<endl;
    list<CardLocation>::iterator it;
    for(it=alarms.begin(); it != alarms.end(); it ++)       //Recorro la lista 
    {
        if( *it ==location )                                //Si ya había una alarma en esa locación corto el for
            break;
    }
    if(it==alarms.end())                                    //Si nunca se salio del for, o sea no había ninguna alarma en la location que pasaron
        alarms.push_back(location);                          //Pongo una alarma allí
}
void BurgleBrosTokens::turnOffAlarm(CardLocation location)
{
    for(list<CardLocation>::iterator it=alarms.begin(); it != alarms.end(); it ++)       //Recorro la lista de alarmas
    {
        if( *it ==location )                                //Si ya había una alarma en esa locación, la borro y termino la función.
        {
            alarms.erase(it);
            break;
        }
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
pair<CardLocation, unsigned int> BurgleBrosTokens::getStealthTokensOnFloor()
{
    return stealthTokensOnFloor;
}
unsigned int BurgleBrosTokens::howManyTokensOnCPURoom(CardName cpuRoom)
{
    return computerRoomsInfo[cpuRoom];
}
pair<bool, CardLocation> BurgleBrosTokens::getKeypadToken()
{
    return keypad;
}
unsigned int BurgleBrosTokens::howManyAlarmsOnFloor(unsigned int floor)
{
    unsigned int count=0;
    for(list<CardLocation>::iterator it=alarms.begin(); it != alarms.end(); it ++)       //Recorro la lista de alarmas
    {
        if( it->floor == floor)   //Si la alarma esta en el piso que pasaron.                            
            count++;
    }
    return count;
}
bool BurgleBrosTokens::isThereAToken(CardLocation location, Token whichToken)
{
    bool retVal=false;
    switch(whichToken)
    {
        case DOWNSTAIRS_TOKEN:
            retVal=isThereADownstairToken(location);
            break;
        case ALARM_TOKEN:
            retVal=isThereAnAlarmToken(location);
            break;
    }
    return retVal;
}
bool BurgleBrosTokens::isThereAnAlarmToken(CardLocation location)
{
    bool retVal=false;
    for(list<CardLocation>::iterator it=alarms.begin(); it != alarms.end(); it ++)       //Recorro la lista de alarmas
    {
        if( *it == location)                            
            retVal=true;
    }
    return true;
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
bool BurgleBrosTokens::isThereAStealthToken(CardLocation location)
{
    bool retVal=false;
    if(stealthTokensOnFloor.first==location && stealthTokensOnFloor.second > 0)
        retVal=true;
    return retVal;
}
void BurgleBrosTokens::lavatoryRevealed(CardLocation lavatoryLocation)
{
    stealthTokensOnFloor.first = lavatoryLocation;
    stealthTokensOnFloor.second = LAVATORY_STEALTH_TOKENS;
}
void BurgleBrosTokens::useLavatoryToken()
{
    if(stealthTokensOnFloor.second > 0)
        stealthTokensOnFloor.second--;
}
void BurgleBrosTokens::placeDownstairToken(CardLocation location)
{
    downstairs.push_back(location);
}
void BurgleBrosTokens::addHackTokenOn(CardName computerRoom)
{
    if(computerRoomsInfo[computerRoom] < MAX_HACK_TOKENS_ON_COMPUTER_ROOM)
        computerRoomsInfo[computerRoom]++;
}
void BurgleBrosTokens::removeOneHackTokenOf(CardName computerRoom)
{
    if(computerRoomsInfo[computerRoom] > 0)
        computerRoomsInfo[computerRoom]--;
}
void BurgleBrosTokens::addCrackTokenOn(CardLocation location)
{
    bool alreadyCracked=false;
    for(list<CardLocation>::iterator it=crackedCards.begin(); it != crackedCards.end(); it++)
    {
        if(*it == location)
            alreadyCracked=true;
    }
    if(!alreadyCracked)
        crackedCards.push_back(location);
}
void BurgleBrosTokens::addCrackTokenOn(list<CardLocation> &location)
{
    for(list<CardLocation>::iterator it=location.begin(); it != location.end(); it++)
        addCrackTokenOn(*it);
}
bool BurgleBrosTokens::isSafeOpened(unsigned int floor)
{
    bool retVal=false;
    unsigned int count=0;
    for(list<CardLocation>::iterator it= crackedCards.begin(); it!=crackedCards.end(); it++)
    {
        if(it->floor == floor)
            count++;
    }
    if(count == 6) //Si había 6 cartas crackeadas en el mismo piso significa que el safe de ese piso esta crackeado
        retVal=true;
    return retVal;
}
pair<bool, CardLocation> BurgleBrosTokens::getPersianKittyToken()
{
    return persianKitty;
}
pair<bool, CardLocation> BurgleBrosTokens::getCrowToken()
{
    return crowToken;
}
BurgleBrosTokens::~BurgleBrosTokens()
{
}
