/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NetworkED.h
 * Author: javier
 *
 * Created on January 18, 2017, 12:28 AM
 */

#ifndef NETWORKED_H
#define NETWORKED_H

#include "NetworkInterface.h"
#include "ProtocolFunctions.h"

class NetworkED: public EventData {
public:
    NetworkED(PerezProtocolHeader header, char * buffer, unsigned int length);
    bool isPacketOk();          //FALTARIA DESARROLLAR
    string getName();
    CharacterName getCharacter();
    void getInitGPos(CardLocation *guardPos, CardLocation *guardsDiePos);
    void getStartInfo(vector<CardName> *tiles, CardLocation *playersStartingPos);
    
    
    virtual ~NetworkED();
private:
    PerezProtocolHeader header;
    char buffer[BUFSIZE];
    unsigned int len;
    bool error=false;
};

#endif /* NETWORKED_H */

