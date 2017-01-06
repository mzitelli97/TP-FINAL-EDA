/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   View.h
 * Author: javier
 *
 * Created on December 24, 2016, 5:09 PM
 */

#ifndef VIEW_H
#define VIEW_H

#include "BurgleBrosModel.h"

typedef enum {  TILE = 0, LOOT_CARDS, CHAR_CARD, GUARD_CARDS, ZOOM, EXTRA_DICE, MENU_ITEM, VOL_BUTTON, HELP_BUTTON, EXIT_BUTTON, NO_ITEM} clickItem;

class View {
public:
    View();
    View(const View& orig);
    virtual ~View();
    virtual void update(BurgleBrosModel * model) = 0;
private:

};

#endif /* VIEW_H */

