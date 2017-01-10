/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicWall.h
 * Author: ubuntu
 *
 * Created on January 9, 2017, 9:03 PM
 */

#ifndef GRAPHICWALL_H
#define GRAPHICWALL_H

#include "GraphicItem.h"


class GraphicWall : public GraphicItem{
public:
    GraphicWall();
    GraphicWall(const GraphicWall& orig);
    virtual ~GraphicWall();
    ItemInfo IAm() override;
    void setLocation(CardLocation front, CardLocation rear);
    virtual void draw();

private:

};

#endif /* GRAPHICWALL_H */

