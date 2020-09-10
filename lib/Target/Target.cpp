#include "Arduino.h"
#include "Target.h"

Target::Target(int piezoPin, int ledRedPin, int ledGreenPin, int hitThreshold)
{
    // Store Pin numbers
    this->piezoPin = piezoPin; 
    this->ledRedPin = ledRedPin; 
    this->ledGreenPin = ledGreenPin;
    
    // Set pin modes
    pinMode(piezoPin, INPUT);
    pinMode(ledRedPin, OUTPUT);
    pinMode(ledGreenPin, OUTPUT);
    
    // Initialize attributes
    this->hitThreshold = hitThreshold;
    hitRegistered = false;
    lastReadValueTime = 0;
    lastTransitionTime = 0;
    currentState = Off;
}

void Target::update(unsigned long currentTime)
{
    // Read sensor & store value
    this->lastReadValue = analogRead(this->piezoPin);
    this->lastReadValueTime = currentTime;

    // Update State -- TODO REFACTOR WITH STATE PATTERN (lol never gonna happen)
    switch(currentState) {
        case TargetState::Off:
            handleOffState();
            break;
        case TargetState::StandBy:
            handleStandByState();
            break;
        case TargetState::Hit:
            handleHitState();
            break;
        default:
            // die
            break;
    }
}

// Used externally to set the target to Stand By
void Target::enable() {
    transitionToStandByState();
}

// Used externally to turn off the target
void Target::disable() {
    transitionToOffState();
}

/*
    - Experimental -
    Basically, this will return "true" for just the cycle in which the hit is registered and transitionToHitState() is executed.
    The first cycle through handleHitState() sets the hitRegistered field to "false"
 */
bool Target::wasHit() {
    return hitRegistered;
}

void Target::setLedColor(LedColor color) {
    switch(color) {
        case LedColor::Red:
            digitalWrite(ledRedPin, LOW);
            digitalWrite(ledGreenPin, HIGH);
            break;
        case LedColor::Green:
            digitalWrite(ledRedPin, HIGH);
            digitalWrite(ledGreenPin, LOW);
            break;
        case LedColor::None:
            digitalWrite(ledRedPin, HIGH);
            digitalWrite(ledGreenPin, HIGH);
            break;
    }
}

// State Handling //

// Off: LEDs are off, nothing else to do
void Target::handleOffState() {
    // Do nothing
}

// StandBy: Waiting to be hit
void Target::handleStandByState() {
    // Check if target was hit
    if(lastReadValue >= hitThreshold) {
        hitRegistered = true;
        transitionToHitState();
    }
}

// Hit: shows Green LED for a moment and transitions to Off
void Target::handleHitState() {
    hitRegistered = false;
    // Check for timer
    if(lastTransitionTime - lastReadValueTime > defaultHitTime) {
        transitionToOffState();
    }
}

// State Transitions //
void Target::transitionToOffState() {
    // Save transition state
    lastTransitionTime = lastReadValue;

    // Turn off LEDs
    setLedColor(LedColor::None);

}

void Target::transitionToStandByState() {
    // Save transition state
    lastTransitionTime = lastReadValue;

    // Turn on Green Light
    setLedColor(LedColor::Red);
}

void Target::transitionToHitState() {
    // Save transition state
    lastTransitionTime = lastReadValue;

    // Turn on Green Light
    setLedColor(LedColor::Green);
}



// Get/Set
void Target::setState(TargetState state){
    currentState = state;
}

TargetState Target::getState() {
    return currentState;
}

void Target::setHitThreshold(int hitThreshold) {
    this->hitThreshold = hitThreshold;
}

int Target::getHitThreshold() {
    return hitThreshold;
}