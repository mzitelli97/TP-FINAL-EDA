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

std::string cardLocationToProtocol(CardLocation &cardLocation);		//(0,0,0) (floor,row,column) = A1F1 (protocol)
CardLocation protocolToCardLocation(std::string location);
CardLocation getRandomCardLocation();
CardLocation getRandomCardLocation(unsigned int inThisFloor);


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
	BurgleBrosCard(CardName type, std::string location);
	BurgleBrosCard();
	void setNeighboardCards(CardPointer left, CardPointer down, CardPointer right, CardPointer up);
	void setNeighboardCard(CardRelativeLocation relativeLocation, CardPointer cardPointer);
	bool hasNeighboard(CardRelativeLocation relativeLocation);
	bool isNeighboard(CardLocation otherCardLocation);
	CardLocation getLocation();
	unsigned int getFloor();
	unsigned int getRow();
	unsigned int getColumn();
	std::string getProtocolUbication();
	void setVisible();
	bool isVisible();
	void safeCracked();
	unsigned int getSafeNumber();
	bool isCracked();
	CardName getCardType();
	~BurgleBrosCard();
private:
	bool visible;
	unsigned int safeNumber;
	bool safeState;
	CardName cardType;
	CardLocation location;
	CardPointer left, down, right, up;									//Esto lo recomend� agustin.
};

#endif

