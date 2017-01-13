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

#define BUTTON_WIDTH (totalWidth/50.0)
#define BUTTON_HEIGHT BUTTON_WIDTH          //to make it a square

#define QUIT_CENTER_X   (39*(totalWidth/40))
#define QUIT_CENTER_Y   (totalWidth/60)

#define HELP_CENTER_X   (38*(totalWidth/40))
#define HELP_CENTER_Y   (totalWidth/60)

#define MUTE_CENTER_X   (37*(totalWidth/40))
#define MUTE_CENTER_Y   (totalWidth/60)

#define PASS_CENTER_X   (34*(totalWidth/40))
#define PASS_CENTER_Y   (totalWidth/60)
#define PASS_WIDTH      (totalWidth/15)
#define PASS_HEIGHT     (totalHeight/20)

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
    switch(button)
    {
        case QUIT_BUTTON:
            center.x=QUIT_CENTER_X;
            center.y=QUIT_CENTER_Y;
            this->width=BUTTON_WIDTH;
            this->height=BUTTON_HEIGHT; 
            break;
        case PASS_BUTTON:
            center.x=PASS_CENTER_X;
            center.y=PASS_CENTER_Y;
            this->width=PASS_WIDTH;
            this->height=PASS_HEIGHT; 
            break;
        case HELP_BUTTON:
            center.x = HELP_CENTER_X;
            center.y = HELP_CENTER_Y;
            this->width = BUTTON_WIDTH;
            this->height = BUTTON_HEIGHT;
            break;
        case MUTE_BUTTON:
            center.x = MUTE_CENTER_X;
            center.y = MUTE_CENTER_Y;
            this->width = BUTTON_WIDTH;
            this->height = BUTTON_HEIGHT;
            break;
        default:
            break;
    }
    min.x=center.x - (this->width)/2;
        max.x=center.x + (this->width)/2;
        min.y=center.y - (this->height)/2;
        max.y=center.y + (this->height)/2;
    
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
    if(button == PASS_BUTTON)
        return {PASS_BUTTON_CLICK,nullptr};
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
    if(button == ZOOM_BUTTON)
    {
        logic2GraphicCardLocation({zoomFloor,3,3});
        min.x += (width + BUTTON_WIDTH/3.5);
        min.y += (height - BUTTON_HEIGHT);
        width = BUTTON_WIDTH;
        height = BUTTON_HEIGHT;
        max.x = min.x + width;
        max.y = min.y + height;
    }
}

GraphicButton::~GraphicButton() {
}
