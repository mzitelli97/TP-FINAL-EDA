#include "BurgleBrosFloor.h"
#include <cstring>
#include <limits>
#include <set>

using namespace std;

#define NO_PREVIOUS (-1)

unsigned int indexToInt(CardLocation &i );

BurgleBrosFloor::BurgleBrosFloor(unsigned int whichFloor, std::vector<CardName> &orderedCards)
{
	initFloor(whichFloor, orderedCards);
}
BurgleBrosFloor::BurgleBrosFloor()
{
}
void BurgleBrosFloor::initFloor(unsigned int whichFloor, std::vector<CardName> &orderedCards)
{
	floorNumber = whichFloor;
	if (orderedCards.size() == (FLOOR_RAWS * FLOOR_COLUMNS))
	{
		unsigned int row = 0;
		unsigned int column = 0;
		for (std::vector<CardName>::iterator it = orderedCards.begin(); it != orderedCards.end(); ++it)
		{
			CardLocation auxLocation;
			auxLocation.floor = floorNumber;
			auxLocation.row = row;
			auxLocation.column = column;
			BurgleBrosCard auxCard(*it, auxLocation);
			cards[auxLocation.row][auxLocation.column] = auxCard;
			if (column == (FLOOR_COLUMNS - 1))
			{
				row++;
				column = 0;
			}
			else
				column++;
		}
		linkCards();
	}
        initAdjList();
}
CardLocation BurgleBrosFloor::getSafeLocation()
{
    CardLocation retVal,aux;
    for(aux.row=0; aux.row<FLOOR_RAWS; aux.row++)
    {
        for(aux.column=0;aux.column<FLOOR_COLUMNS;aux.column++)
        {
            CardName name=cards[aux.row][aux.column].getCardType();
            if(name == SAFE)
                retVal=aux;
        }
    }
    retVal.floor=floorNumber;
    return retVal;
}
void BurgleBrosFloor::crackSafe()
{
    CardLocation safePos=getSafeLocation();
    cards[safePos.row][safePos.column].safeCracked();
}
bool BurgleBrosFloor::isSafeCracked()
{
    CardLocation safePos=getSafeLocation();
    return cards[safePos.row][safePos.column].isCracked();
}
void BurgleBrosFloor::getWalls(vector<wall> &vector) 
{
    for(unsigned int i=0; i<NUMBER_OF_WALLS; i++)
        vector.push_back(walls[i]);
}

void BurgleBrosFloor::linkCards()
{
	linkCardsWithoutWalls();
	generateWalls();
	for (unsigned int row = 0; row < FLOOR_RAWS; row++)
	{
		for (unsigned int column = 0; column < FLOOR_COLUMNS; column++)
		{
			for (unsigned int wallNr = 0; wallNr < NUMBER_OF_WALLS; wallNr++)
			{
				if ((row != (FLOOR_RAWS - 1)) && (cards[row][column].getLocation() == walls[wallNr].FrontCard) && (cards[row+1][column].getLocation() == walls[wallNr].RearCard))
				{
					cards[row][column].setNeighboardCard(DOWN_CARD, nullptr);
					cards[row+1][column].setNeighboardCard(UP_CARD, nullptr);
				}
				if ((column != (FLOOR_COLUMNS - 1)) && (cards[row][column].getLocation() == walls[wallNr].FrontCard) && (cards[row][column+1].getLocation() == walls[wallNr].RearCard))
				{
					cards[row][column].setNeighboardCard(RIGHT_CARD, nullptr);
					cards[row][column+1].setNeighboardCard(LEFT_CARD, nullptr);
				}
			}
		}
	}
}
void BurgleBrosFloor::linkCardsWithoutWalls()
{
	for (unsigned int row = 0; row < FLOOR_RAWS; row++)
	{
		for (unsigned int column = 0; column < FLOOR_COLUMNS; column++)
		{
			if (row == 0 && column == 0)													//Esquina izq sup
				cards[row][column].setNeighboardCards(nullptr, &(cards[row+1][column]), &(cards[row][column+1]), nullptr);
			else if (row == 0 && column == FLOOR_COLUMNS-1)									//Esquina der sup
				cards[row][column].setNeighboardCards(&(cards[row][column-1]), &(cards[row+1][column]), nullptr, nullptr);
			else if (row == FLOOR_RAWS-1 && column == 0)									//Esquina izq inf
				cards[row][column].setNeighboardCards(nullptr, nullptr, &(cards[row][column+1]), &(cards[row-1][column]));
			else if (row == FLOOR_RAWS - 1 && column == FLOOR_COLUMNS-1)					//Esquina der inf
				cards[row][column].setNeighboardCards(&(cards[row][column-1]), nullptr, nullptr, &(cards[row-1][column]));
			else if (row == 0)																//Banda superior
				cards[row][column].setNeighboardCards(&(cards[row][column-1]), &(cards[row+1][column]), &(cards[row][column+1]), nullptr);
			else if (column == 0)															//Banda izquierda
				cards[row][column].setNeighboardCards(nullptr, &(cards[row+1][column]), &(cards[row][column+1]), &(cards[row-1][column]));
			else if (column == FLOOR_COLUMNS-1)												//Banda derecha
				cards[row][column].setNeighboardCards(&(cards[row][column-1]), &(cards[row+1][column]), nullptr, &(cards[row-1][column]));
			else if (row == FLOOR_RAWS-1)													//Banda inferior
				cards[row][column].setNeighboardCards(&(cards[row][column-1]), nullptr, &(cards[row][column+1]), &(cards[row-1][column]));
			else																			//Centro del piso
				cards[row][column].setNeighboardCards(&(cards[row][column-1]), &(cards[row+1][column]), &(cards[row][column+1]), &(cards[row-1][column]));
		}
	}
}
void BurgleBrosFloor::generateWalls()
{
	if (floorNumber == 0)
	{
		wall wallTemp[] = { 
			{ { floorNumber, 0, 0 }, { floorNumber, 0, 1 } },
			{ { floorNumber, 0, 2 }, { floorNumber, 1, 2 } },
			{ { floorNumber, 1, 0 }, { floorNumber, 2, 0 } },
			{ { floorNumber, 1, 1 }, { floorNumber, 2, 1 } },
			{ { floorNumber, 1, 2 }, { floorNumber, 1, 3 } },
			{ { floorNumber, 2, 3 }, { floorNumber, 3, 3 } },
			{ { floorNumber, 3, 0 }, { floorNumber, 3, 1 } },
			{ { floorNumber, 3, 1 }, { floorNumber, 3, 2 } }
		};
		std::memcpy(walls, wallTemp, sizeof(wallTemp));
	}
	else if (floorNumber == 1)
	{
		wall wallTemp[] = { 
			{ { floorNumber, 0, 0 }, { floorNumber, 0, 1 } },
			{ { floorNumber, 0, 1 }, { floorNumber, 0, 2 } },
			{ { floorNumber, 0, 2 }, { floorNumber, 0, 3 } },
			{ { floorNumber, 1, 1 }, { floorNumber, 2, 1 } },
			{ { floorNumber, 1, 2 }, { floorNumber, 2, 2 } },
			{ { floorNumber, 3, 0 }, { floorNumber, 3, 1 } },
			{ { floorNumber, 3, 1 }, { floorNumber, 3, 2 } },
			{ { floorNumber, 3, 2 }, { floorNumber, 3, 3 } }
		};
		std::memcpy(walls, wallTemp, sizeof(wallTemp));
	}
	else if (floorNumber == 2)
	{
		wall wallTemp[] = {
			{ { floorNumber, 0, 2 }, { floorNumber, 1, 2 } },
			{ { floorNumber, 1, 0 }, { floorNumber, 1, 1 } },
			{ { floorNumber, 1, 0 }, { floorNumber, 2, 0 } },
			{ { floorNumber, 1, 2 }, { floorNumber, 1, 3 } },
			{ { floorNumber, 1, 2 }, { floorNumber, 2, 2 } },
			{ { floorNumber, 2, 0 }, { floorNumber, 2, 1 } },
			{ { floorNumber, 2, 1 }, { floorNumber, 2, 2 } },
			{ { floorNumber, 3, 2 }, { floorNumber, 3, 3 } }
		};
		std::memcpy(walls, wallTemp, sizeof(wallTemp));
	}
}

void BurgleBrosFloor::initAdjList()
{
    vector<unsigned int> aux;
    adjacentList.reserve(FLOOR_COLUMNS * FLOOR_RAWS);
    for(unsigned int i=0; i < FLOOR_COLUMNS * FLOOR_RAWS; i++)
        adjacentList.push_back(aux);
    unsigned int count;
    vector<vector<unsigned int>>::iterator tileIt;
    for(tileIt = adjacentList.begin(), count=0;tileIt!=adjacentList.end(); tileIt++,count++ )
    {
        if(cards[count/FLOOR_COLUMNS][count%FLOOR_COLUMNS].hasNeighboard(RIGHT_CARD))
            tileIt->push_back(count+1);
        if(cards[count/FLOOR_COLUMNS][count%FLOOR_COLUMNS].hasNeighboard(DOWN_CARD))
            tileIt->push_back(count+FLOOR_COLUMNS);
        if(cards[count/FLOOR_COLUMNS][count%FLOOR_COLUMNS].hasNeighboard(LEFT_CARD))
            tileIt->push_back(count-1);
        if(cards[count/FLOOR_COLUMNS][count%FLOOR_COLUMNS].hasNeighboard(UP_CARD))
            tileIt->push_back(count-FLOOR_COLUMNS);
    }
}

bool BurgleBrosFloor::isAWallBetween(CardLocation tile1, CardLocation tile2)
{
    bool retVal=false;
    for(unsigned int i=0; i< NUMBER_OF_WALLS ; i++)
    {
        if(walls[i].FrontCard == tile1 && walls[i].RearCard == tile2)
            retVal = true;
        else if(walls[i].FrontCard == tile2 && walls[i].RearCard == tile1)
            retVal = true;
    }
    return retVal;
}

bool BurgleBrosFloor::areTilesAdjacent(CardLocation source, CardRelativeLocation whereToMove)
{
	return cards[source.row][source.column].hasNeighboard(whereToMove);
}
bool BurgleBrosFloor::areTilesAdjacent(CardLocation source, CardLocation destination)
{
	return cards[source.row][source.column].isNeighboard(destination);
}
void BurgleBrosFloor::setCardVisible(CardLocation location)
{
	cards[location.row][location.column].setVisible();
}
bool BurgleBrosFloor::isCardVisible(CardLocation location)
{
	return cards[location.row][location.column].isVisible();
}
unsigned int BurgleBrosFloor::getCardSafeNumber(CardLocation location)
{
	return cards[location.row][location.column].getSafeNumber();
}
CardName BurgleBrosFloor::getCardType(CardLocation location)
{
	return cards[location.row][location.column].getCardType();
}
CardName BurgleBrosFloor::getCardType(unsigned int number)
{
	return getCardType(intToIndex(number));
}
CardLocation BurgleBrosFloor::intToIndex(unsigned int i)
{
	CardLocation aux;
	aux.floor = floorNumber;
	aux.column = i%FLOOR_COLUMNS;
	aux.row = i / FLOOR_RAWS;
	return aux;
}

list<CardLocation> BurgleBrosFloor::getShortestPath(CardLocation source, CardLocation destination)
{
    vector<unsigned int> minDist;
    vector<int> prevCard;
    unsigned int auxCard = indexToInt(destination);
    list<CardLocation> retVal;
    computeDijkstra(indexToInt(source), indexToInt(destination), minDist, prevCard);
    
    for ( ; auxCard != NO_PREVIOUS; auxCard = prevCard[auxCard])
    {    
        CardLocation temp = {floorNumber, auxCard/FLOOR_COLUMNS,auxCard%FLOOR_COLUMNS};
        retVal.push_front(temp);
    }
    return retVal;
}
/* Creditos de la función a https://rosettacode.org/wiki/Dijkstra%27s_algorithm#C.2B.2B*/
 void BurgleBrosFloor::computeDijkstra(unsigned int sourceCard, unsigned int destinationCard,vector<unsigned int> &minDist,vector<int> &prevCard)
 {
    int numberOfCards = FLOOR_RAWS * FLOOR_COLUMNS; //El numero de cartas siempre es fijo
    bool pathToTargetObtained=false;
    minDist.clear();                       
    minDist.resize(numberOfCards, std::numeric_limits<int>::max());      //Pongo todas las etiquetas de djikstra en infinito, como trabajo con ints, le pongo max.
    minDist[sourceCard] = 0;                                        //La distancia desde el vertice que partí hacia si mismo es 0.
    prevCard.clear();                               
    prevCard.resize(numberOfCards, NO_PREVIOUS);
    set<pair<unsigned int, int> > cardQueue;
    cardQueue.insert(make_pair(minDist[sourceCard], sourceCard));  //Parto del vértice sourceCard.
    while (!pathToTargetObtained && !cardQueue.empty())             
    {
        unsigned int dist = cardQueue.begin()->first;
        int A = cardQueue.begin()->second;
        cardQueue.erase(cardQueue.begin());
        vector<unsigned int> &neighbors = adjacentList[A];
        vector<unsigned int>::iterator neighbor_iter = neighbors.begin();
        for (neighbor_iter = neighbors.begin();neighbor_iter != neighbors.end();neighbor_iter++)
        {
            
            unsigned int B = *neighbor_iter;
            unsigned int totalDist = dist + 1; //El peso de entre dos vértices siempre es 1 para nuestro grafo.
            if (totalDist < minDist[B]) {
	        cardQueue.erase(std::make_pair(minDist[B], B));
 
	        minDist[B] = totalDist;
	        prevCard[B] = A;
	        cardQueue.insert(std::make_pair(minDist[B], B));
                if(B==destinationCard)
                {
                    pathToTargetObtained=true;
                    break;
                }
	    }
        }
    }
 }
unsigned int indexToInt(CardLocation &i )
{
    return i.row*FLOOR_COLUMNS+i.column;
}
CardLocation BurgleBrosFloor::getKittyMovingPos(CardLocation playerPos)
{
    unsigned int sourceCard = indexToInt(playerPos);
    vector<unsigned int> minDist;
    vector<int> prevCard;
    CardLocation target;
    list<CardLocation> path;
    int numberOfCards = FLOOR_RAWS * FLOOR_COLUMNS; //El numero de cartas siempre es fijo
    bool pathToTargetObtained=false;
    minDist.clear();                       
    minDist.resize(numberOfCards, std::numeric_limits<int>::max());      //Pongo todas las etiquetas de djikstra en infinito, como trabajo con ints, le pongo max.
    minDist[sourceCard] = 0;                                        //La distancia desde el vertice que partí hacia si mismo es 0.
    prevCard.clear();                               
    prevCard.resize(numberOfCards, NO_PREVIOUS);
    set<pair<unsigned int, int> > cardQueue;
    cardQueue.insert(make_pair(minDist[sourceCard], sourceCard));  //Parto del vértice sourceCard.
    int auxCard;
    while (!pathToTargetObtained && !cardQueue.empty())             
    {
        unsigned int dist = cardQueue.begin()->first;
        int A = cardQueue.begin()->second;
        cardQueue.erase(cardQueue.begin());
        vector<unsigned int> &neighbors = adjacentList[A];
        vector<unsigned int>::iterator neighbor_iter = neighbors.begin();
        for (neighbor_iter = neighbors.begin();neighbor_iter != neighbors.end();neighbor_iter++)
        {
            
            unsigned int B = *neighbor_iter;
            unsigned int totalDist = dist + 1; //El peso de entre dos vértices siempre es 1 para nuestro grafo.
            if (totalDist < minDist[B]) {
	        cardQueue.erase(std::make_pair(minDist[B], B));
 
	        minDist[B] = totalDist;
	        prevCard[B] = A;
	        cardQueue.insert(std::make_pair(minDist[B], B));
                CardLocation aux= intToIndex(B);
                aux.floor=floorNumber;
                if(isAnAlarmTile(getCardType(aux)) && aux!= playerPos)
                {
                    auxCard = B;
                    pathToTargetObtained=true;
                    target=aux;
                    break;
                }
	    }
        }
    }
    
    for ( ; auxCard != NO_PREVIOUS; auxCard = prevCard[auxCard])
    {    
        CardLocation temp = {floorNumber, (unsigned int)auxCard/FLOOR_COLUMNS,(unsigned int)auxCard%FLOOR_COLUMNS};
        path.push_front(temp);
    }
    path.pop_front(); // Desecho la carta de la que partió
    return path.front();    //Devuelvo para el primer tile que se mueve.
}

BurgleBrosFloor::~BurgleBrosFloor()
{
}
