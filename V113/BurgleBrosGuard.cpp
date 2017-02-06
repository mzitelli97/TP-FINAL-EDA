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
    topOfNotShownDeckVisible=false;
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
    topOfNotShownDeckVisible=false;
    diceNumber = 2+floor;
}

void BurgleBrosGuard::setTopOfNotShownDeckVisible(bool whichState)
{
    topOfNotShownDeckVisible=whichState;
}
bool BurgleBrosGuard::isTopOfNotShownDeckVisible()
{
    return topOfNotShownDeckVisible;
}


void BurgleBrosGuard::pushTopCardToTheBottom()
{/*Si la carta estaba en el top del mazo ( posición cero) va hacia su nueva posición, que depende de con cuantas cartas estemos jugando:*/
    unsigned int newPos = NUMBER_OF_CARDS_TO_PLAY-shownDeck.size(); //Por ejemplo si saqué 6 cartas, jugabamos con 10, su posición nueva va a ser la 4:
    CardLocation topCard = cardDeck.front();
    list<CardLocation>::iterator it=cardDeck.begin();
    advance(it,newPos);
    cardDeck.insert(it, topCard);
    cardDeck.pop_front();
    cardSincronized.push_back(topCard);
}   
void BurgleBrosGuard::pushCardToTheBottom(CardLocation thisCard)
{/*Si la carta estaba en el top del mazo ( posición cero) va hacia su nueva posición, que depende de con cuantas cartas estemos jugando:*/
    unsigned int newPos = NUMBER_OF_CARDS_TO_PLAY-shownDeck.size(); //Por ejemplo si saqué 6 cartas, jugabamos con 10, su posición nueva va a ser la 4:
    list<CardLocation>::iterator it1;
    for(it1=cardDeck.begin(); it1!=cardDeck.end();it1++)        //busco la carta del deck 
    {
        if(*it1 == thisCard)
            break;
    }
    cardDeck.erase(it1);       //La borro
    list<CardLocation>::iterator it=cardDeck.begin();
    advance(it,newPos);
    cardDeck.insert(it, thisCard);       //La pongo en el supuesto fondo del mazo
    cardSincronized.push_back(thisCard);
}   
void BurgleBrosGuard::pushCardToTheTop(CardLocation thisCard)
{
    unsigned int newPos = NUMBER_OF_CARDS_TO_PLAY-shownDeck.size(); //Por ejemplo si saqué 6 cartas, jugabamos con 10, su posición nueva va a ser la 4:
    list<CardLocation>::iterator it1;
    for(it1=cardDeck.begin(); it1!=cardDeck.end();it1++)        //busco la carta del deck 
    {
        if(*it1 == thisCard)
            break;
    }
    cardDeck.erase(it1);       //La borro
    cardDeck.push_front(thisCard);
    cardSincronized.push_back(thisCard);
}
void BurgleBrosGuard::init() 
{
    initialized=true;
    position = drawCardTarget();            //Toma una carta objetivo, allí se posicionara el guard
    currentTarget = drawCardTarget();       //La siguiente carta objetivo es hacia donde se dirige.
}
void BurgleBrosGuard::init(CardLocation guardPos, CardLocation diePos) 
{
    initialized=true;
    position = guardPos;
    currentTarget= diePos;
    drawCardTarget(guardPos);            //Toma una carta objetivo, allí se posicionara el guard
    drawCardTarget(diePos);       //La siguiente carta objetivo es hacia donde se dirige.
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
void BurgleBrosGuard::incDiceNumber()
{
    if(diceNumber < 6)
        diceNumber++;
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
    CardLocation aux;
    if(shownDeck.size() == NUMBER_OF_CARDS_TO_PLAY) //Si me falta 1 para usar todas las cartas con las que estoy jugando ( 10 para 2 personas) se baraja de vuelta al sacar la primera
    {    
        aux=cardDeck.front();            //Guardo la primera.
        initCardDeck();                             //Barajo de vuelta y saco esa carta que antes era la que quedaba.
        drawCardTarget(aux);
        currentTarget = aux;
        incDiceNumber();    
    }
    else            //Sino, agarro la primera del cardDeck y se la pongo al shownDeck.
    {
        aux = cardDeck.front();
        cardDeck.pop_front();
        shownDeck.push_front(aux);
        currentTarget = aux;
    }
    for(list<CardLocation>::iterator sincronizedCards=cardSincronized.begin(); sincronizedCards!=cardSincronized.end(); sincronizedCards++) //si no era la que saqué, recorro las cartas sincronizadas,
    {
        if(aux==*sincronizedCards)      //Me fijo si era una de las cartas que estaban sincronizadas.
        {
            cardSincronized.erase(sincronizedCards);    //EN ese caso la borro.
            break;
        }
    }
    return aux;
}
bool BurgleBrosGuard::drawCardTarget(CardLocation targetCard)
{
    bool retVal=false;
    list<CardLocation>::iterator it;
    list<CardLocation>::iterator auxIt;
    CardLocation aux;
    if(shownDeck.size() == NUMBER_OF_CARDS_TO_PLAY) //Si me falta 1 para usar todas las cartas con las que estoy jugando ( 10 para 2 personas) se baraja de vuelta al sacar la primera
    {    
        initCardDeck();                             //Barajo de vuelta 
        incDiceNumber();    
    }
    for(it=cardDeck.begin(); it!=cardDeck.end();it++)           //Recorro cada carta
    {
        if(*it == targetCard)           //Si es la carta que se pedía, la pongo en las visibles 
        {
            CardLocation aux = *it;
            auxIt=it;
            shownDeck.push_front(aux);
            currentTarget = aux;
            for(list<CardLocation>::iterator sincronizedCards=cardSincronized.begin(); sincronizedCards!=cardSincronized.end(); sincronizedCards++) //si no era la que saqué, recorro las cartas sincronizadas,
            {
                if(*it==*sincronizedCards)      //Me fijo si era una de las cartas que estaban sincronizadas.
                {
                    cardSincronized.erase(sincronizedCards);    //EN ese caso la borro.
                    break;
                }
            }
            retVal=true;
            break;
        }
        else if(it!=cardDeck.begin()) //salvo para la primer carta, igual esto no debería pasar nunca si esta bien hecho de afeura.
        {   //Si pase por una carta que esta sincronizada la tengo que hacer avanzar 1 lugar en el mazo, para esto se trata este if.
            bool itsAsincroCard=false;
            for(list<CardLocation>::iterator sincronizedCards=cardSincronized.begin(); sincronizedCards!=cardSincronized.end(); sincronizedCards++) //si no era la que saqué, recorro las cartas sincronizadas,
            {
                if(*it==*sincronizedCards)      //Me fijo si era una de las cartas que estaban sincronizadas.
                    itsAsincroCard=true;
            }
            if(itsAsincroCard)
            {
                list<CardLocation>::iterator prev = it;
                prev--; //Apunto al anterior elemento
                CardLocation tempLocation=*it;  //Copia del elemento a swapear
                *it=*prev;
                *prev=tempLocation;         //Pongo la carta sincronizada 1 lugar más cerca del frente del mazo.
            }
            
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
