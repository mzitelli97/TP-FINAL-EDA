#include "BurgleBrosCard.h"

std::string CardNameToStr(CardName tile)
{
	switch (tile)
	{
	case ATRIUM: return "Atrium";
	case CAMERA: return "Camera";
	case COMPUTER_ROOM_FINGERPRINT: return "Computer room fingerprint";
	case COMPUTER_ROOM_LASER: return "Computer room laser";
	case COMPUTER_ROOM_MOTION: return "Computer room motion";
	case DEADBOLT: return "Deadbolt";
	case FINGERPRINT: return "Fingerprint";
	case FOYER: return "Foyer";
	case KEYPAD: return "Keypad";
	case LABORATORY: return "Laboratory";
	case LASER: return "Laser";
	case LAVATORY: return "Lavatory";
	case MOTION: return "Motion";
	case SAFE: return "Safe";
	case SCANNER_DETECTOR: return "Scanner detector";
	case SECRET_DOOR: return "Secret door";
	case SERVICE_DUCT: return "Service duct";
	case STAIR: return "Stairs";
	case THERMO: return "Thermo";
	case WALKAWAY: return "Walkaway";
	case GUARD_CARD: return "Guard card";
	default: return "Error";
	}
}
bool operator<(const CardLocation &l, const CardLocation &r)
{
	if (l.floor < r.floor)
		return true;
	else if (l.floor == r.floor && l.row < r.row)
		return true;
	else if (l.floor == r.floor && l.row == r.row && l.column < r.column)
		return true;
	return false;
}
bool operator!=(const CardLocation &l, const CardLocation &r)
{
    return !(l==r);
}
bool operator==(const CardLocation &l, const CardLocation &r)
{
	if (l.column == r.column && l.row == r.row && l.floor == r.floor)
		return true;
	else
		return false;
}
bool isAnAlarmTile(CardName tile)
{
    return (tile==FINGERPRINT || tile == LASER || tile == MOTION || tile == SCANNER_DETECTOR || tile == THERMO || tile == CAMERA);
}
CardLocation getRandomCardLocation()
{
    CardLocation retVal;
    retVal.floor = rand()%3;
    retVal.row = rand()%4;
    retVal.column = rand()%4;
    return retVal;
}
CardLocation getRandomCardLocation(unsigned int inThisFloor)
{
    CardLocation retVal= getRandomCardLocation();
    retVal.floor=inThisFloor;
    return retVal;
}



BurgleBrosCard::BurgleBrosCard()
{
	visible = false;
	safeState = false;
}
BurgleBrosCard::BurgleBrosCard(CardName type, CardLocation location)
{
	cardType = type;
	visible = false;
	safeState = false;
	this->location = location;
}
CardLocation  BurgleBrosCard::getLocation()
{
	return location;
}
unsigned int BurgleBrosCard::getFloor()
{
	return location.floor;
}
unsigned int BurgleBrosCard::getRow()
{
	return location.row;
}
unsigned int BurgleBrosCard::getColumn()
{
	return location.column;
}
void BurgleBrosCard::setVisible()
{
	visible = true;
        if(cardType != SAFE)
            safeNumber = MIN_SAFE_NUMBER + (rand() % (MAX_SAFE_NUMBER - 1));
        else
            safeNumber = 0;
}
bool BurgleBrosCard::isVisible()
{
	return visible;
}
void BurgleBrosCard::safeCracked()
{
    safeState = true;
}
unsigned int BurgleBrosCard::getSafeNumber()
{
	return safeNumber;
}
bool BurgleBrosCard::isCracked()
{
	return safeState;
}
CardName BurgleBrosCard::getCardType()
{
	return cardType;
}
void BurgleBrosCard::setNeighboardCards(CardPointer left, CardPointer down, CardPointer right, CardPointer up)
{
	this->left = left;
	this->down = down;
	this->right = right;
	this->up = up;
}
void BurgleBrosCard::setNeighboardCard(CardRelativeLocation relativeLocation, CardPointer cardPointer)
{
	if (relativeLocation == RIGHT_CARD)
		right = cardPointer;
	if (relativeLocation == LEFT_CARD)
		left = cardPointer;
	if (relativeLocation == DOWN_CARD)
		down = cardPointer;
	if (relativeLocation == UP_CARD)
		up = cardPointer;
}
bool BurgleBrosCard::hasNeighboard(CardRelativeLocation relativeLocation)
{
	bool retVal = false;
	if (relativeLocation == RIGHT_CARD && right != nullptr)
		retVal = true;
	else if (relativeLocation == LEFT_CARD && left != nullptr)
		retVal = true;
	else if (relativeLocation == DOWN_CARD && down != nullptr)
		retVal = true;
	else if (relativeLocation == UP_CARD && up != nullptr)
		retVal = true;
	return retVal;
}
bool BurgleBrosCard::isNeighboard(CardLocation otherCardLocation)
{
	bool retVal = false;
	if (left != nullptr && left->getLocation() == otherCardLocation)
		retVal = true;
	if (down != nullptr && down->getLocation() == otherCardLocation)
		retVal = true;
	if (right != nullptr && right->getLocation() == otherCardLocation)
		retVal = true;
	if (up != nullptr && up->getLocation() == otherCardLocation)
		retVal = true;
	return retVal;
}

BurgleBrosCard::~BurgleBrosCard()
{
}

