#include "NetworkInterface.h"

#define DIFF_TIME_CLOCK(X,Y) (((double)((X)-(Y)))/((double) CLOCKS_PER_SEC))
#define RAND_IN_RANGE_DOUBLE(x,y) y+((((double)rand())/((double)(RAND_MAX)))*((x)-(y))) //y<x



using namespace std;


bool packetHasNoDataField(PerezProtocolHeader h)
{
    return (h==ACK || h==AGREE || h==DISAGREE || h==NAME || h==YOU_START || h==I_START || h==PASS || h==WE_WON || h==WE_LOST || h==GAME_OVER || h==QUIT || h==ERRORR);
}


NetworkInterface::NetworkInterface()
{
    p2networking = new Networking;
    firstTimeCalled = true;
    timeToBecomeServer = RAND_IN_RANGE_DOUBLE(MAX_WAITING_TIME, MIN_WAITING_TIME);
    currentRole = CLIENT;
    currClock = clock();
    prevClock = currClock;
    error=false;
}
NetworkInterface::NetworkInterface(Networking &networking)
{
	p2networking = &networking;
	firstTimeCalled = true;
	timeToBecomeServer = RAND_IN_RANGE_DOUBLE(MAX_WAITING_TIME, MIN_WAITING_TIME);
	currentRole = CLIENT;
	currClock = clock();
	prevClock = currClock;
        error=false;
}
bool NetworkInterface::standardConnectionStart(string &ip)
{
	bool connected = false;
        double time;
	if (firstTimeCalled == true)
	{
		firstTimeCalled = false;
		p2networking->prepareToConnect(ip);
	}
	switch (currentRole)
	{
	case CLIENT:
		currClock = clock();
                time = DIFF_TIME_CLOCK(currClock, prevClock);
		if (p2networking->tryToConnect() == true)
			connected = true;
		else if (time > 0.0)          //ESTO LO PUSE EN 0 PORQUE EN LA CAGADA DE NETBEANS NO FUNCABA SINO.
		{
			currentRole = SERVER;
			p2networking->abortConnecting();
			p2networking->prepareToListen();
                        cout<<"YA SOY SERVER";
		}
               break;
	case SERVER:
		if (p2networking->listen() == true)
			connected = true;
		break;
	}
	return connected;
}
CommunicationRole NetworkInterface::getCommunicationRole()
{
	return currentRole;
}
bool NetworkInterface::recievePacket(PerezProtocolHeader *header, unsigned char * msg, unsigned int *len)
{
    return p2networking->recievePacket(header,(char *)msg,len);
}
bool NetworkInterface::sendPacket(PerezProtocolHeader header)
{
    bool retVal=false;
    unsigned char buff[1];
    unsigned int i=0;
    if(packetHasNoDataField(header))
        retVal=p2networking->sendPacket(header,(const char *)buff,i);
    else
    {
        error=true;
        errorMsg= "ERROR: NetworkInterface error: tried to send a message that has data field without data field.";
    }
    return retVal;
}
bool NetworkInterface::sendName(string name)
{
    bool retVal=false;
    unsigned char auxBuffer[BUFSIZE];
    auxBuffer[0] = '\0';
    auxBuffer[0] = name.length();
    memcpy(&(auxBuffer[1]), name.c_str(), name.length());
    retVal = p2networking->sendPacket(NAME_IS, (const char *)auxBuffer, name.length() + 1);
    return retVal;
}
bool NetworkInterface::sendChar(CharacterName characterName)
{
    bool retVal=false;
    unsigned char auxBuffer[1];
    auxBuffer[0]=(unsigned char) characterName;
    retVal = p2networking->sendPacket(I_AM, (const char *)auxBuffer, 1);
    return retVal;
}
bool NetworkInterface::sendInitGPos(CardLocation guardPos, CardLocation guardDiePos)
{
    bool retVal=false;
    string aux = cardLocationToProtocol(guardPos) + cardLocationToProtocol(guardDiePos); 
    retVal = p2networking->sendPacket(INITIAL_G_POS, aux.c_str(), aux.length());
    return retVal;
}
bool NetworkInterface::sendStartInfo(vector<CardName> &tiles, CardLocation &initTile)
{
    bool retVal=false;
    unsigned char auxBuffer[BUFSIZE];
    if(tiles.size() == BOARD_STANDARD_FLOORS*FLOOR_RAWS * FLOOR_COLUMNS)
    {
        unsigned int i;
        for(i=0; i<BOARD_STANDARD_FLOORS*FLOOR_RAWS * FLOOR_COLUMNS; i++)
        {
            auxBuffer[i]=(unsigned char) tiles[i];
        }
        string initPos=cardLocationToProtocol(initTile);
        memcpy(&(auxBuffer[i]), initPos.c_str(), initPos.length());	 
        retVal = p2networking->sendPacket(START_INFO,(const char *) auxBuffer, BOARD_STANDARD_FLOORS*FLOOR_RAWS * FLOOR_COLUMNS+ initPos.length());
    }
    return retVal;
}

bool NetworkInterface::sendDice(vector<unsigned int> &dice)
{
    bool retVal=false;
    char buffer[MAX_NMBR_OF_EXTRA_DICES];
    for(unsigned int i=0; i<MAX_NMBR_OF_EXTRA_DICES; i++)
        buffer[i]=(char)((unsigned int)'0'+dice[i]);
    retVal=p2networking->sendPacket(THROW_DICE, buffer, MAX_NMBR_OF_EXTRA_DICES);
    return retVal;
}


bool NetworkInterface::sendPeek(CardLocation tileToPeek, unsigned int safeNumber)
{
    bool retVal=false;
    char buffer[2];
    buffer[0]='0'+safeNumber;
    buffer[1]='\0';
    string fullmsg= cardLocationToProtocol(tileToPeek) + buffer;
    retVal=p2networking->sendPacket(PEEK, fullmsg.c_str(), fullmsg.length());
    return retVal;
}
bool NetworkInterface::sendMove(CardLocation tileToPeek, unsigned int safeNumber)
{
    bool retVal=false;
    char buffer[2];
    buffer[0]='0'+safeNumber;
    buffer[1]='\0';
    string fullmsg= cardLocationToProtocol(tileToPeek) + buffer;
    retVal=p2networking->sendPacket(MOVE, fullmsg.c_str(), fullmsg.length());
    return retVal;
}

bool NetworkInterface::sendUseToken(CardLocation location)
{
    bool retVal=false;
    string msg=cardLocationToProtocol(location);
    retVal=p2networking->sendPacket(USE_TOKEN, msg.c_str(), msg.length());
    return retVal;
}
bool NetworkInterface::sendAddToken(CardLocation location)
{
    bool retVal=false;
    string msg=cardLocationToProtocol(location);
    retVal=p2networking->sendPacket(ADD_TOKEN, msg.c_str(), msg.length());
    return retVal;
}
bool NetworkInterface::sendSpent(bool YesOrNo)
{
    char buffer[1];
    if(YesOrNo==true)
        buffer[0]='Y';
    else
        buffer[0]='N';
    return p2networking->sendPacket(SPENT_OK, buffer, 1);
}
bool NetworkInterface::sendGMove(list<GuardMoveInfo> guardMovement)
{
    unsigned char buffer[BUFSIZE];
    buffer[0]=guardMovement.size();
    list<GuardMoveInfo>::iterator lastInfo=guardMovement.begin();
    list<GuardMoveInfo>::iterator it;
    unsigned int i=1;
    for(it=guardMovement.begin(); it != guardMovement.end(); it++ )
    {
        if(it->meaning== GUARD_STEP_TO)     //Si fue un step le pongo el formato de la carta
        {
            if(lastInfo->meaning==GUARD_CARD_PICK)   //SI hubo un mensaje previo y fue un levante de carta, pongo el 0xff para separar.
            {
                buffer[i]= 0xFF;
                i++;
            }
            cardLocationToProtocol(it->cardLocation).copy((char *)&(buffer[i]), PROTOCOL_LOCATION_LENGTH);
            i += PROTOCOL_LOCATION_LENGTH;
        }
        else
        {
            if(lastInfo->meaning==GUARD_STEP_TO)   //SI hubo un mensaje previo y fue un guard step pongo el separador 0xFF
            {
                buffer[i]= 0xFF;
                i++;
            }
            cardLocationToProtocol(it->cardLocation).copy((char *)&(buffer[i]), PROTOCOL_LOCATION_LENGTH);
            i += PROTOCOL_LOCATION_LENGTH;
        }
        lastInfo==it;
    }
    return p2networking->sendPacket(GUARD_MOVEMENT, (char *) buffer, i);
}
NetworkInterface::~NetworkInterface()
{
}
