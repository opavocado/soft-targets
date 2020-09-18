/*
  Target.h - Library for controlling a Target (hopefully) painlessly
  Created by Nicolas Verdicchio, September 09, 2020.
*/
#ifndef Target_h
#define Target_h

#include "Arduino.h"

enum TargetState {Off, StandBy, Hit};
enum LedColor {Red, Green, None};

class Target
{
  public:
    Target(int piezoPin, int ledRedPin, int ledGreenPin, int hitThreshold);
    void update(unsigned long currentTime);

    void enable();
    void disable();
    
    bool wasHit();

    // Get/Set
    void setState(TargetState state);
    TargetState getState();
    
    int getLastReadValue();

    void setHitThreshold(int hitThreshold);
    int getHitThreshold();

  private:
    int piezoPin;
    int ledRedPin;
    int ledGreenPin;
    int lastReadValue;
    int hitThreshold;
    bool hitRegistered;
    unsigned long lastReadValueTime;
    unsigned long lastTransitionTime;
    TargetState currentState;
    const unsigned long defaultHitTime = 100; // 1/10 of a sec of showing green light before turning off

    void transitionToOffState();
    void handleOffState();
    
    void transitionToStandByState();
    void handleStandByState();

    void transitionToHitState();
    void handleHitState();

    void setLedColor(LedColor color);
};

#endif