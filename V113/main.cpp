/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: javier
 *
 * Created on December 29, 2016, 4:15 PM
 */

#include <cstdlib>
#include "BurgleBrosModel.h"
#include "BurgleBrosView.h"
#include "BurgleBrosSound.h"
#include "LibsInit.h"
#include "GUI.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    srand(time(NULL));
    allegro_startup();
    BurgleBrosModel model;
    BurgleBrosView view;
    BurgleBrosController controller;
    GUI gui;
    BurgleBrosSound sound;
    view.ViewInit(&model);
    view.update(&model);
    
    model.attachView(&view);
    controller.attachModel(&model);
    controller.attachView(&view);
    gui.atachController(&controller);
    model.attachController(&controller);
    model.attachSoundManager(&sound);
    
    while(gui.gameStillPlaying())
    {
        if(gui.hayEvento())
            gui.parseEvento();
    }
    
    return 0;
}

