/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicItem.h
 * Author: carlos
 *
 * Created on 29 de diciembre de 2016, 18:37
 */

#ifndef GRAPHICITEM_H
#define GRAPHICITEM_H

#include "View.h"
#include "ImageLoader.h"

typedef struct
{
    double x;
    double y;
}Point;

class GraphicItem {
public:
    GraphicItem();
    GraphicItem(const GraphicItem& orig);
    GraphicItem(Point min, Point max);
    GraphicItem(Point center, double width, double height);
    void setScreenDimentions(unsigned int totalWidth, unsigned int totalHeight);
    virtual ~GraphicItem();
    bool isPointIn(Point point);
    virtual void draw()=0;
    virtual clickItem IAm() = 0;
protected:
    ALLEGRO_BITMAP * image;
    Point min;
    Point max;
    Point center;
    double width;
    double height;
    unsigned int totalWidth, totalHeight;
    //bool alreadyUpdated;
};

#endif /* GRAPHICITEM_H */

