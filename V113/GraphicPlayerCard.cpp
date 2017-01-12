/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicPlayerCard.cpp
 * Author: carlos
 * 
 * Created on 30 de diciembre de 2016, 02:29
 */

#include "GraphicPlayerCard.h"

#define STEALTH_TOKEN_WIDTH (totalWidth/40.0)
#define STEALTH_TOKEN_HEIGHT (totalHeight/20.0)
#define CARD_WIDTH (totalWidth/9.0)
#define CARD_HEIGHT (totalHeight/5.4)
#define SEPARATION (totalWidth/90.0)


GraphicPlayerCard::GraphicPlayerCard(ALLEGRO_BITMAP * image, ALLEGRO_BITMAP * stealthTokenImg, unsigned int lives, std::string name, ActionOrigin whichPlayer,unsigned int width,unsigned int height)
{
    this->image=image;
    this->lives=lives;
    this->name=name;
    this->whichPlayer=whichPlayer;
    setScreenDimentions(width, height);
    stealthToken= stealthTokenImg;
}
void  GraphicPlayerCard:: setLives(unsigned int livesNumber)
{   
    if(livesNumber<4 && livesNumber>0)
        lives=livesNumber;
}

void GraphicPlayerCard::setPosition()
{
    if(zoomed)
    {
        width = CARD_WIDTH*2.5;
        height = CARD_HEIGHT*2.5;
        min.x = width/3.0;
        min.y = height/3.0;
    }
    else
    {
        width = CARD_WIDTH;
        height = CARD_HEIGHT;
        if(whichPlayer == THIS_PLAYER_ACTION)
            min.x = STEALTH_TOKEN_WIDTH;
        else 
            min.x = totalWidth - STEALTH_TOKEN_WIDTH - width;
        min.y = totalHeight - STEALTH_TOKEN_HEIGHT - height;
    }
    max.x = min.x + width;
    max.y = min.y + height;
    
}

void GraphicPlayerCard::draw()
{
    setPosition();
    if(whichPlayer==THIS_PLAYER_ACTION)
    {
        al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),
                min.x,min.y,width,height,0);
        for(unsigned int i=0; i <(lives-1); i++)
            al_draw_scaled_bitmap(stealthToken,0,0,al_get_bitmap_width(stealthToken),al_get_bitmap_height(stealthToken),
                    min.x + width + SEPARATION, min.y + i * STEALTH_TOKEN_HEIGHT,STEALTH_TOKEN_WIDTH,STEALTH_TOKEN_HEIGHT,0);
    }
    else
    {
        al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),
                min.x,min.y,width,height,0);
        for(unsigned int i=0; i <(lives-1); i++)
            al_draw_scaled_bitmap(stealthToken,0,0,al_get_bitmap_width(stealthToken),al_get_bitmap_height(stealthToken),
                    min.x - STEALTH_TOKEN_WIDTH - SEPARATION,min.y + i * STEALTH_TOKEN_HEIGHT,STEALTH_TOKEN_WIDTH,STEALTH_TOKEN_HEIGHT,0);
    }
}
ItemInfo GraphicPlayerCard::IAm()
{
    ItemInfo retVal;
    retVal.type = CHAR_CARD_CLICK;
    retVal.info = &whichPlayer;
    return retVal;
}


