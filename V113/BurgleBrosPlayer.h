#ifndef BURGLEBROSPLAYER_H
#define BURGLEBROSPLAYER_H
#include "BurgleBrosBoard.h"
#include "BurgleBrosLoots.h"

using namespace std;

typedef enum { THE_JUICER = 0x20, THE_HACKER, THE_ACROBAT, THE_SPOTTER, THE_HAWK, THE_RAVEN, THE_PETERMAN } CharacterName;
#define NUMBER_OF_CHARACTERS 7
#define FIRST_CHARACTER THE_JUICER
#define INIT_NMBR_OF_LIVES 4

string character2Str(CharacterName character);
typedef struct{
    CardLocation position;
    CharacterName character;
    unsigned int lives;
    string name;
    
}Info2DrawPlayer;


class BurgleBrosPlayer
{
public:
	BurgleBrosPlayer();
	unsigned int getCurrLifes();
        unsigned int getcurrentActions();
	CardLocation getPosition();
	CharacterName getCharacter();
        string getName();
	bool isItsTurn();
        void setTurn(bool isPlayersTurn);
        void setActions(unsigned int actions);
        void decActions();
	bool isOnHelicopter();
	bool isOnBoard();
	bool carriesLoot();
        void setPosition(CardLocation location);
        bool hasLoot(Loot loot);
        list<Loot> getLootsCarried();
	~BurgleBrosPlayer();
private:
        void pickRandomPlayer();
        void pickRandomPlayer(CharacterName exceptThis);
	string name;
	bool isPlayersTurn;
	bool isOnTheHelicopter;
	bool isOnTheBoard;
	bool isCarryingLoot;
	CardLocation position;
	CharacterName characterName;
	unsigned int lives;
	list<Loot> lootCarried;
	unsigned int currentActions;
};
#endif
