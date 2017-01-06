/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicPlayer.h
 * Author: carlos
 *
 * Created on 30 de diciembre de 2016, 00:40
 */

#ifndef GRAPHICPLAYER_H
#define GRAPHICPLAYER_H

#include "GraphicItem.h"


using namespace std;

class GraphicPlayer : public GraphicItem{
public:
    GraphicPlayer(ALLEGRO_BITMAP * image, CardLocation location,unsigned int width, unsigned int height);
    GraphicPlayer(const GraphicPlayer& orig);
    virtual ~GraphicPlayer();
    void setLocation(CardLocation l);
    virtual clickItem IAm();
private:
    GraphicPlayer();

};

#endif /* GRAPHICPLAYER_H */

