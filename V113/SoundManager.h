/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SoundManager.h
 * Author: javier
 *
 * Created on January 11, 2017, 2:14 AM
 */

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

typedef enum{ALARM_TRIGGERED, SAFE_CRACKED, KEYPAD_OPENED, STAIRS_STEPS, CHIHUAHUA_BARKS, LOST, WON}SoundEffect;

class SoundManager {
public:
    SoundManager();
    SoundManager(const SoundManager& orig);
    virtual void playSoundEffect(SoundEffect effect)=0;
    virtual ~SoundManager();
private:

};

#endif /* SOUNDMANAGER_H */

