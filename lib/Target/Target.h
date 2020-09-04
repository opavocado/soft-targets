/*
  Target.h - Library for controlling a Target (hopefully) painlessly
  Created by Nicolas Verdicchio, September 09, 2020.
*/
#ifndef Target_h
#define Target_h

#include "Arduino.h"


class Target
{
  public:
    Target(int piezoPin, int ledRedPin, int ledGreenPin);
    enum TargetState {Off, StandBy, Ready};
    void update(unsigned long currentTime);
    void setState(TargetState state);

  private:
    int piezoPin;
    int ledRedPin;
    int ledGreenPin;
    unsigned long lastTransitionTime;
    TargetState currentState;
};

#endif