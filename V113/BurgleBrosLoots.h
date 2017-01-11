#ifndef BURGLEBROSLOOTS_H
#define BURGLEBROSLOOTS_H
#define NUMBER_OF_PLAYERS 2
#include "BurgleBrosCard.h"
#include <iostream>
#include <vector>


typedef enum { TIARA = 0x30, PERSIAN_KITTY, PAINTING, MIRROR, KEYCARD, ISOTOPE, GEMSTONE, CURSED_GOBLET, CHIHUAHUA, GOLD_BAR } Loot;
#define NUMBER_OF_LOOTS 10
#define MAX_LOOTS_IN_A_GAME 4
using namespace std;
string loot2Str(Loot loot);
typedef enum{OTHER_PLAYER_ACTION, THIS_PLAYER_ACTION, NON_PLAYER} ActionOrigin;
typedef struct
{
	Loot loot;
	ActionOrigin owner;//no es BurgleBrosPlayer por problemas con includes, pero siempre desreferenciar a menos que sea null.
}Info2DrawLoot;

class BurgleBrosLoots
{
public:
	BurgleBrosLoots();
	Info2DrawLoot getLootInfo(unsigned int nmbrOfLoot);
	unsigned int getCurrentLoots();
        bool isLootDrawn(Loot loot);
        bool isGoldBarOnFloor();
        void setGoldBardLocation(CardLocation safeLocation);
        bool canPlayerPickUpGoldBarOnFloor(ActionOrigin whichPlayer, CardLocation playerLocation);
        Loot pickGoldBarOnFloor(ActionOrigin owner);
        Loot getLoot(ActionOrigin owner); //Devuelve el loot que estaba en la cima de la pila y guarda en su info interna el loot que sac� y a que jugador le pertenece.
	~BurgleBrosLoots();
private:
	void shuffleDeck();
	vector<Loot> lootDeck;
	Info2DrawLoot lootInfo[MAX_LOOTS_IN_A_GAME];
        pair<bool,CardLocation> goldBarOnFloor;
	unsigned int currentLoots;
	CardLocation persianKittyLocation;
};
#endif

