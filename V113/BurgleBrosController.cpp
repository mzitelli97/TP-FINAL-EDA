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
    gameIsOver=false;
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
bool BurgleBrosController::checkIfGameFinished()
{
    return gameIsOver;
}
string BurgleBrosController::askForSpentOK(vector<string> &message)
{
    string retVal;
    //Parar timers que controlan el timeout
    retVal=view->MessageBox(message);  //Bloqueante
    
    //Manda por network el spent ok con yes o no
    return retVal;
}


void BurgleBrosController::parseMouseEvent(EventData *mouseEvent)
{
    
    if(mouseEvent!=nullptr)
    {
        MouseED *p2MouseData = dynamic_cast<MouseED *> (mouseEvent);
        if( p2MouseData != nullptr)
        {
            ItemInfo temp;
            vector<string> exitMsg={"Quit","Confirm quit", "You have pressed the quit button. Are you sure you wanna quit?"};
            Point aux={(double)p2MouseData->getX(), (double)p2MouseData->getY()};
            temp=view->itemFromClick(aux);
            //location=view->point2Location(aux);
            CardLocation * auxLocation;
            ActionOrigin * auxPlayer;
            auxInfo * menuInfo;
            CardLocation aux1 = {1,3,3};
            unsigned int * floor;
            switch(temp.type)
            {
   /*For the other cases it may be necessary functions like point2Guard, point2Player, to recognize which
    graphic item was clicked, ex., which of the guardCard(floor), which playerCard, which playerLoot, which button*/
                case TILE_CLICK:
                    auxLocation = (CardLocation *)temp.info;
                    view->showMenu(modelPointer->getPosibleActions(modelPointer->getPlayerOnTurn(), *auxLocation), aux, *auxLocation);
                    view->update(modelPointer);
                    break;
                case MENU_ITEM_CLICK:
                    menuInfo = (auxInfo *)temp.info;
                    interpretAction(menuInfo->option, menuInfo->location);
                    view->update(modelPointer);
                    break;
                case LOOT_CARDS_CLICK:
                    auxPlayer = (ActionOrigin *)temp.info;
                    break;
                case GUARD_CARDS_CLICK:
                    floor = (unsigned int *)temp.info;
                    cout<<*floor<<endl;
                    break;
                case CHAR_CARD_CLICK:
                    auxPlayer = (ActionOrigin *)temp.info;
                    if(*auxPlayer == THIS_PLAYER_ACTION)
                    {
                        view->cheatCards();
                        view->update(modelPointer);
                    }
                    break;
                case ZOOM_CLICK:
                    floor = (unsigned int *)temp.info;
                    view->zoomFloor(*floor,modelPointer);
                    view->update(modelPointer);
                    break;
                case EXIT_BUTTON_CLICK:
                    if(view->yesNoMessageBox(exitMsg)==1)
                    {
                        gameIsOver=true;
                        quitCause=USER_QUIT;
                    }
                    break;
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
    else if(action=="ADD TOKEN")
        modelPointer->addToken(modelPointer->getPlayerOnTurn(),location);
    else if(action=="ADD DIE")
        modelPointer->addDieToSafe(modelPointer->getPlayerOnTurn(),location);
    else if(action=="CRACK")
        modelPointer->crackSafe(modelPointer->getPlayerOnTurn(),location);
}

BurgleBrosController::~BurgleBrosController() {
}

