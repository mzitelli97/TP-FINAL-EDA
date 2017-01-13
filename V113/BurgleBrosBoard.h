#ifndef BURGLEBROSBOARD_H
#define BURGLEBROSBOARD_H
#include "BurgleBrosFloor.h"
#include <string>
#include "StrNmbrFieldToArray.h"

CardLocation intToCardLocation(unsigned int cardNumber); //si se la llama con 16, devuleve (1,0,0) (piso 1 la primer carta), etc.  0<=i<48

#define BOARD_STANDARD_FLOORS 3

class BurgleBrosBoard
{
public:
	BurgleBrosBoard();
	void initBoard();						//Inicializa el tablero repartiendo las cartas entre los distintos pisos.
	void initBoard(std::string startInfo);	//Inicializa el tablero interpretando el msj "START_INFO" del protocolo.
	std::string getStartInfo();				//Devuelve todos los numeros de tipos de carta en el formato del paquete "START_INFO" sin la ultima coma y sin la posici�n del guardia.
	bool adjacentCards(CardLocation source, CardRelativeLocation whereToMove);
	bool adjacentCards(CardLocation source, CardLocation destination);
	void getWalls(vector<wall> &vector);
	BurgleBrosCard getCardCopy(CardLocation location);
	BurgleBrosCard getCardCopy(std::string location);
	void setCardVisible(CardLocation location);
	void setCardVisible(std::string location);
	bool isCardVisible(CardLocation location);
	bool isCardVisible(std::string location);
	unsigned int getCardSafeNumber(CardLocation location);
	unsigned int getCardSafeNumber(std::string location);
	bool isCardCracked(CardLocation location);  //()
	bool isCardCracked(std::string location);
        bool isSafeCracked(unsigned int floor);
        bool setSafeCracked(unsigned int floor);
        bool isAWallBetween(CardLocation tile1, CardLocation tile2);
	CardName getCardType(CardLocation location);
	CardName getCardType(std::string location);
        CardLocation getOtherServiceDuctPos(CardLocation secretDoor1);
        CardLocation getComputerRoomLocation(CardName computerRoom);
        bool isCardUpstairs(CardLocation source, CardLocation destination);
        bool isCardDownstairs(CardLocation source, CardLocation destination);
        bool canSafeBeCracked(unsigned int safeFloor); //Si están visibles todas las cartas en la misma fila y columna que el safe devuelve true
        list<CardLocation> tilesWithCracked(vector<unsigned int> &dice, unsigned int safeFloor);    //Devuelve todas las cartas que tienen el mismo safe number que algun dado que salio, y estan en misma fila o columna que el safe de su piso
        list<CardLocation> getShortestPath(CardLocation source, CardLocation destination);//DESARROLLAR
        unsigned int getShortestPathLength(CardLocation source, CardLocation destination);//DESARROLLAR
        void activateMotion();
        void deActivateMotion();
        bool isMotionActivated();
	void testBoard();
	~BurgleBrosBoard();
private:
	void sliceVector(std::vector<CardName> &allFloors, std::vector<CardName> *firstFloor, std::vector<CardName> *secondFloor, std::vector<CardName> *thirdFloor);
	void startInfoToVector(std::string &startInfo, std::vector<CardName> *CardNames);
	void getEachFloorTiles(std::vector<CardName> *firstFloor, std::vector<CardName> *secondFloor, std::vector<CardName> *thirdFloor);
	BurgleBrosFloor floors[BOARD_STANDARD_FLOORS];
        bool motion;
};
#endif
