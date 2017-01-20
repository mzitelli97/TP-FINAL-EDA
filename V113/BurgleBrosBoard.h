#ifndef BURGLEBROSBOARD_H
#define BURGLEBROSBOARD_H
#include "BurgleBrosFloor.h"
#include <string>

CardLocation intToCardLocation(unsigned int cardNumber); //si se la llama con 16, devuleve (1,0,0) (piso 1 la primer carta), etc.  0<=i<48

#define BOARD_STANDARD_FLOORS 3

class BurgleBrosBoard
{
public:
	BurgleBrosBoard();
	void initBoard();
        void initBoard(vector<CardName> &allTiles);//Inicializa el tablero repartiendo las cartas entre los distintos pisos.
	bool adjacentCards(CardLocation source, CardRelativeLocation whereToMove);
	bool adjacentCards(CardLocation source, CardLocation destination);              //Devuelve true si las cartas son vecinas y no hay paredes entre ellas.
	void getWalls(vector<wall> &vector);    
	unsigned int setCardVisible(CardLocation location);
        unsigned int setCardVisible(CardLocation location, unsigned int safeNumber);   //Da vuelta una carta y le asigna un numero de safeNumber específico.       
	bool isCardVisible(CardLocation location);
	unsigned int getCardSafeNumber(CardLocation location);
        bool isSafeCracked(unsigned int floor);
        bool setSafeCracked(unsigned int floor);
        bool isAWallBetween(CardLocation tile1, CardLocation tile2);            
	CardName getCardType(CardLocation location);                                    //Devuelve de que tipo era una carta
        CardLocation getOtherServiceDuctPos(CardLocation secretDoor1);                  //Dada una secret Door, devuelve la posición de la otra.
        CardLocation getComputerRoomLocation(CardName computerRoom);                    //Dada una computer room, devuelve su posición en el tablero
        CardLocation getLavatoryLocation();
        bool isCardUpstairs(CardLocation source, CardLocation destination);
        bool isCardDownstairs(CardLocation source, CardLocation destination);                       
        bool canSafeBeCracked(unsigned int safeFloor);                                              //Si hay por lo menos una carta visible en la misma fila o columna que el safe devuelve true
        list<CardLocation> tilesWithCracked(vector<unsigned int> &dice, unsigned int safeFloor);    //Devuelve todas las cartas que tienen el mismo safe number que algun dado que salio, y estan en misma fila o columna que el safe de su piso
        list<CardLocation> getShortestPath(CardLocation source, CardLocation destination);      //Obtiene el camino más corto entre dos tiles
        unsigned int getShortestPathLength(CardLocation source, CardLocation destination);      //Obtiene el largo del camino más corto entre dos tiles
        void activateMotion();          //Activa el sensor de motion 
        void deActivateMotion();        //Desactiva el sensor de motion
        bool isMotionActivated();
        bool canKittyMove(CardLocation ownerPos);       //FALTA CAMBIAR
        CardLocation getKittyMovingPos(CardLocation ownerPos);      //FALTA CAMBIAR
	~BurgleBrosBoard();
private:
	void sliceVector(std::vector<CardName> &allFloors, std::vector<CardName> *firstFloor, std::vector<CardName> *secondFloor, std::vector<CardName> *thirdFloor);
	void getEachFloorTiles(std::vector<CardName> *firstFloor, std::vector<CardName> *secondFloor, std::vector<CardName> *thirdFloor);
	BurgleBrosFloor floors[BOARD_STANDARD_FLOORS];
        bool motion;
};
#endif
