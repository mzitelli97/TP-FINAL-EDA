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

CharacterName getRandomCharacter()
{
    CharacterName retVal;
    unsigned int i= rand()% NUMBER_OF_CHARACTERS;
    retVal= (CharacterName)((unsigned int)FIRST_CHARACTER + i);
    return retVal;
}
CharacterName  getRandomCharacter(CharacterName exceptThis)
{
    CharacterName retVal;
    do{
        retVal=getRandomCharacter();
    }while(retVal==exceptThis);
    return retVal;
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
void BurgleBrosPlayer::getToDaChoppa()
{
    isOnTheHelicopter=true;
    isOnTheBoard=false;
    //position = {3,4,4}; this does not work, do something to dont show the player anymore
}
void BurgleBrosPlayer::setCharacter(CharacterName character)
{
    characterName=character;
}
void BurgleBrosPlayer::setName(string name)
{
    this->name=name;
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
bool BurgleBrosPlayer::isOnHelicopter()
{
    return isOnTheHelicopter;
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
void BurgleBrosPlayer::deattachLoot(Loot loot)
{
    for(list<Loot>::iterator it=lootCarried.begin(); it != lootCarried.end(); it++)
    {
        if(*it == loot)
        {
            lootCarried.erase(it);
            break;
        }            
    }
}


bool BurgleBrosPlayer::hasLoot(Loot loot)
{
    bool retVal=false;
    for(list<Loot>::iterator it=lootCarried.begin(); it != lootCarried.end(); it++)
    {
        if(*it == loot)
        {
            retVal=true;
            break;
        }
    }
    return retVal;
}

bool BurgleBrosPlayer::carriesLoot() 
{
    bool retVal=true;
    if(lootCarried.empty())
        retVal=false;
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

void BurgleBrosPlayer::attachLoot(Loot loot)
{
    lootCarried.push_back(loot);
}
BurgleBrosPlayer::BurgleBrosPlayer()
{
    //pickRandomPlayer();//Ver si queda adentro, afuera o que....
    currentActions=4;
    lives=INIT_NMBR_OF_LIVES;
    isOnTheHelicopter=false;
    isPlayersTurn=false;
}

BurgleBrosPlayer::~BurgleBrosPlayer()
{
}
