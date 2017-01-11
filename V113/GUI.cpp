/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GUI.cpp
 * Author: user
 * 
 * Created on 6 de enero de 2017, 10:50
 */

#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include "GUI.h"
#include "MouseED.h"

GUI::GUI() {
    
    this->EventQueue=al_create_event_queue();
    if(EventQueue != NULL)
    {
        al_register_event_source(EventQueue,al_get_mouse_event_source());
        al_register_event_source(EventQueue,al_get_keyboard_event_source());
    }
    
}

GUI::GUI(const GUI& orig) {
}

void GUI::atachController(BurgleBrosController* Controller)
{
    this->Controller=Controller;
}

bool GUI::gameStillPlaying()
{
    return !(Controller->checkIfGameFinished());
}
bool GUI::hayEvento()
{
    bool retVal=false;
    if(al_get_next_event(EventQueue,&rawEvent))   //necesito una eventQueue y donde la iniciliza
    {
       /* switch(rawEvent.type)
        {       
            case ALLEGRO_MOUSE_EVENT:*/

                if(rawEvent.mouse.type == ALLEGRO_EVENT_MOUSE_AXES)
                {
                   
                }
                else if(rawEvent.mouse.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                {
                    
                    MouseED *auxData= new MouseED(true,rawEvent.mouse.x,rawEvent.mouse.y);
                    eventData=(EventData *) auxData;
                    event=GUI_EVENT_MOUSE;
                    retVal=true;
                }
                else if(rawEvent.mouse.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                {

                }
                //break;
 /*           case ALLEGRO_KEYBOARD_EVENT:    
                    
                break;
        
        }*/
        
        
    }
    //elseif NETWORKING
    return retVal;
}

void GUI::parseEvento(){
    
    switch(event)
    {
        case GUI_EVENT_MOUSE:
            Controller->parseMouseEvent(eventData);
            break;
        case GUI_EVENT_KEYBOARD:
            break;
        case GUI_EVENT_NETWORKING:
            break;
    }
    
}

GUI::~GUI() {
}

