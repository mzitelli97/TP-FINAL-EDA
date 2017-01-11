/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicButton.h
 * Author: javier
 *
 * Created on January 11, 2017, 1:23 AM
 */

#ifndef GRAPHICBUTTON_H
#define GRAPHICBUTTON_H
#include "GraphicItem.h"

typedef struct{
   int aux; 
}infoButton;

class GraphicButton: public GraphicItem {
public:
    GraphicButton();
    GraphicButton(const GraphicButton& orig);
    GraphicButton(ALLEGRO_BITMAP * buttonImage,ALLEGRO_BITMAP * unMuteimage, buttonAction identifier, unsigned int width, unsigned int height);
    void setZoomFloor(unsigned int floor);
    buttonAction getButtonIdentifier();
    void toggleMute();
    void setLocation();
    ItemInfo IAm() override;
    virtual ~GraphicButton();
    
private:
    buttonAction button;
    unsigned int zoomFloor;
    ALLEGRO_BITMAP * image_2;
    infoButton *info;
};

#endif /* GRAPHICBUTTON_H */

