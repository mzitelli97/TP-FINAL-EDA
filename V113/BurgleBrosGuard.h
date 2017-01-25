#ifndef BURGLEBROSGUARD_H
#define BURGLEBROSGUARD_H
#include "BurgleBrosBoard.h"

#define FLOOR_1_INIT_DICE 2
#define FLOOR_2_INIT_DICE 3
#define FLOOR_3_INIT_DICE 4

#define NUMBER_OF_CARDS_TO_PLAY 10 //Cuando se juega de a 2 jugadores se toman solo 10 cartas de juego

using namespace std;
typedef struct{
    CardLocation position;
    unsigned int dieNumber;
    CardLocation diePosition;
    list<CardLocation> shownDeck;
    bool initialized;
    bool isTopOfNotShownDeckVisible;
    CardLocation topOfNotShownDeck;
}Info2DrawGuard;

class BurgleBrosGuard
{
public:
	BurgleBrosGuard();
        BurgleBrosGuard(unsigned int floor);
	CardLocation getTopCard();
        void setPosition(CardLocation location);
        bool checkIfInitialized();
	list<CardLocation> getPath();
        list<CardLocation> getShownDeck();
	unsigned int getDiceNumber();
	unsigned int getfloor();
	CardLocation getPosition();
	CardLocation getTargetPosition();
        void init();
        void init(CardLocation guardPos, CardLocation diePos);
        void incDiceNumber();
        bool isTopOfNotShownDeckVisible();
        void pushTopCardToTheBottom();
        void pushCardToTheBottom(CardLocation thisCard);
        void pushCardToTheTop(CardLocation thisCard);
        void setTopOfNotShownDeckVisible(bool whichState);
        bool step();                                        //DESARROLLAR (devuelve 1 si llego al objetivo)
        void setNewTarget(CardLocation alarm);              //DESARROLLAR
        void setNewPathToTarget(list<CardLocation> &pathToTarget);   //DESARROLLAR
        CardLocation drawCardTarget();      //Devuelve una copia la que agarró
	bool drawCardTarget(CardLocation targetCard);   //Devuelve true si encontró la carta en el mazo de las no mostradas.
	~BurgleBrosGuard();
private:
        void setPosition();
        void initCardDeck();
        void shuffleCardDeck();
	
	void shuffleDecks();
        bool initialized;
        bool topOfNotShownDeckVisible;      //Indica si está visible la primer carta del mazo de las que no fueron mostradas ( para el special ability del spotter).
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

