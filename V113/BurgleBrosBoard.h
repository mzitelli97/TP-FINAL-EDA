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
        bool isMovePossible(CardLocation source, CardRelativeLocation whereToMove);
	bool isMovePossible(CardLocation source, CardLocation destination);
	bool isMovePossible(std::string source, std::string destination);
	BurgleBrosCard getCardCopy(CardLocation location);
	BurgleBrosCard getCardCopy(std::string location);
        bool neighbours(CardLocation cardA,CardLocation cardB);//Desarrollar
	void setCardVisible(CardLocation location);
	void setCardVisible(std::string location);
	bool isCardVisible(CardLocation location);
	bool isCardVisible(std::string location);
	void safeCrackedThisCard(CardLocation location);
	void safeCrackedThisCard(std::string location);
	unsigned int getCardSafeNumber(CardLocation location);
	unsigned int getCardSafeNumber(std::string location);
	bool isCardCracked(CardLocation location);
	bool isCardCracked(std::string location);
        bool isAWallBetween(CardLocation tile1, CardLocation tile2);
	CardName getCardType(CardLocation location);
	CardName getCardType(std::string location);
        CardLocation getOtherServiceDuctPos(CardLocation secretDoor1);
        CardLocation getComputerRoomLocation(CardName computerRoom);
        bool isCardUpstairs(CardLocation source, CardLocation destination);
        bool isCardDownstairs(CardLocation source, CardLocation destination);
        list<CardLocation> getShortestPath(CardLocation source, CardLocation destination);//DESARROLLAR
        unsigned int getShortestPathLength(CardLocation source, CardLocation destination);//DESARROLLAR
	void testBoard();
	~BurgleBrosBoard();
private:
	void sliceVector(std::vector<CardName> &allFloors, std::vector<CardName> *firstFloor, std::vector<CardName> *secondFloor, std::vector<CardName> *thirdFloor);
	void startInfoToVector(std::string &startInfo, std::vector<CardName> *CardNames);
	void getEachFloorTiles(std::vector<CardName> *firstFloor, std::vector<CardName> *secondFloor, std::vector<CardName> *thirdFloor);
	BurgleBrosFloor floors[BOARD_STANDARD_FLOORS];
};
#endif
