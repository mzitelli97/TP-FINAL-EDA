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
    for(unsigned int i= TIARA; i < NUMBER_OF_LOOTS; i++)
        lootDeck.push_back((Loot) i);
    lootDeck.push_back(GOLD_BAR);  //Hay 2 barras de oro en el mazo.
    shuffleDeck();
}
void BurgleBrosLoots::shuffleDeck()
{
    shuffle(lootDeck.begin(), lootDeck.end(), default_random_engine(rand()));
}
Loot BurgleBrosLoots::getLoot(ActionOrigin owner)
{
    Loot aux=lootDeck[0];
    lootDeck.erase(lootDeck.begin());
    lootInfo[currentLoots].loot = aux;
    lootInfo[currentLoots].owner = owner;
    currentLoots++;
}


BurgleBrosLoots::~BurgleBrosLoots()
{
}
