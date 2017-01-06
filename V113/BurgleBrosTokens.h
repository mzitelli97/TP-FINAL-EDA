#ifndef BURGLEBROSTOKENS_H
#define BURGLEBROSTOKENS_H
#include "BurgleBrosBoard.h"
#define NUMBER_OF_COMPUTER_ROOMS 3
#include <map>
using namespace std;
typedef enum { STEALTH_TOKEN, ALARM_TOKEN, SAFE_TOKEN, PERSIAN_KITTY_TOKEN, HACK_TOKEN, KEYPAD_TOKEN, DOWNSTAIRS_TOKEN, CROW_TOKEN} Token;
string token2Str(Token token);
#define MAX_DOWNSTAIRS_TOKENS 2

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
        list<CardLocation> getStealthTokensOnFloor();
        vector<CardLocation> getDownstairs();
        void turnOffAlarm(CardLocation location); //Desarrollar
        unsigned int howManyAlarmsOnFloor(unsigned int floor);       //FALTA DESARROLLAR
        unsigned int howManyTokensOnCPURoom(CardName cpuRoom);
        bool isThereAToken(CardLocation location, Token whichToken); //FALTA DESARROLLAR
        bool isKeypadOpen();
        CardLocation getKeypadOpenLocation();
	~BurgleBrosTokens();
private:
	bool isThereADownstairToken(CardLocation location);
    list<CardLocation> alarms;	
        list<CardLocation> crackedCards;
	list<CardLocation> stealthTokensOnFloor;
        vector<CardLocation> downstairs;
	map<CardName, unsigned int> computerRoomsInfo;
	bool keypadOpen;
	CardLocation keypadOpenLocation;
};
#endif

