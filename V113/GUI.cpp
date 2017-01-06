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

#include "GUI.h"
#include "MouseED.h"

GUI::GUI() {
    
    this->EventQueue=al_create_event_queue();
    if(EventQueue != NULL)
    
}

GUI::GUI(const GUI& orig) {
}

GUI::hayEvento()
{
    
    if(al_get_next_event(EventQueue,&rawEvent))   //necesito una eventQueue y donde la iniciliza
    {
        switch(rawEvent.type)
        {       
                case ALLEGRO_MOUSE_EVENT:
                    MouseED *auxData;
                    
                    if(rawEvent.mouse.type == ALLEGRO_EVENT_MOUSE_AXES)
                    {
                        
                    }
                    else if(rawEvent.mouse.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    {
                        auxData= new MouseED(true,rawEvent.mouse.x,rawEvent.mouse.y);
                    }
                   
                    
        }
    }
}

GUI::~GUI() {
}

