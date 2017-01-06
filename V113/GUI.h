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
#include "Controller.h"

typedef enum{GUI_EVENT_MOUSE, GUI_EVENT_KEYBOARD,GUI_EVENT_NETWORKING,GUI_EVENT_NOEVENT} GuiEvent;

class GUI {
public:
    GUI();
    GUI(const GUI& orig);
    bool hayEvento();
    void parseEvento();
    void atachController ( list<Controller *> *listController);
    virtual ~GUI();
    
private:
    list <Controller *> * listController;
    ALLEGRO_EVENT rawEvent;
    GuiEvent Event;
    EventData *eventData;
    ALLEGRO_EVENT_QUEUE EventQueue;        
};

#endif /* GUI_H */

