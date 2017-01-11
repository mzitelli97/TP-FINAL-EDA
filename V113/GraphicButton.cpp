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
#include "ImageLoader.h"
#include "GraphicItem.h"

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

void GraphicButton::draw() {

    //if(image != nullptr)
     //   al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),min.x,min.y,width,height,0);
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
GraphicButton::~GraphicButton() {
}
