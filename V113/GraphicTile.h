/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicTile.h
 * Author: carlos
 *
 * Created on 29 de diciembre de 2016, 20:46
 */

#ifndef GRAPHICTILE_H
#define GRAPHICTILE_H

#include "GraphicItem.h"
#include "BurgleBrosCard.h"

class GraphicTile : public GraphicItem{
public:
   // GraphicTile();
    GraphicTile(ALLEGRO_BITMAP * front,ALLEGRO_BITMAP * back,CardLocation location,unsigned int width,unsigned int height);
    bool isVisible();
    void setVisible(ALLEGRO_BITMAP * safeNumber);
    CardLocation getLocation();
    virtual ~GraphicTile();
    virtual ItemInfo IAm();
    virtual void draw();
    void toggleZoom();
private:
    //clickItem me;
    void setPosition(CardLocation location);
    CardLocation location;
    bool Visible;
    ALLEGRO_BITMAP * back;
    ALLEGRO_BITMAP * safeNumber;
};

#endif /* GRAPHICTILE_H */

