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

#include <list>

#include "BurgleBrosSound.h"

using namespace std;

BurgleBrosSound::BurgleBrosSound() {
    bool test;
    initOK=loadAllSamples();
    al_reserve_samples(3);              //para poder reproducir 3 sonidos a la vez(no va a haber mas)
    if(initOK)
         test=al_play_sample(samples.front(), 1.0, 0.0, 1.0,ALLEGRO_PLAYMODE_LOOP, NULL);   //musica de fondo
    cout<<(unsigned int)test;
    onMute = false;
}

BurgleBrosSound::BurgleBrosSound(const BurgleBrosSound& orig) {
    
}

void BurgleBrosSound::playSoundEffect(SoundEffect effect)
{
    if(!onMute && initOK)
        al_play_sample(samples[(int)effect+1], 1.5, 0.0, 1.0,ALLEGRO_PLAYMODE_ONCE, NULL);  //+1 por la musica de fondo
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
    for(int i = (int)ALARM_TRIGGERED; i <= (int)WON; i++)
    {
        fullPath = (string)SOUNDS_FOLDER + soundEffect2String((SoundEffect)i) + (string)THEMES_EXTENSION;
        temp = al_load_sample(fullPath.c_str());
        if(temp != nullptr)
        {
            samples.push_back(temp);
            retVal=true;
        }
        else { retVal = false; break; }
    }
    return retVal;
}

string BurgleBrosSound::soundEffect2String(SoundEffect effect)
{
    string retVal = "";
    switch(effect)
    {
        case ALARM_TRIGGERED: retVal += "Alarm"; break;
        case SAFE_CRACKED: retVal += "Safe"; break;
        case KEYPAD_OPENED: retVal += "Keypad"; break;
        case STAIRS_STEPS: retVal += "Stairs"; break;
        case CHIHUAHUA_BARKS: retVal += "Bark"; break;
        case LOST: retVal += "Lost"; break;
        case WON: retVal += "Chopper"; break;
        default: retVal += "ERROR"; break;
    }
    return retVal;
}

void BurgleBrosSound::toggleMute()
{
    onMute ^= true;
    if(!onMute)
        al_play_sample(samples.front(), 1.0, 0.0, 1.0,ALLEGRO_PLAYMODE_LOOP, NULL);
    else
        al_stop_samples();
}

void BurgleBrosSound::reset()
{
    onMute = false;
    al_stop_samples();              //paro todos los sonidos que pueda haber
    al_play_sample(samples.front(), 1.0, 0.0, 1.0,ALLEGRO_PLAYMODE_LOOP, NULL); //reinicio la musica de fondo
}


BurgleBrosSound::~BurgleBrosSound() {
}

