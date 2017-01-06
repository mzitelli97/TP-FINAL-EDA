#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H
#define ALLEGRO_STATICLINK
#include <map>
#include "BurgleBrosModel.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
using namespace std;

#define IMAGE_FOLDER "Images/"
#define CHARACTER_CARD_SUBFOLDER "Characters Cards/"
#define CHARACTER_FIGURES_SUBFOLDER "Characters Figures/"
#define GUARD_SUBFOLDER "Guard/"
#define LOOT_SUBFOLDER "Loots/"
#define TILES_SUBFOLDER "Tiles/"
#define TOKENS_SUBFOLDER "Tokens/"
#define DICES_SUBFOLDER "Dices/"
#define IMAGE_EXTENSION ".png"

#define DICE_MAX_NUMBER 6

/* Estos irian en otros lados, pero por ahora quedan aca*/
/********************************************************/

typedef enum { RED_DICE, WHITE_DICE} DiceColor;

/********************************************************/	


class ImageLoader
{
public:
	ImageLoader();
	bool initImages();
	ALLEGRO_BITMAP * getGuardImage();
	ALLEGRO_BITMAP * getImageP(CardName tile);
	ALLEGRO_BITMAP * getImageP(unsigned int safeNumber);
	ALLEGRO_BITMAP * getImageP(CardLocation guardCard);
	ALLEGRO_BITMAP * getImageP(Token token);
	ALLEGRO_BITMAP * getImageP(CharacterName character, bool card); //card == 1 devuelve la carta, sino devuelve la ficha.
	ALLEGRO_BITMAP * getImageP(Loot loot);
        ALLEGRO_BITMAP * getImageP(DiceColor color, unsigned int number);
	ALLEGRO_BITMAP * getImageBackP(CardName tile);
	ALLEGRO_BITMAP * getImageBackP(CardLocation guardCard);
	ALLEGRO_BITMAP * getImageBackP(Loot loot);
	string getError();
	~ImageLoader();
private:
	bool loadCharactersCards();
	bool loadCharactersFigures();
	bool loadTokens();
	bool loadLoots();
	bool loadGuard();
	bool loadTiles();
        bool loadRedDices();
        bool loadWhiteDices();
	bool initOk;
	string errormsg;
	void destroyImages();
	map<CardName, ALLEGRO_BITMAP *> tiles;
	map<unsigned int, ALLEGRO_BITMAP *> safeNumbers;
	map<CardLocation, ALLEGRO_BITMAP *> guardCards;
	map<Loot, ALLEGRO_BITMAP *> loots;
	map<Token, ALLEGRO_BITMAP *> tokens;
	map<CharacterName, ALLEGRO_BITMAP *> characterCards;
	map<CharacterName, ALLEGRO_BITMAP *> character;
	ALLEGRO_BITMAP * tileBack;
	ALLEGRO_BITMAP * guardBack;
	ALLEGRO_BITMAP * guard;
	ALLEGRO_BITMAP * lootBack;
        ALLEGRO_BITMAP * whiteDices[DICE_MAX_NUMBER];
        ALLEGRO_BITMAP * redDices[DICE_MAX_NUMBER];
};
#endif

