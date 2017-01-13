/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicPlayerCard.h
 * Author: carlos
 *
 * Created on 30 de diciembre de 2016, 02:29
 */

#ifndef GRAPHICPLAYERCARD_H
#define GRAPHICPLAYERCARD_H

#include "GraphicItem.h"


class GraphicPlayerCard : public GraphicItem{
public:
    GraphicPlayerCard(ALLEGRO_BITMAP * image, ALLEGRO_BITMAP * stealthTokenImg,unsigned int lives, std::string name, ActionOrigin whichPlayer,unsigned int width,unsigned int height);
    void setLivesAndActions(unsigned int livesNumber,unsigned int actions);
    void setFont(ALLEGRO_FONT * font);
    void setTurn(bool turn);
    ItemInfo IAm() override;
    void draw() override;
    virtual ~GraphicPlayerCard() {};
private:
    void setPosition();
    unsigned int lives;
    unsigned int actions;
    bool turn;
    Point actionsPos;
    Point namePos;
    string name;
    ALLEGRO_BITMAP * stealthToken; 
    ActionOrigin whichPlayer;
    ALLEGRO_FONT * font;
};

#endif /* GRAPHICPLAYERCARD_H */

