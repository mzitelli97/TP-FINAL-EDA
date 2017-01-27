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

typedef enum{INITIALIZING, PLAYING}GameStatus;
typedef enum{FIRST_DECIDING_PLAYER, SECOND_DECIDING_PLAYER}PlayAgainId;//Para cuando se decide jugar de vuelta y se toma como server o cliente, para diferenciarlos esta esto.
typedef enum{USER_QUIT, GAME_WON}QuitCause;

typedef struct
{
    string PlayerName;
    CharacterName playersCharacter;
    CardLocation initPos;
}AuxInitInfo;


#define DEFAULT_WIN_MSG "WON!","You have won the game","Now that youve won the game, you can choose if either play again or quit.","Play again","Quit"
#define DEFAULT_LOST_MSG "LOST!","You have lost the game","Now that youve lost the game, you can choose if either play again or quit.","Play again","Quit"
#define DEFAULT_PLAY_AGAIN_MSG "Play again?", "The game has finished", "The other Player has chosen to play again, do you agree?", "Play again", "Quit"

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
    string getUsersResponse(vector<string> &message);
    
    virtual ~BurgleBrosController();
private:
    void handlePlayAgain();
    void handleLootsExchange(NetworkED * networkEvent);
    void clientInitRoutine(NetworkED *networkEvent);
    void serverInitRoutine(NetworkED *networkEvent);
    void firstDecidedRoutine(NetworkED *networkEvent);
    void secondDecidedRoutine(NetworkED *networkEvent);
    void interpretNetworkAction(NetworkED *networkEvent);
    void doOnePacketAction(NetworkED *networkEvent);
    void interpretAction(string action, CardLocation location);
    void analizeIfModelRequiresMoreActions(NetworkED *networkEvent);
    void handleWonOrLost(PerezProtocolHeader msg);
    void checkGameStatus();
    void resetGame();
    NetworkInterface * networkInterface;
    bool firstInitDone;
    CommunicationRole communicationRole;
    unsigned int initPacketCount;
    AuxInitInfo auxInitInfo[NUMBER_OF_PLAYERS]; 
    list<NetworkED> packetToAnalize; //Para eventos como move, que necesita varios paquetes para ejecutarse completamente, esta ésta queue.
    BurgleBrosModel *modelPointer;
    BurgleBrosView *view;
    bool aMoveActionPending;
    bool iStarted;
    CardLocation previousMovingToLocation;
    string thisPlayerName;
    bool quit;
    PlayAgainId whichPlayer;
    GameStatus status;
    QuitCause quitCause;
    bool waiting4QuitAck;
};

#endif /* BURGLEBROSCONTROLLER_H */

