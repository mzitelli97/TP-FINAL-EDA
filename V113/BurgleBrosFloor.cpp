#include "BurgleBrosFloor.h"
#include <cstring>
#include <limits>
#include <set>

using namespace std;

#define NO_PREVIOUS (-1)

std::string testFunction(bool yesOrNo);
std::string testFunction2(CardName entry);
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

bool BurgleBrosFloor::isMovePossible(CardLocation source, CardRelativeLocation whereToMove)
{
	return cards[source.row][source.column].hasNeighboard(whereToMove);
}
bool BurgleBrosFloor::isMovePossible(CardLocation source, CardLocation destination)
{
	return cards[source.row][source.column].isNeighboard(destination);
}
bool BurgleBrosFloor::isMovePossible(std::string source, std::string destination)
{
	return isMovePossible(protocolToCardLocation(source), protocolToCardLocation(destination));
}
BurgleBrosCard BurgleBrosFloor::getCardCopy(CardLocation location)
{
	return cards[location.row][location.column];
}
void BurgleBrosFloor::setCardVisible(CardLocation location)
{
	cards[location.row][location.column].setVisible();
}
bool BurgleBrosFloor::isCardVisible(CardLocation location)
{
	return cards[location.row][location.column].isVisible();
}
void BurgleBrosFloor::safeCrackedThisCard(CardLocation location)
{
	cards[location.row][location.column].safeCracked();
}
unsigned int BurgleBrosFloor::getCardSafeNumber(CardLocation location)
{
	return cards[location.row][location.column].getSafeNumber();
}
bool BurgleBrosFloor::isCardCracked(CardLocation location)
{
	return cards[location.row][location.column].isCracked();
}
CardName BurgleBrosFloor::getCardType(CardLocation location)
{
	return cards[location.row][location.column].getCardType();
}
CardName BurgleBrosFloor::getCardType(unsigned int number)
{
	return getCardType(intToIndex(number));
}

void BurgleBrosFloor::testFloor()
{
	std::cout << "Its going to show the possible moves in the current floor: " << std::endl;
	for (unsigned int row = 0; row < FLOOR_RAWS; row++)
	{
		for (unsigned int column = 0; column < FLOOR_COLUMNS; column++)
		{
			std::cout << "Card nmbr " << (row*FLOOR_RAWS + column + 1) << " type " << testFunction2(cards[row][column].getCardType()).c_str();
			std::cout << " To Left: " << testFunction(cards[row][column].hasNeighboard(LEFT_CARD)).c_str();
			std::cout << " To Down: " << testFunction(cards[row][column].hasNeighboard(DOWN_CARD)).c_str();
			std::cout << " To Right: " << testFunction(cards[row][column].hasNeighboard(RIGHT_CARD)).c_str();
			std::cout << " To Up: " << testFunction(cards[row][column].hasNeighboard(UP_CARD)).c_str() << std::endl;
		}
	}
}

std::string testFunction(bool entry)
{
	if (entry == true)
		return "YES";
	else
		return "NO";
}
std::string testFunction2(CardName entry)
{
	switch (entry)
	{
		case ATRIUM: return "Atrium";
		case CAMERA: return "CAMERA";
		case COMPUTER_ROOM_FINGERPRINT: return "COMPUTER_ROOM_FINGERPRINT";
		case COMPUTER_ROOM_LASER: return "COMPUTER_ROOM_LASER";
		case COMPUTER_ROOM_MOTION: return "COMPUTER_ROOM_MOTION";
		case DEADBOLT: return "DEADBOLT";
		case FINGERPRINT: return "FINGERPRINT";
		case FOYER: return "FOYER";
		case KEYPAD: return "KEYPAD";
		case LABORATORY: return "Atrium";
		case LASER: return "CAMERA";
		case LAVATORY: return "LAVATORY";
		case MOTION: return "MOTION";
		case SAFE: return "SAFE";
		case SCANNER_DETECTOR: return "SCANNER_DETECTOR";
		case SECRET_DOOR: return "SECRET_DOOR";
		case SERVICE_DUCT: return "SERVICE_DUCT";
		case STAIR: return "STAIR";
		case THERMO: return "THERMO";
		case WALKAWAY: return "WALKAWAY";
		case GUARD_CARD: return "GUARD_CARD";
		default: return "Error";
	}
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

BurgleBrosFloor::~BurgleBrosFloor()
{
}
