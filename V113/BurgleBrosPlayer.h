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
    unsigned int currActions;
    bool turn;
}Info2DrawPlayer;

CharacterName getRandomCharacter();
CharacterName  getRandomCharacter(CharacterName exceptThis);


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
        void setCharacter(CharacterName character);
        void getToDaChoppa();
        bool hasLoot(Loot loot);
        void pickRandomPlayer();
        void pickRandomPlayer(CharacterName exceptThis);
        list<Loot> getLootsCarried();
        void attachLoot(Loot loot);
        void deattachLoot(Loot loot);
        void setName(string name);
        void decLives();
	~BurgleBrosPlayer();
private:
        
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
