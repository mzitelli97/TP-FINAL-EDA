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
#include "GraphicMenuItem.h"

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
            ItemInfo temp;
            Point aux={(double)p2MouseData->getX(), (double)p2MouseData->getY()};
            temp=view->itemFromClick(aux);
            //location=view->point2Location(aux);
            CardLocation * auxLocation;
            ActionOrigin * auxPlayer;
            auxInfo * menuInfo;
            unsigned int * guardFloor;
            switch(temp.type)
            {
   /*For the other cases it may be necessary functions like point2Guard, point2Player, to recognize which
    graphic item was clicked, ex., which of the guardCard(floor), which playerCard, which playerLoot, which button*/
                case TILE:
                    auxLocation = (CardLocation *)temp.info;
                    view->showMenu(modelPointer->getPosibleActions(modelPointer->getPlayerOnTurn(), *auxLocation), aux, *auxLocation);
                    view->update(modelPointer);
                    break;
                case MENU_ITEM:
                    menuInfo = (auxInfo *)temp.info;
                    interpretAction(menuInfo->option, menuInfo->location);
                    //view->eraseMenu();
                    view->update(modelPointer);
                    break;
                case LOOT_CARDS:
                    auxPlayer = (ActionOrigin *)temp.info;
                    /*if(*auxPlayer == THIS_PLAYER_ACTION)
                        view->zoomFloor(0);
                    else if(*auxPlayer == OTHER_PLAYER_ACTION)
                        view->zoomFloor(1);
                    else view->zoomFloor(2);
                    view->update(modelPointer);*/
                    break;
                case GUARD_CARDS:
                    guardFloor = (unsigned int *)temp.info;
                    cout<<*guardFloor<<endl;
                case CHAR_CARD:
                    auxPlayer = (ActionOrigin *)temp.info;
                    if(*auxPlayer == THIS_PLAYER_ACTION)
                    {
                        view->cheatCards();
                        view->update(modelPointer);
                    }
                default:
                    break;
            }
        }
    }
    
    
    
}
void BurgleBrosController::interpretAction(string action, CardLocation location)
{
    view->eraseMenu();
    if(action == "PEEK")//VER SI ESTE TIPO DE FUNCIONES TIENEN QUE RECIBIR QUE PLAYER O USAR EL QUE ESTA EN TURNO DIRECTAMENTE
        modelPointer->peek(modelPointer->getPlayerOnTurn(),location);
    else if(action=="MOVE")
        modelPointer->move(modelPointer->getPlayerOnTurn(),location);
}

BurgleBrosController::~BurgleBrosController() {
}

