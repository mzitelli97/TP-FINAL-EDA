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
    motion=false;
    vector<CardName> firstFloor, secondFloor, thirdFloor;
    getEachFloorTiles(&firstFloor, &secondFloor, &thirdFloor);
    //firstFloor[0]=MOTION;
    //firstFloor[5]=LASER;
    floors[0].initFloor(0, firstFloor);
    floors[1].initFloor(1, secondFloor);
    floors[2].initFloor(2, thirdFloor);
}
bool BurgleBrosBoard::isAWallBetween(CardLocation tile1, CardLocation tile2)
{
    if(tile1.floor == tile2.floor)
        return floors[tile1.floor].isAWallBetween(tile1, tile2);
    else
        return false;
}
bool BurgleBrosBoard::adjacentCards(CardLocation source, CardRelativeLocation whereToMove)
{
	return floors[source.floor].areTilesAdjacent(source, whereToMove);
}
bool BurgleBrosBoard::adjacentCards(CardLocation source, CardLocation destination)
{
	return floors[source.floor].areTilesAdjacent(source, destination);
}

void BurgleBrosBoard::getWalls(vector<wall> &vector)
{
    for(unsigned int i=0;i <BOARD_STANDARD_FLOORS; i++)
        floors[i].getWalls(vector);
}
void BurgleBrosBoard::setCardVisible(CardLocation location)
{
	return floors[location.floor].setCardVisible(location);
}
bool BurgleBrosBoard::isCardVisible(CardLocation location)
{
	return floors[location.floor].isCardVisible(location);
}
unsigned int BurgleBrosBoard::getCardSafeNumber(CardLocation location)
{
	return floors[location.floor].getCardSafeNumber(location);
}
CardName BurgleBrosBoard::getCardType(CardLocation location)
{
	return floors[location.floor].getCardType(location);
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

list<CardLocation> BurgleBrosBoard::getShortestPath(CardLocation source, CardLocation destination)
{
    list<CardLocation> retVal;
    if(source.floor == destination.floor && source.floor <BOARD_STANDARD_FLOORS)
    {
        retVal= floors[source.floor].getShortestPath(source, destination);
        retVal.pop_front(); //Borro el primer elemento del camino ya que es igual al source
    }
    return retVal;
}
unsigned int BurgleBrosBoard::getShortestPathLength(CardLocation source, CardLocation destination)
{
    list<CardLocation> aux;
    if(source.floor == destination.floor && source.floor <BOARD_STANDARD_FLOORS)
    {
        aux = floors[source.floor].getShortestPath(source, destination);
        aux.pop_front();    //Borro el primer elemento del camino ya que es igual al source
    }
    return aux.size();
}
list<CardLocation>  BurgleBrosBoard::tilesWithCracked(vector<unsigned int> &dice, unsigned int safeFloor)
{
    list<CardLocation> retVal;
    CardLocation safePos=floors[safeFloor].getSafeLocation();
    CardLocation aux;
    for(vector<unsigned int>::iterator it=dice.begin(); it!=dice.end(); it++)   //Para cada dado
    {
        if(*it != 0)            //Si cada dado es distinto de 0
        {
            aux=safePos;
            for(aux.row=0; aux.row < FLOOR_RAWS; aux.row++) //Recorro toda la fila en la que esta el safe
            {
                if(floors[safePos.floor].getCardType(aux) != SAFE && isCardVisible(aux) && floors[safePos.floor].getCardSafeNumber(aux) == *it)  //Si hay una carta que tiene el mismo safe number que el dado se pushea
                    retVal.push_back(aux);
            }
            aux.row=safePos.row;
            for(aux.column=0; aux.column < FLOOR_COLUMNS; aux.column++)//Recorro toda la columna en la que esta el safe
            {
                if(floors[safePos.floor].getCardType(aux) != SAFE && isCardVisible(aux) && floors[safePos.floor].getCardSafeNumber(aux) == *it) //Si hay una carta que tiene el mismo safe number que el dado se pushea
                    retVal.push_back(aux);
            }
        }
    }
    return retVal;
}
bool BurgleBrosBoard::canSafeBeCracked(unsigned int safeFloor)
{
    bool retVal=false;
    CardLocation safePos=floors[safeFloor].getSafeLocation();
    CardLocation aux;
    aux=safePos;
    /*
    bool retVal=true;
    if(!floors[safePos.floor].isCardVisible(safePos))   //Si no esta visible la safe tampoco se puede crackear
        retVal=false;
    for(aux.row=0; aux.row < FLOOR_RAWS; aux.row++) //Recorro toda la fila en la que esta el safe
    {
        if(floors[safePos.floor].getCardType(aux) != SAFE && (!floors[safePos.floor].isCardVisible(aux)))  
            retVal=false;
    }
    aux.row=safePos.row;
    for(aux.column=0; aux.column < FLOOR_COLUMNS; aux.column++)//Recorro toda la columna en la que esta el safe
    {
        if(floors[safePos.floor].getCardType(aux) != SAFE && (!floors[safePos.floor].isCardVisible(aux)))  
            retVal=false;
    }*/
    for(aux.row=0; aux.row < FLOOR_RAWS; aux.row++) //Recorro toda la fila en la que esta el safe
    {
        if(floors[safePos.floor].getCardType(aux) != SAFE && floors[safePos.floor].isCardVisible(aux))  
            retVal=true;
    }
    aux.row=safePos.row;
    for(aux.column=0; aux.column < FLOOR_COLUMNS; aux.column++)//Recorro toda la columna en la que esta el safe
    {
        if(floors[safePos.floor].getCardType(aux) != SAFE && floors[safePos.floor].isCardVisible(aux))  
            retVal=true;
    }
    if(!floors[safePos.floor].isCardVisible(safePos))   //Si no esta visible la safe tampoco se puede crackear
        retVal=false;
    return retVal;
}
bool BurgleBrosBoard::isSafeCracked(unsigned int floor)
{
    return floors[floor].isSafeCracked();
}
bool BurgleBrosBoard::setSafeCracked(unsigned int floor)
{
    floors[floor].crackSafe();
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

bool BurgleBrosBoard:: isCardUpstairs(CardLocation source, CardLocation destination)
{
    bool retVal=false;
    if(source.floor<2)
    {
        source.floor++;
        if(source==destination)
            retVal=true;
    }
    return retVal;
}

bool BurgleBrosBoard::  isCardDownstairs(CardLocation source, CardLocation destination)
{
    bool retVal=false;
    if(source.floor>0)
    {
        source.floor--;
        if(source==destination)
            retVal=true;
    }
    return retVal;
}

void BurgleBrosBoard::activateMotion() 
{
    motion=true;
}

void BurgleBrosBoard::deActivateMotion() 
{
    motion=false;
}

bool BurgleBrosBoard::isMotionActivated() 
{
    return motion;
}
bool BurgleBrosBoard::canKittyMove(CardLocation ownerPos)
{
    bool retVal=false;
    CardLocation aux;
    aux.floor= ownerPos.floor;
    for(aux.row=0; aux.row<FLOOR_RAWS; aux.row++)
    {
        for(aux.column=0; aux.column<FLOOR_RAWS; aux.column++)
        {
            if(isAnAlarmTile(getCardType(aux)) && ownerPos!=aux)    //Si hay una tile de alarma en el piso y no es en la que está parado el chabon
                retVal=true;
        }
    }
    return retVal;
}

CardLocation BurgleBrosBoard::getKittyMovingPos(CardLocation ownerPos)
{
    return floors[ownerPos.floor].getKittyMovingPos(ownerPos);
}
