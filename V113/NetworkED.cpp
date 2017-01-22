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
CardLocation NetworkED::getPos()
{
    CardLocation retVal;
    if(header==MOVE || header == PEEK)
    {
        char temp =  buffer[len-1];   //Guardo el numero del safe.
        buffer[len-1]= '\0';    //Pongo un terminador en su lugar
        string aux =(char *) buffer;
        retVal=protocolToCardLocation(aux); // Lo paso por string y lo convierto a card locatioon
        buffer[len-1]=temp;         //Le vuelvo a asignar su número del safe.
    }
    else 
        error=true;
    return retVal;
}
CardLocation NetworkED::getTokenPos()
{
    CardLocation retVal;
    if(header==ADD_TOKEN || USE_TOKEN)
    {
        buffer[len]= '\0';
        string aux =(char *) buffer;
        retVal=protocolToCardLocation(aux);
    }
    else
        error=true;
    return retVal;
}
bool NetworkED::playerAcceptedToSpentMoves()
{
    bool retVal=false;
    if(header==SPENT_OK)
    {
        if(buffer[0]=='Y')
            retVal=true;
    }
    else 
        error=true;
    return retVal;
}
unsigned int NetworkED::getSafeNumber()
{
    unsigned int retVal;
    if(header==MOVE || header == PEEK)
    {
        retVal=buffer[len-1]- '0';       //El numero de safe se guarda en el ultimo byte del msg.
    }
    else 
        error=true;
    return retVal;
}
void NetworkED::getDice(vector<unsigned int> &dice)
{
    dice.clear();
    dice.reserve(MAX_NMBR_OF_EXTRA_DICES);
    if(header==THROW_DICE)
    {
        for(unsigned int i=0; i<MAX_NMBR_OF_EXTRA_DICES; i++)
            dice.push_back((unsigned int)(buffer[i]-'0'));
    }
    else 
        error=true;
}

void NetworkED::getGuardMovement(list<GuardMoveInfo> &guardInfo)
{
    unsigned int i=1;
    unsigned char temp;
    GuardMoveInfo auxgInfo;
    LocationMeaning currMeaning=GUARD_STEP_TO;
    while(i<len)
    {
        if(buffer[i] == 0xFF)
        {
            if(currMeaning==GUARD_STEP_TO)
                currMeaning=GUARD_CARD_PICK;
            else
                currMeaning=GUARD_STEP_TO;
            i++;
        }
        else
        {
            temp=buffer[i+PROTOCOL_LOCATION_LENGTH];
            buffer[i+PROTOCOL_LOCATION_LENGTH]='\0';
            auxgInfo.cardLocation=protocolToCardLocation((const char*)&(buffer[i]));
            auxgInfo.meaning=currMeaning;
            guardInfo.push_back(auxgInfo);
            buffer[i+PROTOCOL_LOCATION_LENGTH]=temp;
            i += PROTOCOL_LOCATION_LENGTH;
        }
        
    }
}

NetworkED::~NetworkED() 
{
}

