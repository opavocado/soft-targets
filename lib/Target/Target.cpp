#include "Arduino.h"
#include "Target.h"

Target::Target(int piezoPin, int ledRedPin, int ledGreenPin)
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
    lastTransitionTime = 0;
    currentState = Off;
}

void Target::update(unsigned long currentTime)
{
    /*
    // If last tone duration has conluded AND there's still something on the queue
    if(currentTime >= (lastPlayedToneTime + currentToneDuration) && toneQueue.size() > 0) {
        // Stop all sounds
        noTone(pin);
        
        // Obtain next tone
        Tone currentTone = toneQueue.shift();

        // Play next tone if it's note isn't silent
        int currentNote = currentTone.getNote();
        if(SILENT != currentNote) {
            tone(pin, currentNote, currentTone.getDuration());
        }
        
        // Update time stamp and note duration
        lastPlayedToneTime = currentTime;
        currentToneDuration = currentTone.getDuration();
        
        // Release memory of tone - is this needed? Tone wasn't generated with new
        //delete(&currentTone);
    }
    */
}

void Target::setState(TargetState state){

}

