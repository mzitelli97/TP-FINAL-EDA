/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BurgleBrosController.h
 * Author: javier
 *
 * Created on December 29, 2016, 5:34 PM
 */

#ifndef BURGLEBROSCONTROLLER_H
#define BURGLEBROSCONTROLLER_H
#include "BurgleBrosModel.h"
#include "BurgleBrosView.h"
#include "EventData.h"
#include "NetworkED.h"
#include "Controller.h"
#include "NetworkInterface.h"

typedef enum{INITIALIZING, PLAYING, GAME_ENDED}GameStatus;

typedef enum{USER_QUIT, GAME_WON}QuitCause;

typedef struct
{
    string PlayerName;
    CharacterName playersCharacter;
    CardLocation initPos;
}AuxInitInfo;


#define DEFAULT_WIN_MSG "WON!","You have won the game","Now that youve won the game, you can choose if either play again or quit.","Play again","Quit"

class BurgleBrosController:public Controller {
public:
    BurgleBrosController();
    BurgleBrosController(const BurgleBrosController& orig);
    void attachNetworkInterface(NetworkInterface * p2NetworkInterface);
    void setCommunicationRoleNThisPlayerName(CommunicationRole communicationRole, string name);
    void attachModel(BurgleBrosModel *gamePointer);
    void attachView(BurgleBrosView *view);
    bool checkIfGameFinished();
    void parseMouseEvent(EventData *mouseEvent);
    void parseNetworkEvent(EventData *networkEvent);
    virtual string askForSpentOK(vector<string> &message);
    virtual ~BurgleBrosController();
private:
    void clientInitRoutine(NetworkED *networkEvent);
    void serverInitRoutine(NetworkED *networkEvent);
    void interpretNetworkAction(NetworkED *networkEvent);
    void interpretAction(string action, CardLocation location);
    void checkGameStatus();
    NetworkInterface * networkInterface;
    CommunicationRole communicationRole;
    unsigned int initPacketCount;
    AuxInitInfo auxInitInfo[NUMBER_OF_PLAYERS];     
    BurgleBrosModel *modelPointer;
    BurgleBrosView *view;
    string thisPlayerName;
    bool quit;
    GameStatus status;
    QuitCause quitCause;
};

#endif /* BURGLEBROSCONTROLLER_H */

