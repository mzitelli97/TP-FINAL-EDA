#include "BurgleBrosLoots.h"
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <algorithm>    // std::shuffle

string loot2Str(Loot loot)
{
	switch (loot)
	{
	case TIARA: return "Tiara";
	case PERSIAN_KITTY:return "Persian kitty";
	case PAINTING:return "Painting";
	case MIRROR:return "Mirror";
	case KEYCARD:return "Keycard";
	case ISOTOPE:return "Isotope";
	case GEMSTONE:return "Gemstone";
	case CURSED_GOBLET:return "Cursed goblet";
	case CHIHUAHUA:return "Chihuahua";
	case GOLD_BAR:return "Gold bar";
	default: return "Error";
	}
}

Info2DrawLoot BurgleBrosLoots::getLootInfo(unsigned int nmbrOfLoot)
{
    return lootInfo[nmbrOfLoot];
}
unsigned int BurgleBrosLoots::getCurrentLoots()
{
    return currentLoots;
}


BurgleBrosLoots::BurgleBrosLoots()
{
    currentLoots=0;
    for(unsigned int i= TIARA; i < TIARA + NUMBER_OF_LOOTS; i++)
        lootDeck.push_back((Loot) i);
    lootDeck.push_back(GOLD_BAR);  //Hay 2 barras de oro en el mazo.
    shuffleDeck();
    goldBarOnFloor.first=false;
}
void BurgleBrosLoots::shuffleDeck()
{
    shuffle(lootDeck.begin(), lootDeck.end(), default_random_engine(rand()));
}
bool BurgleBrosLoots::isLootDrawn(Loot loot)
{
    bool retVal=false;
    for(unsigned int i=0; i<currentLoots; i++)
    {
        if(lootInfo[i].loot==loot)
            retVal=true;
    }
    return retVal;
}
Loot BurgleBrosLoots::getLoot(PlayerId owner)
{
    Loot aux=lootDeck[0];
    lootDeck.erase(lootDeck.begin());
    lootInfo[currentLoots].loot = aux;
    lootInfo[currentLoots].owner = owner;
    if(aux==GOLD_BAR)
    {
        for(vector<Loot>::iterator it=lootDeck.begin(); it!=lootDeck.end();it++)
        {
            if(*it==GOLD_BAR)
            {
                lootDeck.erase(it);
                break;
            }
        }
        currentLoots++;
        lootInfo[currentLoots].loot = GOLD_BAR;
        lootInfo[currentLoots].owner = NON_PLAYER;   //Sin dueño
        goldBarOnFloor.first=true;
    }
    currentLoots++;
    return aux;
}
Loot BurgleBrosLoots::getLoot(PlayerId owner, Loot thisLoot)
{
    lootInfo[currentLoots].loot = thisLoot;
    lootInfo[currentLoots].owner = owner;
    for(vector<Loot>::iterator it=lootDeck.begin(); it!=lootDeck.end();it++)            //Borro el loot que se pido
    {
        if(*it==thisLoot)
        {
            lootDeck.erase(it);
            break;
        }
    }
    if(thisLoot==GOLD_BAR)      //Si era un gold Bar se saca el otro goldbar
    {
        for(vector<Loot>::iterator it=lootDeck.begin(); it!=lootDeck.end();it++)
        {
            if(*it==GOLD_BAR)
            {
                lootDeck.erase(it);
                break;
            }
        }
        currentLoots++;
        lootInfo[currentLoots].loot = GOLD_BAR;
        lootInfo[currentLoots].owner = NON_PLAYER;   //Sin dueño
        goldBarOnFloor.first=true;
    }
    currentLoots++;
    return thisLoot;
}

void BurgleBrosLoots::setGoldBardLocation(CardLocation safeLocation)
{
    goldBarOnFloor.second=safeLocation;
}
bool BurgleBrosLoots::canPlayerPickUpGoldBarOnFloor(PlayerId whichPlayer, CardLocation playerLocation)
{
    bool retVal=false;
    if(goldBarOnFloor.first)        //Si hay una gold bar en el piso
    {
        unsigned int i;
        PlayerId playerWhoAlreadyCarriesAGoldBar;
        for(i=0; i<currentLoots;i++)
        {
            if(lootInfo[i].loot==GOLD_BAR && lootInfo[i].owner != NON_PLAYER)
                playerWhoAlreadyCarriesAGoldBar=lootInfo[i].owner;
        }
        if(whichPlayer != playerWhoAlreadyCarriesAGoldBar && playerLocation==goldBarOnFloor.second)
            retVal=true;
    }
    return retVal;
}

Loot BurgleBrosLoots::pickGoldBarOnFloor(PlayerId owner, CardLocation playerLocation)
{
    if(canPlayerPickUpGoldBarOnFloor(owner,playerLocation))
    {
        unsigned int i;
        for(i=0; i<currentLoots;i++)
        {
            if(lootInfo[i].owner==NON_PLAYER && lootInfo[i].loot==GOLD_BAR)       
                break;
        }
        lootInfo[i].owner=owner;
        goldBarOnFloor.first=false;
    }    
    return GOLD_BAR;
}

bool BurgleBrosLoots::canPlayerPickUpKitty(PlayerId whichPlayer, CardLocation playerLocation) 
{
    bool retVal=false;
    if(persianKitty.first && playerLocation==persianKitty.second)
        retVal=true;
    return retVal;

}

Loot BurgleBrosLoots::pickUpKitty(PlayerId owner,CardLocation playerLocation) 
{
    if(canPlayerPickUpKitty(owner,playerLocation))
    {
        unsigned int i;
        for(i=0; i<currentLoots;i++)
        {
            if(lootInfo[i].loot==PERSIAN_KITTY)       
                break;
        }
        lootInfo[i].owner=owner;
        persianKitty.first=false;
    }    
    return PERSIAN_KITTY;
}

bool BurgleBrosLoots::areLootsOnFloor()
{
    bool retVal=false;
    for(unsigned int i=0; i<currentLoots;i++)
    {
        if(lootInfo[i].owner==NON_PLAYER)
            retVal=true;
    }
    return retVal;
}





void BurgleBrosLoots::setNewLootOwner(Loot loot, PlayerId playerId) 
{
    unsigned int i;
    for(i=0; i<currentLoots;i++)
    {
        if(lootInfo[i].loot==loot)
            break;
    }
    lootInfo[i].owner=playerId;
    if(loot==PERSIAN_KITTY && playerId==NON_PLAYER)
        persianKitty.first=true;
    
}


BurgleBrosLoots::~BurgleBrosLoots()
{
}
