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

using namespace std;

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
        this->modelPointer = gamePointer;
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
            Point aux={(double)p2MouseData->getX(), (double)p2MouseData->getY()};
            CardLocation location;
            temp=view->itemFromClick(aux);          //this could be in the tile case
            location=view->point2Location(aux);
            switch(temp)
            {
   /*For the other cases it may be necessary functions like point2Guard, point2Player, to recognize which
    graphic item was clicked, ex., which of the guardCard(floor), which playerCard, which playerLoot, which button*/
                case TILE:
                    view->showMenu(modelPointer->getPosibleActions(THIS_PLAYER_ACTION, location), aux, location);
                    view->update(modelPointer);
                    break;
                case MENU_ITEM:
                    interpretAction(view->getDDMenuOption(aux), view->getDDMenuLocation());
                    view->eraseMenu();
                    view->update(modelPointer);
                    break;
                default:
                    break;
            }
        }
    }
    
    
    
}
void BurgleBrosController::interpretAction(string action, CardLocation location)
{
    
    if(action == "PEEK")//VER SI ESTE TIPO DE FUNCIONES TIENEN QUE RECIBIR QUE PLAYER O USAR EL QUE ESTA EN TURNO DIRECTAMENTE
        modelPointer->peek(THIS_PLAYER_ACTION,location);
    else if(action=="MOVE")
        modelPointer->move(THIS_PLAYER_ACTION,location);
}

BurgleBrosController::~BurgleBrosController() {
}

