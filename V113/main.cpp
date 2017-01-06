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
#include "LibsInit.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    srand(time(NULL));
    BurgleBrosModel model;
    allegro_startup();
    BurgleBrosView view;
    view.ViewInit(&model);
    list<string> options;
    options.push_back("MOVE");
    options.push_back("PEEK");
    options.push_back("USE TOKEN");
    //options.push_back("OFFER LOOT");
    
    view.showMenu(options, {500,500}, {0,0,0});
    view.update(&model);
    al_rest(5);
    clickItem item = view.itemFromClick({50,50});
    cout << item << endl;
    model.move(THIS_PLAYER_ACTION, {0,1,0});
    view.update(&model);
    al_rest(5);
    return 0;
}

