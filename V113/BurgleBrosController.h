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

class BurgleBrosController {
public:
    BurgleBrosController();
    BurgleBrosController(const BurgleBrosController& orig);
    void attachModel(BurgleBrosModel *gamePointer);
    void attachView(BurgleBrosView *view);
    void parseMouseEvent(EventData *mouseEvent);
    virtual ~BurgleBrosController();
private:
    BurgleBrosModel *modelPointer;
    BurgleBrosView *view;
};

#endif /* BURGLEBROSCONTROLLER_H */

