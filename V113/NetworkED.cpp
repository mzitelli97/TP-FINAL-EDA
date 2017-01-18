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

NetworkED::NetworkED(PerezProtocolHeader header,unsigned char * buffer, unsigned int length) 
{
     error=false;
     this->header=header;
     this->len=length;
     memcpy(this->buffer, buffer, len);
}

bool NetworkED::isPacketOk()
{
    return true; //Por ahora confiamos que todos los paquetes se van a mandar bien.
}
PerezProtocolHeader NetworkED::getHeader()
{
    return header;
}
CharacterName NetworkED::getCharacter()
{
    CharacterName retVal;
    if(header==I_AM)
    {
        retVal=(CharacterName)buffer[0];        //Su primer dato como numero representa justo el character name
    }
    else 
        error=true;
    return retVal;
}

string NetworkED::getName()
{
    buffer[len]= '\0';
    string aux = (char *)(&(buffer[1]));    //Como en el paquete name is se guarda los chars a partir del 2do byte y en el primero su largo es válido esto.
    return aux;
}

void NetworkED::getInitGPos(CardLocation *guardPos, CardLocation *guardsDiePos)
{
    if(header==INITIAL_G_POS)
    {
        buffer[len]= '\0';
        string aux = (char *)buffer;    //Aca quedaría en aux por ejemplo A1F2A2F1
        *guardPos=protocolToCardLocation(aux.substr(0,PROTOCOL_LOCATION_LENGTH));   //Acá se los separa.
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
            tiles->push_back((CardName)buffer[i]);      //Se pasa el tipo de cada tile
        string aux= (char *)(&(buffer[i]));             //Luego la posición el protocolo se obtiene al finalizar los tiles
        *playersStartingPos=protocolToCardLocation(aux);
    }
    else 
        error=true;
}


NetworkED::~NetworkED() 
{
}

