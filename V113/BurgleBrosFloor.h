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
	void initFloor(unsigned int whichFloor, std::vector<CardName> &orderedCards);                   //Inicializa el floor con las cartas dadas en forma de vector.
        void getWalls(vector<wall> &vector);                                                            //Devuelve las 8 walls correspondientes a su piso.
	std::list<CardLocation> getShortestPath(CardLocation source, CardLocation destination);		//Devuelve la lista que da el camino más corto desde una posición a otra.
	bool areTilesAdjacent(CardLocation source, CardRelativeLocation whereToMove);                   //Dice si son adjacentes (puede ser que no porque no haya nada a su posición relativa o una pared).
	bool areTilesAdjacent(CardLocation source, CardLocation destination);
	unsigned int setCardVisible(CardLocation location);                                 //Da vuelta una carta y devuelve que numero de safe number salio
        unsigned int setCardVisible(CardLocation location, int safeNumber);                 //Da vuelta la carta, le asigna el safenumber pasado por asignado y devuleve el mismo.
        bool isAWallBetween(CardLocation tile1, CardLocation tile2);                //Devuelve si hay una pared entre 2 tiles
	bool isCardVisible(CardLocation location);                                  
	void crackSafe();                                                           //Le pone a la carta SAFE de su piso que está crackeada.
	unsigned int getCardSafeNumber(CardLocation location);                      //Devuelve el numero para crackear de una carta
        bool isSafeCracked();                                                       //Devuelve si ya se crackeó la safe
        CardLocation getSafeLocation();                                             //Devuelve la posición del safe
	CardName getCardType(CardLocation location);                                //Obtiene que tipo de tile es en esa ubicación.
	CardName getCardType(unsigned int number);
        CardLocation getKittyMovingPos(CardLocation location);          //Dice para donde va ir el persian kitty si se tiran mal los dados
	~BurgleBrosFloor();
private:
	CardLocation intToIndex(unsigned int i );
	void linkCards();           //Le pone todos los vecinos propios a cada carta del piso
        void initAdjList();         //Crea la lista de adjacencia, para poder computar los dijkstra más facilmente
        void computeDijkstra(unsigned int sourceCard, unsigned int destinationCard,vector<unsigned int> &minDist,vector<int> &prevCard);
        vector<vector<unsigned int>> adjacentList;  //Para cada carta representada con un entero (0,0,0 -> 0, 0,1,0->4, etc), hay un vector con todas sus adjacentes representadas también por un número entero.
	void linkCardsWithoutWalls();       
	void generateWalls();
	unsigned int floorNumber;
	wall walls[NUMBER_OF_WALLS];
	BurgleBrosCard cards[FLOOR_RAWS][FLOOR_COLUMNS];
};
#endif

