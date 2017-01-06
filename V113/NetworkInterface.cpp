#include "NetworkInterface.h"

#define DIFF_TIME_CLOCK(X,Y) (((double)((X)-(Y)))/((double) CLOCKS_PER_SEC))
#define RAND_IN_RANGE_DOUBLE(x,y) y+((((double)rand())/((double)(RAND_MAX)))*((x)-(y))) //y<x

using namespace std;
NetworkInterface::NetworkInterface()
{
    p2networking = new Networking;
    firstTimeCalled = true;
    timeToBecomeServer = RAND_IN_RANGE_DOUBLE(MAX_WAITING_TIME, MIN_WAITING_TIME);
    currentRole = CLIENT;
    currClock = clock();
    prevClock = currClock;
}
NetworkInterface::NetworkInterface(Networking &networking)
{
	p2networking = &networking;
	firstTimeCalled = true;
	timeToBecomeServer = RAND_IN_RANGE_DOUBLE(MAX_WAITING_TIME, MIN_WAITING_TIME);
	currentRole = CLIENT;
	currClock = clock();
	prevClock = currClock;
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
bool NetworkInterface::sendPacket(PerezProtocolHeader header, string message)
{
	bool retVal = false;
	string cardTypes, playerTile;
	size_t found;
	unsigned char auxBuffer[BUFSIZE];
	unsigned char auxChar;
	switch (header)
	{
	case START_INFO:
		auxBuffer[0] = '\0';
		unsigned int len;
		found = message.rfind(',');
		cardTypes = message.substr(0, found);
		playerTile = message.substr(found + 1, message.length() - (found + 1));
		strNmbrFieldToArray(cardTypes, auxBuffer, &len);
		auxBuffer[len] = '\0';
		memcpy(&(auxBuffer[len]), playerTile.c_str(), playerTile.length());
		retVal = p2networking->sendPacket(header, (const char *)auxBuffer, playerTile.length() + len);
		break;
	case GUARD_MOVEMENT:
		auxBuffer[0] = '\0';
		memcpy(auxBuffer, message.c_str(), message.length());
		for (unsigned int i = 0; i < message.length(); i++)
		{
			if (auxBuffer[i] == ',')												//entre los movs que realiza y las carta que levanta, el guard se pone un FF, pero en el programa le vamos a poner , as� es mas facil porque se puede operar con strings
				auxBuffer[i] = 0xFF;												//entonces se reemplaza antes de enviarse en esta capa m�s baja.
		}
		retVal = p2networking->sendPacket(header, (const char *)auxBuffer, message.length());
		break;
	case NAME_IS:
		auxBuffer[0] = '\0';
		auxBuffer[0] = message.length();											//Por protocolo, debe ir en el primer byte el largo del nombre y luego el nombre.
		memcpy(&(auxBuffer[1]), message.c_str(), message.length());
		retVal = p2networking->sendPacket(header, (const char *)auxBuffer, message.length() + 1);
		break;
	case I_AM: case OFFER_LOOT: case REQUEST_LOOT:
		auxChar = (unsigned char)stoi(message);
		retVal = p2networking->sendPacket(header, (const char *)&auxChar, 1);
		break;
	default:
		retVal = p2networking->sendPacket(header, message.c_str(), message.length());
		break;
	}
	return retVal;
}

bool NetworkInterface::recievePacket(PerezProtocolHeader *headerRecieved, string *messageRecieved)
{
	bool retVal = false;
	unsigned int lengthRecieved;
	unsigned char auxBuffer[BUFSIZE];
	retVal = p2networking->recievePacket(headerRecieved, (char *)auxBuffer, &lengthRecieved);
	if (retVal == true)
	{
		auxBuffer[lengthRecieved] = (unsigned char) '\0';
		string playerPos; //Switch no deja crear variables  en sus casos, pongo todas las variables auxiliares aca.
		string cardTypes;
		string coma;
		char auxBuffer2[BUFSIZE];
		switch (*headerRecieved)
		{
		case START_INFO:
			playerPos = (char *)&(auxBuffer[lengthRecieved - 4]);
			coma = ",";
			arrayToStrNmbrField(&cardTypes, auxBuffer, lengthRecieved - 4); //4 De la posici�n del juego
			*messageRecieved = cardTypes + coma + playerPos;
			break;
		case GUARD_MOVEMENT:
			for (unsigned int i = 0; i < lengthRecieved; i++)
			{
				if (auxBuffer[i] == 0xFF)
					auxBuffer[i] = ',';
			}
			*messageRecieved = (char *)auxBuffer;
			break;
		case NAME_IS:
			*messageRecieved = (char *)&(auxBuffer[1]);
			break;
		case I_AM: case OFFER_LOOT: case REQUEST_LOOT:
			auxBuffer2[0] = '\0';
			sprintf(auxBuffer2, "%d", (unsigned int)auxBuffer[0]);
			*messageRecieved = auxBuffer2;
			break;
		default:
			*messageRecieved = (char *)auxBuffer; //Faltar�a checkear si es v�lido el header.
			break;
		}
	}
	return retVal;
}






NetworkInterface::~NetworkInterface()
{
}
