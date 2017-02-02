#ifndef BURGLEBROSTOKENS_H
#define BURGLEBROSTOKENS_H
#include "BurgleBrosBoard.h"
#define NUMBER_OF_COMPUTER_ROOMS 3
#include <map>
using namespace std;
typedef enum { STEALTH_TOKEN, ALARM_TOKEN, SAFE_TOKEN, PERSIAN_KITTY_TOKEN, HACK_TOKEN, KEYPAD_TOKEN, DOWNSTAIRS_TOKEN, CROW_TOKEN} Token;
string token2Str(Token token);

#define MAX_DOWNSTAIRS_TOKENS 3
#define MAX_HACK_TOKENS_ON_COMPUTER_ROOM 6
#define LAVATORY_STEALTH_TOKENS 3

typedef struct
{
    Token token;
    CardLocation position;
}Info2DrawTokens;


class BurgleBrosTokens
{
public:
    BurgleBrosTokens();
    list<CardLocation> getAlarmsList();
    list<CardLocation> getCrackedCards();
    pair<CardLocation, unsigned int> getStealthTokensOnFloor();
    list<CardLocation> getKeypadTokens();
    pair<bool, CardLocation> getPersianKittyToken();
    pair<bool, CardLocation> getCrowToken();
    vector<CardLocation> getDownstairs();
    void triggerAlarm(CardLocation location);   
    void turnOffAlarm(CardLocation location);
    void lavatoryRevealed(CardLocation lavatoryLocation);
    void useLavatoryToken();
    void placeDownstairToken(CardLocation location);
    void addHackTokenOn(CardName computerRoom);
    void removeOneHackTokenOf(CardName computerRoom);
    void addCrackTokenOn(CardLocation location);
    void addCrackTokenOn(list<CardLocation> &location);
    bool isSafeOpened(unsigned int floor);
    bool areAllSafesOpen();
    unsigned int howManyAlarmsOnFloor(unsigned int floor);       
    unsigned int howManyTokensOnCPURoom(CardName cpuRoom);
    void placeCrowToken(CardLocation location);
    bool isThereAKeypadToken(CardLocation location);
    void putKeyPadToken(CardLocation location);
    bool isThereAToken(CardLocation location, Token whichToken); //FALTA DESARROLLAR
    bool isThereADownstairToken(CardLocation location);
    bool isThereAnAlarmToken(CardLocation location);
    bool isThereAStealthToken(CardLocation location);
    bool isThereACrowToken(CardLocation  location);
    bool isThereAPersianKittyToken(CardLocation  location);
    void placePersianKittyToken(pair<bool, CardLocation> persianKittyToken);
    ~BurgleBrosTokens();
private:
    list<CardLocation> alarms;	
    list<CardLocation> crackedCards;
    pair<CardLocation, unsigned int> stealthTokensOnFloor;
    vector<CardLocation> downstairs;
    map<CardName, unsigned int> computerRoomsInfo;
    list<CardLocation>keypadTokens;
    pair<bool, CardLocation> persianKitty;  //El bool representa si está el token en el tablero.
    pair<bool, CardLocation> crowToken;     //El bool representa si está el token en el tablero.
    
};
#endif

