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
#include "ImageLoader.h"        //check if this is necessary(this include the model)
#include "LibsInit.h"

typedef struct
{
    double x;
    double y;
}Point;

typedef struct
{
    clickItem type;
    void * info;
}ItemInfo;

#define FLOOR_WIDTH (totalWidth/4.5)
#define FLOOR_HEIGHT (totalHeight/2.25)
#define SPACE_BETWEEN_FLOORS (totalWidth/20.0)
#define TOTAL_FLOORS_WIDTH (3.0 * FLOOR_WIDTH + 3.0 * SPACE_BETWEEN_FLOORS)         //no configurable
#define FLOOR_MIN_X (totalWidth/20.0)
#define FLOOR_MIN_Y (totalHeight/10.0)
#define TILES_HEIGHT (FLOOR_HEIGHT/(float)FLOOR_RAWS)
#define TILES_WIDTH  (FLOOR_WIDTH/(float)FLOOR_COLUMNS)

class GraphicItem {
public:
    GraphicItem();
    GraphicItem(const GraphicItem& orig);
    GraphicItem(Point min, Point max);
    GraphicItem(Point center, double width, double height);
    void setScreenDimentions(unsigned int totalWidth, unsigned int totalHeight);
    virtual ~GraphicItem();
    bool isPointIn(Point point);
    bool isZoomed();
    virtual void draw();
    virtual void toggleZoom();
    virtual ItemInfo IAm() = 0;
protected:
    void logic2GraphicCardLocation(CardLocation location);
    ALLEGRO_BITMAP * image;
    Point min;
    Point max;
    Point center;
    double width;
    double height;
    unsigned int totalWidth, totalHeight;
    bool zoomed;
};

#endif /* GRAPHICITEM_H */

