/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BurgleBrosController.cpp
 * Author: javier
 * 
 * Created on December 29, 2016, 5:34 PM
 */

#include "BurgleBrosController.h"
#include "MouseED.h"

BurgleBrosController::BurgleBrosController() 
{
    modelPointer=nullptr;
    view=nullptr;
}

BurgleBrosController::BurgleBrosController(const BurgleBrosController& orig) {
}

void BurgleBrosController::attachModel(BurgleBrosModel *gamePointer)
{
    if(gamePointer!=nullptr)
        this->modelPointer;
}
void BurgleBrosController::attachView(BurgleBrosView *view)
{
    if(view!=nullptr)
        this->view=view;
}
void BurgleBrosController::parseMouseEvent(EventData *mouseEvent)
{
    
    if(mouseEvent!=nullptr)
    {
        MouseED *p2MouseData = dynamic_cast<MouseED *> (mouseEvent);
        if( p2MouseData != nullptr)
        {
            clickItem temp;
            Point aux;
            CardLocation location;
            aux.x=p2MouseData->getX();
            aux.y=p2MouseData->getY();
            temp=view->itemFromClick(aux);
            location=view->point2Location(aux);
            switch(temp)
            {
                case TILE:
                    view->showMenu(modelPointer->getPosibleActions(THIS_PLAYER_ACTION, aux), aux, location);
                    break;
                case MENU_ITEM:
                    interpretAction(view->getDDMenuOption(), view->getDDMenuLocation())
                    break;
                default:
                    break;
            }
        }
    }
    
    
    
}


BurgleBrosController::~BurgleBrosController() {
}

