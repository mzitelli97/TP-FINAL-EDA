#include "BurgleBrosPlayer.h"

string character2Str(CharacterName character)
{
	switch (character)
	{
	case THE_JUICER:return "The juicer";
	case THE_HACKER:return "The hacker";
	case THE_ACROBAT:return "The acrobat";
	case THE_SPOTTER:return "The spotter";
	case THE_HAWK:return "The hawk";
	case THE_RAVEN:return "The raven";
	case THE_PETERMAN:return "The peterman";
	default: return "Error";
	}
}
unsigned int BurgleBrosPlayer::getCurrLifes()
{
    return lives;
}
void BurgleBrosPlayer::decLives()
{
    if(lives > 0)
        lives--;
}




void BurgleBrosPlayer::pickRandomPlayer()
{
    unsigned int i= rand()% NUMBER_OF_CHARACTERS;
    characterName= (CharacterName)((unsigned int)FIRST_CHARACTER + i);
    currentActions=4;
}
void BurgleBrosPlayer::pickRandomPlayer(CharacterName exceptThis)
{
    do{
        pickRandomPlayer();
    }while(characterName==exceptThis);
}
unsigned int BurgleBrosPlayer::getcurrentActions()
{
    return currentActions;
}
void BurgleBrosPlayer::setPosition(CardLocation location)
{
    position=location;
}
bool BurgleBrosPlayer::isItsTurn()
{
    return isPlayersTurn;
}
CardLocation BurgleBrosPlayer::getPosition()
{
    return position;
}
void BurgleBrosPlayer::setTurn(bool isPlayersTurn)
{
    this->isPlayersTurn=isPlayersTurn;
}

void BurgleBrosPlayer::setActions(unsigned int actions)
{
    currentActions = actions;
}
void BurgleBrosPlayer::decActions()
{
    if(currentActions > 0)
        currentActions--;
}
bool BurgleBrosPlayer::hasLoot(Loot loot)
{
    bool retVal=false;
    for(list<Loot>::iterator it=lootCarried.begin(); it != lootCarried.end(); it++)
    {
        if(*it == loot)
            retVal=true;
    }
    return retVal;
}
CharacterName BurgleBrosPlayer:: getCharacter()
{
    return characterName;
}
string BurgleBrosPlayer:: getName()
{
    return name;
}


BurgleBrosPlayer::BurgleBrosPlayer()
{
    //pickRandomPlayer();//Ver si queda adentro, afuera o que....
    position.floor=0;
    position.row=0;
    position.column=0;
    lives=INIT_NMBR_OF_LIVES;
}

BurgleBrosPlayer::~BurgleBrosPlayer()
{
}
