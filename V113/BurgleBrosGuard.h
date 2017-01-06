#ifndef BURGLEBROSGUARD_H
#define BURGLEBROSGUARD_H
#include "BurgleBrosBoard.h"

#define FLOOR_1_INIT_DICE 2
#define FLOOR_2_INIT_DICE 3
#define FLOOR_3_INIT_DICE 4

using namespace std;
typedef struct{
    CardLocation position;
    unsigned int dieNumber;
    CardLocation diePosition;
    list<CardLocation> shownDeck;    
    
}Info2DrawGuard;

class BurgleBrosGuard
{
public:
	BurgleBrosGuard();
        BurgleBrosGuard(unsigned int floor);
	CardLocation getTopCard();
	list<CardLocation> getPath();
        list<CardLocation> getShownDeck();
	unsigned int getDiceNumber();
	unsigned int getfloor();
	CardLocation getPosition();
	CardLocation getTargetPosition();
        string getInitGPos();
	~BurgleBrosGuard();
private:
	bool step(); //devuelve 1 si lleg� al objetivo.
        void setPosition();
        void initCardDeck();
        void shuffleCardDeck();
        void setPosition(string initialGPos);
	void setNewTarget(CardLocation alarm);
	CardLocation drawCardTarget();
	bool drawCardTarget(CardLocation targetCard);
	void shuffleDecks();
	list<CardLocation> cardDeck;
	list<CardLocation> shownDeck;
	CardLocation currentTarget;
	CardLocation position;
	unsigned int diceNumber;
	unsigned int floor;
        bool isGuardsTurn;
	list<CardLocation> pathToTarget;
};
#endif

