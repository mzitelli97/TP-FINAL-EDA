/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Controller.h
 * Author: javier
 *
 * Created on January 10, 2017, 12:41 AM
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>
#include <vector>

using namespace std;

class Controller {
public:
    Controller();
    Controller(const Controller& orig);
    virtual bool askForSpentOK(vector<string> &message)=0;
    virtual ~Controller();
private:

};

#endif /* CONTROLLER_H */

