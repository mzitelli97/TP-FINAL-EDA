/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BurgleBrosSound.cpp
 * Author: javier
 * 
 * Created on January 11, 2017, 2:17 AM
 */

#include "BurgleBrosSound.h"

using namespace std;

BurgleBrosSound::BurgleBrosSound() {
    bool test;
    initOK=loadAllSamples();
    al_reserve_samples(1);
    if(initOK)
         test=al_play_sample(samples.front(), 1.0, 0.0, 1.0,ALLEGRO_PLAYMODE_LOOP, NULL);
    cout<<(unsigned int)test;
}

BurgleBrosSound::BurgleBrosSound(const BurgleBrosSound& orig) {
    
}

void BurgleBrosSound::playSoundEffect(SoundEffect effect)
{
    
}
bool BurgleBrosSound::loadAllSamples()
{
    bool retVal=false;
    string fullPath = (string)MUSIC_FOLDER + (string)THEME_1 + (string)THEMES_EXTENSION;
    ALLEGRO_SAMPLE * temp = al_load_sample(fullPath.c_str());
    if(temp != nullptr)
    {
        samples.push_back(temp);
        retVal=true;
    }
    return retVal;
}

BurgleBrosSound::~BurgleBrosSound() {
}

