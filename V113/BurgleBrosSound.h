/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BurgleBrosSound.h
 * Author: javier
 *
 * Created on January 11, 2017, 2:17 AM
 */

#ifndef BURGLEBROSSOUND_H
#define BURGLEBROSSOUND_H

#include "SoundManager.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <iostream>
#include <vector>

#define MUSIC_FOLDER "Music/"
#define SOUNDS_FOLDER "Sounds/"


#define THEME_1 "Pink panther"

#define THEMES_EXTENSION ".wav"

using namespace std;

class BurgleBrosSound:public SoundManager {
public:
    BurgleBrosSound();
    BurgleBrosSound(const BurgleBrosSound& orig);
    virtual void playSoundEffect(SoundEffect effect);
    virtual void toggleMute();
    virtual ~BurgleBrosSound();
private:
    vector<ALLEGRO_SAMPLE *> samples;
    string soundEffect2String(SoundEffect effect);
    bool loadAllSamples();
    bool initOK;
    bool onMute;

};

#endif /* BURGLEBROSSOUND_H */

