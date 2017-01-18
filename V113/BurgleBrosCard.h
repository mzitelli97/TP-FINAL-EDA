#ifndef BURGLEBROSCARD_H
#define BURGLEBROSCARD_H
#include <iostream>

#define MAX_SAFE_NUMBER 6
#define MIN_SAFE_NUMBER 1

#define IS_COMPUTER_ROOM(x) (((x)==COMPUTER_ROOM_FINGERPRINT) ||((x)==COMPUTER_ROOM_MOTION) || ((x)==COMPUTER_ROOM_LASER)) 

typedef enum{ ATRIUM, CAMERA, COMPUTER_ROOM_FINGERPRINT, COMPUTER_ROOM_LASER, COMPUTER_ROOM_MOTION, DEADBOLT, FINGERPRINT, FOYER, KEYPAD,
			  LABORATORY, LASER, LAVATORY, MOTION, SAFE, SCANNER_DETECTOR, SECRET_DOOR, SERVICE_DUCT, STAIR, THERMO, WALKAWAY, GUARD_CARD}CardName;
std::string CardNameToStr(CardName tile);

typedef enum { LEFT_CARD, DOWN_CARD, RIGHT_CARD, UP_CARD }CardRelativeLocation;

typedef struct{
	unsigned int floor;
	unsigned int row;
	unsigned int column;
}CardLocation;

bool operator==(const CardLocation &l, const CardLocation &r);
bool operator<(const CardLocation &l,const CardLocation &r);
bool operator!=(const CardLocation &l, const CardLocation &r);


CardLocation getRandomCardLocation();
CardLocation getRandomCardLocation(CardLocation exceptThisPos, unsigned int inThisFloor);
CardLocation getRandomCardLocation(unsigned int inThisFloor);
bool isAnAlarmTile(CardName tile);

typedef struct{
    CardLocation location;
    CardName type;
    bool isVisible;
    unsigned int safeNumber;
}Info2DrawCards;



class BurgleBrosCard		//IMPORTANTE SEEDEAR EL RANDOM PARA EL SAFE_CRACKED!!!!!
{
public:
	typedef BurgleBrosCard * CardPointer;
	BurgleBrosCard(CardName type, CardLocation location);
	BurgleBrosCard();
	void setNeighboardCards(CardPointer left, CardPointer down, CardPointer right, CardPointer up); //Le asigna sus cartas vecinas, nullptr == no hay vecina
	void setNeighboardCard(CardRelativeLocation relativeLocation, CardPointer cardPointer);
	bool hasNeighboard(CardRelativeLocation relativeLocation);  //Devuelve si no es nullptr esa vecina.
	bool isNeighboard(CardLocation otherCardLocation);
	CardLocation getLocation();             //getters
	unsigned int getFloor();
	unsigned int getRow();
	unsigned int getColumn();
	void setVisible();                      //Da vuelta la carta, si no es un safe le asigna un número para el safe.
	bool isVisible();                     
	void safeCracked();
	unsigned int getSafeNumber();
	bool isCracked();
	CardName getCardType();
	~BurgleBrosCard();
private:
	bool visible;               
	unsigned int safeNumber;    
	bool safeState;             //Esta variable se pensó para ponerle a todas las cartas que tengan un crack token encima, y al safe cuando se abre, pero se termino usando solo para cuando la safe se abre.
	CardName cardType;
	CardLocation location;      //Su ubicación en pisos.
	CardPointer left, down, right, up;  //Sus cartas vecinas.
};

#endif

