/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicButton.cpp
 * Author: javier
 * 
 * Created on January 11, 2017, 1:23 AM
 */

#include "GraphicButton.h"

#define BUTTON_WIDTH 20.0//(totalWidth/)
#define BUTTON_HEIGHT 20.0//(totalHeight)

GraphicButton::GraphicButton() {
}

GraphicButton::GraphicButton(const GraphicButton& orig) {
}

GraphicButton::GraphicButton(ALLEGRO_BITMAP * buttonImage,ALLEGRO_BITMAP * unMuteimage, buttonAction identifier, unsigned int width, unsigned int height)
{
    this->info=nullptr;          //Por ahora dejo esto asi
    this->button=identifier;
    this->image=buttonImage;
    this->image_2=unMuteimage;
    setScreenDimentions(width,height);
    zoomed = false;
}



ItemInfo GraphicButton::IAm()
{
    if(button == MUTE_BUTTON || button==UNMUTE_BUTTON)
        return {VOL_BUTTON_CLICK,nullptr};
    if(button == HELP_BUTTON)
        return {HELP_BUTTON_CLICK,nullptr};
    if(button == ZOOM_BUTTON)
        return {ZOOM_CLICK,&zoomFloor};
    if(button == QUIT_BUTTON)
        return {EXIT_BUTTON_CLICK,nullptr};
}

buttonAction GraphicButton::getButtonIdentifier()
{
    return button;
}

void GraphicButton::setZoomFloor(unsigned int floor)
{
    this->zoomFloor=floor;
}

void GraphicButton::toggleMute()
{
    if(button==MUTE_BUTTON)
        button=UNMUTE_BUTTON;
    if(button==UNMUTE_BUTTON)
        button=MUTE_BUTTON;
}

void GraphicButton::setLocation()
{
    logic2GraphicCardLocation({zoomFloor,3,3});
    min.x += (width + 10.0);
    min.y += (height - BUTTON_HEIGHT);
    width = BUTTON_WIDTH;
    height = BUTTON_HEIGHT;
    max.x = min.x + width;
    max.y = min.y + height;
}

GraphicButton::~GraphicButton() {
}
