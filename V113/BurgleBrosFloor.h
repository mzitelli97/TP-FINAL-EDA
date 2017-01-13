#ifndef BURGLEBROSFLORR_H
#define BURGLEBROSFLORR_H
#include "BurgleBrosCard.h"
#include <list>
#include <vector>
#define FLOOR_RAWS 4
#define FLOOR_COLUMNS 4
#define NUMBER_OF_WALLS 8

typedef struct{
	CardLocation FrontCard;	//Siempre se toma la del frente como la de la izquierda o la de arriba
	CardLocation RearCard;	//Siempre se toma la de atras como la de la derecha o la de abajo.
}wall;

using namespace std;

class BurgleBrosFloor
{
public:
	BurgleBrosFloor(unsigned int whichFloor, std::vector<CardName> &orderedCards);			//Deben ser si o si FLOOR_COLUMNS*FLOOR_RAWS cartas
	BurgleBrosFloor();
	//BurgleBrosFloor(unsigned int whichFloor, std::string protocolCardTypes);
	void initFloor(unsigned int whichFloor, std::vector<CardName> &orderedCards);
        void getWalls(vector<wall> &vector);
	std::string getShortestPathProtocolar(CardLocation source, CardLocation destination);		//Devuelve con formato de protocolo
	std::list<CardLocation> getShortestPath(CardLocation source, CardLocation destination);		//
	bool isMovePossible(CardLocation source, CardRelativeLocation whereToMove);
	bool isMovePossible(CardLocation source, CardLocation destination);
	bool isMovePossible(std::string source, std::string destination);
	BurgleBrosCard getCardCopy(CardLocation location);
	void setCardVisible(CardLocation location);
        bool isAWallBetween(CardLocation tile1, CardLocation tile2);
	bool isCardVisible(CardLocation location);
	void crackSafe();
	unsigned int getCardSafeNumber(CardLocation location);
        bool isCardCracked(CardLocation location);  //()
        bool isSafeCracked();
        CardLocation getSafeLocation();
	CardName getCardType(CardLocation location);
	CardName getCardType(unsigned int number);
        CardLocation getKittyMovingPos(CardLocation location); // Dice para donde va ir el persian kitty si se tiran mal los dados
	void testFloor();

	~BurgleBrosFloor();
private:
	CardLocation intToIndex(unsigned int i );
	void linkCards();
        void initAdjList();
        void computeDijkstra(unsigned int sourceCard, unsigned int destinationCard,vector<unsigned int> &minDist,vector<int> &prevCard);
        vector<vector<unsigned int>> adjacentList;
	void linkCardsWithoutWalls();
	void generateWalls();
	unsigned int floorNumber;
	wall walls[NUMBER_OF_WALLS];
	BurgleBrosCard cards[FLOOR_RAWS][FLOOR_COLUMNS];
};
#endif

