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
void GraphicPlayerCard::draw()
{
    if(whichPlayer==THIS_PLAYER_ACTION)
    {
        al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),
                STEALTH_TOKEN_WIDTH,totalHeight - STEALTH_TOKEN_HEIGHT - 200,200,200,0);
        for(unsigned int i=0; i <(lives-1); i++)
            al_draw_scaled_bitmap(stealthToken,0,0,al_get_bitmap_width(stealthToken),al_get_bitmap_height(stealthToken),
                    STEALTH_TOKEN_WIDTH + 200 + 20, totalHeight - STEALTH_TOKEN_HEIGHT - 200 + i * STEALTH_TOKEN_HEIGHT,STEALTH_TOKEN_WIDTH,STEALTH_TOKEN_HEIGHT,0);
    }
    else
    {
        al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),
                totalWidth - STEALTH_TOKEN_WIDTH - 200,totalHeight - STEALTH_TOKEN_HEIGHT - 200,200,200,0);
        for(unsigned int i=0; i <(lives-1); i++)
            al_draw_scaled_bitmap(stealthToken,0,0,al_get_bitmap_width(stealthToken),al_get_bitmap_height(stealthToken),
                    totalWidth - 2*STEALTH_TOKEN_WIDTH - 200 - 20,totalHeight - STEALTH_TOKEN_HEIGHT - 200 + i * STEALTH_TOKEN_HEIGHT,STEALTH_TOKEN_WIDTH,STEALTH_TOKEN_HEIGHT,0);
    }
}
clickItem GraphicPlayerCard::IAm()
{
    return CHAR_CARD;
}


