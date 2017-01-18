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
#include "GUI.h"
#include "NetworkED.h"
#include <algorithm>

using namespace std;

BurgleBrosController::BurgleBrosController() 
{
    modelPointer=nullptr;
    view=nullptr;
    quit=false;
    status=INITIALIZING;
    initPacketCount=0;
}

BurgleBrosController::BurgleBrosController(const BurgleBrosController& orig) {
}

void BurgleBrosController::setThisPlayerName(string name)
{
    this->thisPlayerName=name;
}

void BurgleBrosController::setCommunicationRole(CommunicationRole communicationRole)
{
    this->communicationRole=communicationRole;
}
void BurgleBrosController::attachNetworkInterface(NetworkInterface * p2NetworkInterface)
{
    this->networkInterface=p2NetworkInterface;
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
    return quit;
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
            PlayerId * auxPlayer;
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
                    auxPlayer = (PlayerId *)temp.info;
                    view->zoomLoot(*auxPlayer);
                    view->update(modelPointer);
                    break;
                case GUARD_CARDS_CLICK:
                    floor = (unsigned int *)temp.info;
                    view->showMenu(modelPointer->getPosibleActionsToGuard(modelPointer->getPlayerOnTurn(), *floor), aux, *floor);
                    view->update(modelPointer);
                    break;
                case CHAR_CARD_CLICK:
                    auxPlayer = (PlayerId *)temp.info;
                    if(*auxPlayer == THIS_PLAYER)
                        view->cheatCards();
                    else if (*auxPlayer == OTHER_PLAYER)
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
                        quit=true;
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
}

void BurgleBrosController::parseNetworkEvent(EventData *networkEvent)
{
    NetworkED *p2NetworkData = dynamic_cast<NetworkED *> (networkEvent);
    if(p2NetworkData!=nullptr)
    {
        switch(status)      //Depende de en que estado está el juego, los paquetes de internet significan distintas cosas
        {
            case INITIALIZING:          //En la inicialización importa si es el cliente o el server en cuanto al orden de los mensajes
                if(communicationRole==CLIENT)
                    clientInitRoutine(p2NetworkData);
                else if(communicationRole==SERVER)
                    serverInitRoutine(p2NetworkData);
                break;
            default:
                break;
              
        }
    }
    else
        quit=true;
}

void BurgleBrosController::clientInitRoutine(NetworkED *networkEvent)
{
    unsigned int packetCountCopy=initPacketCount;   //Saco una copia del número de paquete de inicialización
    CardLocation guardPos,guardsDiePos, playersPos;
    vector<CardName> tiles;
    switch(initPacketCount)
    {
        case 0: 
            if(networkEvent->getHeader() == NAME)   //Primero el client recibe el paquete name
            {
                networkInterface->sendName(thisPlayerName);  //Al cual le responde con su nombre 
                initPacketCount++;
            }
            break;
        case 1:
            if(networkEvent->getHeader() == ACK)        //Una vez que el server recibió la informacion y confirmó con un ack
            {
                networkInterface->sendPacket(NAME);     //Se le envía name para saber el nombre del server.
                initPacketCount++;
            }
            break;
        case 2:
            if(networkEvent->getHeader() == NAME_IS)    //El server responde con su nombre.
            {
                auxInitInfo[OTHER_PLAYER].PlayerName=networkEvent->getName(); //Se guarda en una estructura auxiliar para luego pasarle toda la información junta de inicialización de jugadores al modelo.
                networkInterface->sendPacket(ACK);     //Se le envía un ack para confirmar la información recibida.
                initPacketCount++;
            }
            break;
        case 3:
            if(networkEvent->getHeader() == I_AM)   //Luego el server manda que character escogió
            {
                auxInitInfo[OTHER_PLAYER].playersCharacter=networkEvent->getCharacter();        //Se guarda su jugador
                auxInitInfo[THIS_PLAYER].playersCharacter=getRandomCharacter(auxInitInfo[OTHER_PLAYER].playersCharacter);    //Se elige uno random que no sea el que escogió el server
                networkInterface->sendChar(auxInitInfo[THIS_PLAYER].playersCharacter);      //Y se le manda la info de cual es el que escogió el client.
                initPacketCount++;
            }
            break;
        case 4:
            if(networkEvent->getHeader() == INITIAL_G_POS)      //El server crea a los guardias y le pasa al cliente donde están
            {
                networkEvent->getInitGPos(&guardPos, &guardsDiePos);    //Geteo su info y se la paso al modelo
                modelPointer->copyGuardInitPos(guardPos,guardsDiePos);
                networkInterface->sendPacket(ACK);                      //Respondo con un ack
                initPacketCount++;
            }
            break;
        case 5:
            if(networkEvent->getHeader() == START_INFO)         //Luego vienen de que tipo es cada tile, y la posición inicial de los jugadores
            {   
                networkEvent->getStartInfo(&tiles, &playersPos);    
                modelPointer->initBoard(tiles);                 //Se inicializa ya el board
                auxInitInfo[OTHER_PLAYER].initPos=playersPos;   //Y se pasa toda la info de los players al modelo
                auxInitInfo[THIS_PLAYER].initPos=playersPos;
                modelPointer->initPlayer(THIS_PLAYER,auxInitInfo[THIS_PLAYER].PlayerName,auxInitInfo[THIS_PLAYER].playersCharacter,auxInitInfo[THIS_PLAYER].initPos);
                modelPointer->initPlayer(OTHER_PLAYER,auxInitInfo[OTHER_PLAYER].PlayerName,auxInitInfo[OTHER_PLAYER].playersCharacter,auxInitInfo[OTHER_PLAYER].initPos);
                networkInterface->sendPacket(ACK);              //Se responde con un ack
                initPacketCount++;
            }
            break;
        case 6:
            if(networkEvent->getHeader() == YOU_START)          //Luego el server decide quien empieza.
            {
                initPacketCount=0;
                modelPointer->setInitTurn(THIS_PLAYER);         //Como el server dijo que el cliente empiece empieza el jugador de esta maquina
                status=PLAYING;
            }
            else if(networkEvent->getHeader() == I_START)
            {
                initPacketCount=0;
                modelPointer->setInitTurn(OTHER_PLAYER);         //Como el server dijo que el cliente empiece empieza el, the other player comienza jugando.
                networkInterface->sendPacket(ACK);              //Se le manda un ack para que el server sepa que le llegó el msj al cliente.
                status=PLAYING;
            }
            break;
        default:
            break;
    }
    if(initPacketCount==packetCountCopy)    //Si no fue modificado significa que no entró a un if, por ende hubo un paquete que no siguió las reglas del protocolo -> se cierra el programa.
        quit=true;
}

void BurgleBrosController::serverInitRoutine(NetworkED *networkEvent)
{
    unsigned int packetCountCopy=initPacketCount;   //Saco una copia del número de paquete de inicialización
    CardLocation guardPos,guardsDiePos, playersPos;
    vector<CardName> tiles;
    switch(initPacketCount)
    {
        case 0:
            if(networkEvent->getHeader() == NAME_IS)   //Primero el client recibe el paquete name is del cliente. (Había mandado name antes el server).
            {
                auxInitInfo[OTHER_PLAYER].PlayerName=networkEvent->getName();   //Guarda el nombre del otro
                networkInterface->sendPacket(ACK);      //Al cual le responde con su nombre 
                initPacketCount++;
            }
            break;
        case 1:
            if(networkEvent->getHeader() == NAME)       //El cliente le pide al server su name
            {
                networkInterface->sendName(thisPlayerName);     //El server se lo devuelve.
                initPacketCount++;
            }
            break;
        case 2:
            if(networkEvent->getHeader() == ACK)        //El cliente ya sabe el nombre del server
            {
                auxInitInfo[THIS_PLAYER].playersCharacter=getRandomCharacter(); //ENtonces se obtiene un character aleatorio
                networkInterface->sendChar(auxInitInfo[THIS_PLAYER].playersCharacter); // se lo manda al client
                initPacketCount++;
            }
            break;
        case 3:
            if(networkEvent->getHeader() == I_AM)       //EL cliente manda el character que escogió el.
            {
                auxInitInfo[OTHER_PLAYER].playersCharacter= networkEvent->getCharacter();     //Se obtiene ese character
                modelPointer->generateGuardInitPos(&guardPos, &guardsDiePos);           //Se inicializa el guardia del primer piso
                networkInterface->sendInitGPos(guardPos,guardsDiePos);          //Le manda al cliente donde se inicializó el guardia y su dado.
                initPacketCount++;
            }
        case 4:
            if(networkEvent->getHeader() == ACK)
            {
                modelPointer->initBoard(tiles);
                auxInitInfo[THIS_PLAYER].initPos=getRandomCardLocation(modelPointer->getInfo2DrawGuard(0).position, 0); // EN el piso 0 empiezan
                auxInitInfo[OTHER_PLAYER].initPos= auxInitInfo[THIS_PLAYER].initPos;    //Los dos empiezan en la misma posición
                networkInterface->sendStartInfo(tiles, auxInitInfo[THIS_PLAYER].initPos);   //Se manda la información inicial de los tiles y la posición inicial de los jugadores
                modelPointer->initPlayer(THIS_PLAYER,auxInitInfo[THIS_PLAYER].PlayerName,auxInitInfo[THIS_PLAYER].playersCharacter,auxInitInfo[THIS_PLAYER].initPos); //Se inicializan los jugadores con los datos que veníamos guardando en los anteriores mensajes.
                modelPointer->initPlayer(OTHER_PLAYER,auxInitInfo[OTHER_PLAYER].PlayerName,auxInitInfo[OTHER_PLAYER].playersCharacter,auxInitInfo[OTHER_PLAYER].initPos);
                initPacketCount++;
            }
            break;
        case 5:
            if(networkEvent->getHeader() == ACK)        //Al recibir este ack, ya hay que decidir quien juega
            {
                if(rand()%2)
                {
                    networkInterface->sendPacket(YOU_START);    //Si empieza el cliente, se lo dice y ya termina su fase de inicialización.
                    initPacketCount=0;
                    modelPointer->setInitTurn(OTHER_PLAYER);
                    status=PLAYING;
                }
                else
                {
                    networkInterface->sendPacket(I_START);    //Si empieza el server, espera a que le llegue el ack para empezar a jugar
                    initPacketCount++;
                }
            }
            break;
        case 6:
            if(networkEvent->getHeader() == ACK)
            {
                modelPointer->setInitTurn(THIS_PLAYER);
                initPacketCount=0;
                status=PLAYING;
            }
            break;
            
    }
    if(initPacketCount==packetCountCopy)    //Si no fue modificado significa que no entró a un if, por ende hubo un paquete que no siguió las reglas del protocolo -> se cierra el programa.
        quit=true;
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

