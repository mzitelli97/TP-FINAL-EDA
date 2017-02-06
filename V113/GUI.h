/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GUI.h
 * Author: user
 *
 * Created on 6 de enero de 2017, 10:50
 */

#ifndef GUI_H
#define GUI_H
#include <list>
#include <allegro5/events.h>
#include <allegro5/config.h>
#include "BurgleBrosController.h"
#include "NetworkInterface.h"

typedef enum{GUI_EVENT_MOUSE, GUI_EVENT_KEYBOARD,GUI_EVENT_NETWORKING,GUI_EVENT_NOEVENT} GuiEvent;

using namespace std;

class GUI {
public:
    GUI();
    GUI(const GUI& orig);
    void getNameAndIp(string userName, string ipToConnect, string ipToListen);
    void connect();
    bool hayEvento(void);
    void parseEvento(void);
    bool gameStillPlaying();
    void atachController (BurgleBrosController * Controller);
    virtual ~GUI();
    
private:
    BurgleBrosController * Controller;
    string userName;
    bool error;
    string ipToConnect;
    string ipToListen;
    CommunicationRole communicationRole;
    GuiEvent event;
    ALLEGRO_TIMER * timer;
    EventData *eventData;
    ALLEGRO_EVENT_QUEUE *EventQueue;     
    NetworkInterface networkingInterface;
};

#endif /* GUI_H */

