/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NetworkED.cpp
 * Author: javier
 * 
 * Created on January 18, 2017, 12:28 AM
 */

#include "NetworkED.h"

NetworkED::NetworkED(PerezProtocolHeader header, char * buffer, unsigned int length) 
{
     error=false;
    
}

bool NetworkED::isPacketOk()
{
    return true; //Por ahora confiamos que todos los paquetes se van a mandar bien.
}
CharacterName NetworkED::getCharacter()
{
    CharacterName retVal;
    if(header==I_AM)
    {
        retVal=(CharacterName)buffer[0];
    }
    else 
        error=true;
    return retVal;
}
void NetworkED::getInitGPos(CardLocation *guardPos, CardLocation *guardsDiePos)
{
    if(header==INITIAL_G_POS)
    {
        buffer[len]= '\0';
        string aux = buffer;
        *guardPos=protocolToCardLocation(aux.substr(0,PROTOCOL_LOCATION_LENGTH));
        *guardsDiePos=protocolToCardLocation(aux.substr(PROTOCOL_LOCATION_LENGTH,PROTOCOL_LOCATION_LENGTH));
    }
    else 
        error=true;
}
void NetworkED::getStartInfo(vector<CardName> *tiles, CardLocation *playersStartingPos)
{
    tiles->clear();
    if(header==START_INFO)
    {
        buffer[len]= '\0';
        unsigned int i;
        for(i=0;i<BOARD_STANDARD_FLOORS*FLOOR_RAWS*FLOOR_COLUMNS; i++)
            tiles->push_back((CardName)buffer[i]);
        string aux= (&(buffer[i]));
        *playersStartingPos=protocolToCardLocation(aux);
    }
    else 
        error=true;
}


NetworkED::~NetworkED() 
{
}

