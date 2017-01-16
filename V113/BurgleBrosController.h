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
#include "Controller.h"

typedef enum{USER_QUIT, GAME_WON}QuitCause;

#define DEFAULT_WIN_MSG "WON!","You have won the game","Now that youve won the game, you can choose if either play again or quit.","Play again","Quit"

class BurgleBrosController:public Controller {
public:
    BurgleBrosController();
    BurgleBrosController(const BurgleBrosController& orig);
    void attachModel(BurgleBrosModel *gamePointer);
    void attachView(BurgleBrosView *view);
    bool checkIfGameFinished();
    void parseMouseEvent(EventData *mouseEvent);
    virtual string askForSpentOK(vector<string> &message);
    virtual ~BurgleBrosController();
private:
    void interpretAction(string action, CardLocation location);
    void checkGameStatus();
    BurgleBrosModel *modelPointer;
    BurgleBrosView *view;
    bool gameIsOver;
    QuitCause quitCause;
};

#endif /* BURGLEBROSCONTROLLER_H */

