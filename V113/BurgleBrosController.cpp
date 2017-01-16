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
#include <algorithm>

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
            CardLocation * auxLocation;
            ActionOrigin * auxPlayer;
            auxInfo * menuInfo;
            unsigned int * floor;
            switch(temp.type)
            {
                case TILE_CLICK:
                    auxLocation = (CardLocation *)temp.info;
                    view->showMenu(modelPointer->getPosibleActionsToTile(modelPointer->getPlayerOnTurn(), *auxLocation), aux, *auxLocation);
                    view->update(modelPointer);
                    break;
                case MENU_ITEM_CLICK:
                    menuInfo = (auxInfo *)temp.info;
                    interpretAction(menuInfo->option, menuInfo->location);
                    view->update(modelPointer);
                    break;
                case LOOT_CARDS_CLICK:
                    auxPlayer = (ActionOrigin *)temp.info;
                    view->zoomLoot(*auxPlayer);
                    view->update(modelPointer);
                    break;
                case GUARD_CARDS_CLICK:
                    floor = (unsigned int *)temp.info;
                    view->showMenu(modelPointer->getPosibleActionsToGuard(modelPointer->getPlayerOnTurn(), *floor), aux, *floor);
                    view->update(modelPointer);
                    break;
                case CHAR_CARD_CLICK:
                    auxPlayer = (ActionOrigin *)temp.info;
                    if(*auxPlayer == THIS_PLAYER_ACTION)
                        view->cheatCards();
                    else if (*auxPlayer == OTHER_PLAYER_ACTION)
                        view->zoomPlayerCard(*auxPlayer);
                    view->update(modelPointer);
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
                case PASS_BUTTON_CLICK:
                    view->eraseMenu();
                    modelPointer->pass(modelPointer->getPlayerOnTurn());
                    break;
                default:
                    view->eraseMenu();
                    view->update(modelPointer);
                    break;
            }
        }
    }
    checkGameStatus();
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
    else if(action=="CREATE ALARM")
        modelPointer->createAlarm(modelPointer->getPlayerOnTurn(),location);
    else if(action=="PLACE CROW")
        modelPointer->placeCrow(modelPointer->getPlayerOnTurn(),location);
    else if(action=="PICK UP KITTY")
        modelPointer->pickLoot(modelPointer->getPlayerOnTurn(), location, PERSIAN_KITTY);
    else if(action=="PICK UP GOLD BAR")
        modelPointer->pickLoot(modelPointer->getPlayerOnTurn(), location, GOLD_BAR);
    else if(action=="ESCAPE")
        modelPointer->escape(modelPointer->getPlayerOnTurn(),location);
    else if(action=="PEEK TOP CARD")
        modelPointer->peekGuardsCard(modelPointer->getPlayerOnTurn(),location.floor);
    else
    {
        for(int i = (int)TIARA; i <= (int)GOLD_BAR; i++)
        {
            string ask = "ASK FOR ";
            string offer = "OFFER ";
            ask += loot2Str((Loot)i);
            offer += loot2Str((Loot)i);
            transform(ask.begin(), ask.end(), ask.begin(), ::toupper);
            transform(offer.begin(), offer.end(), offer.begin(), ::toupper);
            if(action==ask)
            {
                modelPointer->askForLoot(modelPointer->getPlayerOnTurn(),location,(Loot)i);
                break;
            }
            if(action==offer)
            {
                modelPointer->offerLoot(modelPointer->getPlayerOnTurn(),location,(Loot)i);
                break;
            }
        }
    }
    /*else if(action=="ASK FOR TIARA")
        modelPointer->askForLoot(modelPointer->getPlayerOnTurn(),location,TIARA);
    else if(action=="ASK FOR PERSIAN KITTY")
        modelPointer->askForLoot(modelPointer->getPlayerOnTurn(),location,PERSIAN_KITTY);
    else if(action=="ASK FOR PAITING")
        modelPointer->askForLoot(modelPointer->getPlayerOnTurn(),location,PAINTING);
    else if(action=="ASK FOR MIRROR")
        modelPointer->askForLoot(modelPointer->getPlayerOnTurn(),location,MIRROR);
    else if(action=="ASK FOR KEYCARD")
        modelPointer->askForLoot(modelPointer->getPlayerOnTurn(),location,KEYCARD);
    else if(action=="ASK FOR ISOTOPE")
        modelPointer->askForLoot(modelPointer->getPlayerOnTurn(),location,ISOTOPE);
    else if(action=="ASK FOR GEMSTONE")
        modelPointer->askForLoot(modelPointer->getPlayerOnTurn(),location,GEMSTONE);
    else if(action=="ASK FOR CURSED GOBLET")
        modelPointer->askForLoot(modelPointer->getPlayerOnTurn(),location,CURSED_GOBLET);
    else if(action=="ASK FOR CHIHUAHUA")
        modelPointer->askForLoot(modelPointer->getPlayerOnTurn(),location,CHIHUAHUA);
    else if(action=="ASK FOR GOLD BAR")
        modelPointer->askForLoot(modelPointer->getPlayerOnTurn(),location,GOLD_BAR);
    else if(action=="OFFER TIARA")
        modelPointer->offerLoot(modelPointer->getPlayerOnTurn(),location,TIARA);
    else if(action=="OFFER PERSIAN KITTY")
        modelPointer->offerLoot(modelPointer->getPlayerOnTurn(),location,PERSIAN_KITTY);
    else if(action=="OFFER PAITING")
        modelPointer->offerLoot(modelPointer->getPlayerOnTurn(),location,PAINTING);
    else if(action=="OFFER MIRROR")
        modelPointer->offerLoot(modelPointer->getPlayerOnTurn(),location,MIRROR);
    else if(action=="OFFER KEYCARD")
        modelPointer->offerLoot(modelPointer->getPlayerOnTurn(),location,KEYCARD);
    else if(action=="OFFER ISOTOPE")
        modelPointer->offerLoot(modelPointer->getPlayerOnTurn(),location,ISOTOPE);
    else if(action=="OFFER GEMSTONE")
        modelPointer->offerLoot(modelPointer->getPlayerOnTurn(),location,GEMSTONE);
    else if(action=="OFFER CURSED GOBLET")
        modelPointer->offerLoot(modelPointer->getPlayerOnTurn(),location,CURSED_GOBLET);
    else if(action=="OFFER CHIHUAHUA")
        modelPointer->offerLoot(modelPointer->getPlayerOnTurn(),location,CHIHUAHUA);
    else if(action=="OFFER GOLD BAR")
        modelPointer->offerLoot(modelPointer->getPlayerOnTurn(),location,GOLD_BAR);*/
}

void BurgleBrosController::checkGameStatus()
{
    if(modelPointer->hasGameFinished())
    {
        string aux = modelPointer->getFinishMsg();
        if(aux=="WON")
        {
            vector<string> auxmsg({DEFAULT_WIN_MSG});
            while(1)
                view->MessageBox(auxmsg);
        }
    }
}


BurgleBrosController::~BurgleBrosController() {
}

