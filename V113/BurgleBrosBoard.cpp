#include "BurgleBrosBoard.h"
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <algorithm>    // std::shuffle

using namespace std;
typedef struct{
	CardName type;
	unsigned int quantity;
}DeckDetails;




BurgleBrosBoard::BurgleBrosBoard()
{
    initBoard();
}
void BurgleBrosBoard::initBoard()
{
	vector<CardName> firstFloor, secondFloor, thirdFloor;
	getEachFloorTiles(&firstFloor, &secondFloor, &thirdFloor);
	floors[0].initFloor(0, firstFloor);
	floors[1].initFloor(1, secondFloor);
	floors[2].initFloor(2, thirdFloor);
}
void BurgleBrosBoard::initBoard(string startInfo)
{
	vector<CardName> allFloors;
	vector<CardName> firstFloor, secondFloor, thirdFloor;
	startInfoToVector(startInfo, &allFloors);
	sliceVector(allFloors, &firstFloor, &secondFloor, &thirdFloor);
	floors[0].initFloor(0, firstFloor);
	floors[1].initFloor(1, secondFloor);
	floors[2].initFloor(2, thirdFloor);
}
string BurgleBrosBoard::getStartInfo()
{
	unsigned char buffer[BOARD_STANDARD_FLOORS*FLOOR_COLUMNS*FLOOR_RAWS];
	unsigned int len = BOARD_STANDARD_FLOORS*FLOOR_COLUMNS*FLOOR_RAWS;
	string retVal;
	for (unsigned int j = 0; j < BOARD_STANDARD_FLOORS; j++)
	{
		for (unsigned int i = 0; i < FLOOR_COLUMNS*FLOOR_RAWS; i++)
			buffer[j*FLOOR_COLUMNS*FLOOR_RAWS + i] = floors[j].getCardType(i);
	}
	arrayToStrNmbrField(&retVal, buffer, len);
	return retVal;
}
bool BurgleBrosBoard::isAWallBetween(CardLocation tile1, CardLocation tile2)
{
    if(tile1.floor == tile2.floor)
        return floors[tile1.floor].isAWallBetween(tile1, tile2);
    else
        return false;
}
bool BurgleBrosBoard::isMovePossible(CardLocation source, CardRelativeLocation whereToMove)
{
	return floors[source.floor].isMovePossible(source, whereToMove);
}
bool BurgleBrosBoard::isMovePossible(CardLocation source, CardLocation destination)
{
	return floors[source.floor].isMovePossible(source, destination);
}
bool BurgleBrosBoard::isMovePossible(std::string source, std::string destination)
{
	return isMovePossible(protocolToCardLocation(source), protocolToCardLocation(destination));
}
BurgleBrosCard BurgleBrosBoard::getCardCopy(CardLocation location)
{
	return floors[location.floor].getCardCopy(location);
}
BurgleBrosCard BurgleBrosBoard::getCardCopy(std::string location)
{
	return getCardCopy(protocolToCardLocation(location));
}
void BurgleBrosBoard::setCardVisible(CardLocation location)
{
	return floors[location.floor].setCardVisible(location);
}
void BurgleBrosBoard::setCardVisible(std::string location)
{
	return setCardVisible(protocolToCardLocation(location));
}
bool BurgleBrosBoard::isCardVisible(CardLocation location)
{
	return floors[location.floor].isCardVisible(location);
}
bool BurgleBrosBoard::isCardVisible(std::string location)
{
	return isCardVisible(protocolToCardLocation(location));
}
void BurgleBrosBoard::safeCrackedThisCard(CardLocation location)
{
	return floors[location.floor].safeCrackedThisCard(location);
}
void BurgleBrosBoard::safeCrackedThisCard(std::string location)
{
	return safeCrackedThisCard(protocolToCardLocation(location));
}
unsigned int BurgleBrosBoard::getCardSafeNumber(CardLocation location)
{
	return floors[location.floor].getCardSafeNumber(location);
}
unsigned int BurgleBrosBoard::getCardSafeNumber(std::string location)
{
	return getCardSafeNumber(protocolToCardLocation(location));
}
bool BurgleBrosBoard::isCardCracked(CardLocation location)
{
	return floors[location.floor].isCardCracked(location);
}
bool BurgleBrosBoard::isCardCracked(std::string location)
{
	return isCardCracked(protocolToCardLocation(location));
}
CardName BurgleBrosBoard::getCardType(CardLocation location)
{
	return floors[location.floor].getCardType(location);
}
CardName BurgleBrosBoard::getCardType(std::string location)
{
	return getCardType(protocolToCardLocation(location));
}

CardLocation BurgleBrosBoard::getOtherServiceDuctPos(CardLocation secretDoor1)
{
    CardLocation retVal = secretDoor1;
    CardLocation aux;
    CardName auxCardName;
    for(aux.floor=0;aux.floor<BOARD_STANDARD_FLOORS; aux.floor++ )
    {
        for(aux.row=0;aux.row<FLOOR_RAWS; aux.row++ )
        {
            for(aux.column=0;aux.column<FLOOR_COLUMNS; aux.column++ )
            {
                if(floors[aux.floor].getCardType(aux) == SERVICE_DUCT &&  (!(aux==secretDoor1)))
                    retVal=aux;
            }
        }
    }
    return retVal;
}
CardLocation BurgleBrosBoard::getComputerRoomLocation(CardName computerRoom)
{
    CardLocation retVal;
    CardLocation aux;
    for(aux.floor=0;aux.floor<BOARD_STANDARD_FLOORS; aux.floor++ )
    {
        for(aux.row=0;aux.row<FLOOR_RAWS; aux.row++ )
        {
            for(aux.column=0;aux.column<FLOOR_COLUMNS; aux.column++ )
            {
                if(floors[aux.floor].getCardType(aux) == computerRoom)
                    retVal=aux;
            }
        }
    }
    return retVal;
}














void BurgleBrosBoard::startInfoToVector(std::string &startInfo, std::vector<CardName> *cardNames)
{
	unsigned char buffer[BOARD_STANDARD_FLOORS*FLOOR_COLUMNS*FLOOR_RAWS];
	unsigned int length;
	string aux;
	size_t found = startInfo.rfind(',');
	aux = startInfo.substr(0, found);
	strNmbrFieldToArray(aux, buffer, &length);
	for (unsigned int i = 0; i < length; i++)
		cardNames->push_back((CardName)buffer[i]);
}

void BurgleBrosBoard::sliceVector(std::vector<CardName> &allFloors, std::vector<CardName> *firstFloor, std::vector<CardName> *secondFloor, std::vector<CardName> *thirdFloor)
{
	for (unsigned int j = 0; j < allFloors.size(); j++)
	{
		if (j < (allFloors.size() / 3))
			firstFloor->push_back(allFloors[j]);
		else if (j<((2 * allFloors.size()) / 3))
			secondFloor->push_back(allFloors[j]);
		else
			thirdFloor->push_back(allFloors[j]);
	}
}


void BurgleBrosBoard::getEachFloorTiles(vector<CardName> *firstFloor, vector<CardName> *secondFloor, vector<CardName> *thirdFloor)
{
	DeckDetails deck[] = {
		{ ATRIUM, 2 },
		{ CAMERA, 4 },
		{ COMPUTER_ROOM_FINGERPRINT, 1 },
		{ COMPUTER_ROOM_LASER, 1 },
		{ COMPUTER_ROOM_MOTION, 1 },
		{ DEADBOLT, 3 },
		{ FINGERPRINT, 3 },
		{ FOYER, 2 },
		{ KEYPAD, 3 },
		{ LABORATORY, 2 },
		{ LASER, 3 },
		{ LAVATORY, 1 },
		{ MOTION, 3 },
		{ SCANNER_DETECTOR, 3 },
		{ SECRET_DOOR, 2 },
		{ SERVICE_DUCT, 2 },
		{ THERMO, 3 },
		{ WALKAWAY, 3 }
	};
	vector<CardName> auxvector;
	for (unsigned int i = 0; i < (sizeof(deck) / sizeof(DeckDetails)); i++)
	{
		for (unsigned int j = 0; j < deck[i].quantity; j++)
			auxvector.push_back(deck[i].type);
	}
	shuffle(auxvector.begin(), auxvector.end(), default_random_engine(rand()));

	sliceVector(auxvector, firstFloor, secondFloor, thirdFloor);

	firstFloor->push_back(SAFE);
	firstFloor->push_back(STAIR);
	secondFloor->push_back(SAFE);
	secondFloor->push_back(STAIR);
	thirdFloor->push_back(SAFE);
	thirdFloor->push_back(STAIR);

	shuffle(firstFloor->begin(), firstFloor->end(), default_random_engine(rand()));
	shuffle(secondFloor->begin(), secondFloor->end(), default_random_engine(rand()));
	shuffle(thirdFloor->begin(), thirdFloor->end(), default_random_engine(rand()));

}
void BurgleBrosBoard::testBoard()
{
	cout << "Floor 1 ";
	floors[0].testFloor();
	cout << "Floor 2 ";
	floors[1].testFloor();
	cout << "Floor 3 ";
	floors[2].testFloor();
}

BurgleBrosBoard::~BurgleBrosBoard()
{
	

}

CardLocation intToCardLocation(unsigned int cardNumber)
{
	CardLocation retVal;
	retVal.floor = cardNumber / (FLOOR_COLUMNS*FLOOR_COLUMNS);
	retVal.column = cardNumber % FLOOR_COLUMNS;
	retVal.row = (cardNumber % (FLOOR_COLUMNS*FLOOR_COLUMNS)) / FLOOR_COLUMNS;
	return retVal;
}
