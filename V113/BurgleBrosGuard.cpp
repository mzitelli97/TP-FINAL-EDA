#include "BurgleBrosGuard.h"
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <algorithm>    // std::shuffle


static void list2Vector(list<CardLocation> &list, vector<CardLocation> &vector);
static void vector2List(vector<CardLocation> &vector, list<CardLocation> &list );

BurgleBrosGuard::BurgleBrosGuard()
{
    initialized=false;
}
bool BurgleBrosGuard::step()
{
    bool retVal=false;
    position=pathToTarget.front();
    if(position== currentTarget)
        retVal=true;
    pathToTarget.pop_front();
    return retVal;
}
void BurgleBrosGuard::setNewTarget(CardLocation alarm)
{
    currentTarget=alarm;
}
void BurgleBrosGuard::setNewPathToTarget(list<CardLocation> &pathToTarget)
{
    this->pathToTarget=pathToTarget;
}
bool BurgleBrosGuard::checkIfInitialized()
{
    return initialized;
}
BurgleBrosGuard::BurgleBrosGuard(unsigned int floor)
{
    this->floor=floor;
    if(floor==0)
        diceNumber=FLOOR_1_INIT_DICE;
    else if(floor==1)
        diceNumber=FLOOR_2_INIT_DICE;
    else if(floor==2)
        diceNumber=FLOOR_3_INIT_DICE;
    initialized=false;
    initCardDeck();
    isGuardsTurn=false;
    
    diceNumber = 2+floor;
}

void BurgleBrosGuard::init() 
{
    initialized=true;
    position = drawCardTarget();            //Toma una carta objetivo, allí se posicionara el guard
    currentTarget = drawCardTarget();       //La siguiente carta objetivo es hacia donde se dirige.
}


void BurgleBrosGuard::setPosition(string initialGPos)
{
    string guardPosition=initialGPos.substr(0,4);
    string guardDicePosition=initialGPos.substr(4,4);
    drawCardTarget(protocolToCardLocation(guardDicePosition));
    position=protocolToCardLocation(guardPosition);
}

void BurgleBrosGuard::setPosition(CardLocation location)
{
    position=location;
}
void BurgleBrosGuard::setPosition()
{
    position=getRandomCardLocation(floor);
    CardLocation aux;
    do{
        aux=getRandomCardLocation(floor);
    }while(aux==position);
    drawCardTarget(aux);
}
string BurgleBrosGuard::getInitGPos()
{
    return cardLocationToProtocol(position) + cardLocationToProtocol(*(shownDeck.begin()));
}

CardLocation BurgleBrosGuard::getTopCard()
{
    return *(cardDeck.begin());
}
unsigned int BurgleBrosGuard::getDiceNumber()
{
    return diceNumber;
}
CardLocation BurgleBrosGuard::getTargetPosition()
{
    return currentTarget;
}
CardLocation BurgleBrosGuard::getPosition()
{
    return position;
}
list<CardLocation> BurgleBrosGuard::getShownDeck()
{
    return shownDeck;
}

BurgleBrosGuard::~BurgleBrosGuard()
{
    
}
void BurgleBrosGuard::initCardDeck()
{
    CardLocation aux;
    cardDeck.clear();
    shownDeck.clear();
    aux.floor=floor;
    for(aux.row=0; aux.row < FLOOR_RAWS; aux.row++)
    {
        for(aux.column=0; aux.column < FLOOR_COLUMNS; aux.column++)
        {
            cardDeck.push_back(aux);
        }
    }
    shuffleCardDeck();
}

CardLocation BurgleBrosGuard::drawCardTarget()
{
    list<CardLocation>::iterator it = cardDeck.begin();
    CardLocation aux = *it;
    cardDeck.pop_front();
    shownDeck.push_front(aux);
    currentTarget = aux;
    return aux;
}
bool BurgleBrosGuard::drawCardTarget(CardLocation targetCard)
{
    bool retVal=false;
    list<CardLocation>::iterator it;
    list<CardLocation>::iterator auxIt;
    for(it=cardDeck.begin(); it!=cardDeck.end();it++)
    {
        if(*it == targetCard)
        {
            CardLocation aux = *it;
            auxIt=it;
            shownDeck.push_front(aux);
            currentTarget = aux;
            retVal=true;
        }
    }
    cardDeck.erase(auxIt);
    return retVal;
}

void BurgleBrosGuard::shuffleCardDeck()
{
    vector<CardLocation> aux;
    list2Vector(cardDeck, aux);
    shuffle(aux.begin(), aux.end(), default_random_engine(rand()));
    vector2List(aux, cardDeck);
}
static void list2Vector(list<CardLocation> &mylist, vector<CardLocation> &myvector)
{
    myvector.clear();
    myvector.reserve(mylist.size());
    list<CardLocation>::iterator it;
    for (it=mylist.begin(); it != mylist.end(); ++it)
        myvector.push_back(*it);     
}
static void vector2List(vector<CardLocation> &myvector, list<CardLocation> &mylist )
{
    mylist.clear();
    for (vector<CardLocation>::iterator it=myvector.begin(); it != myvector.end(); ++it)
        mylist.push_back(*it); 
}