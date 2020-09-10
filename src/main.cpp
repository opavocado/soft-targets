#include <Arduino.h>
#include <Target.h>

#define CONNECTED_TARGETS 3   // Increase value if more targets have been connected

// Sensors
#define PIEZO_1_PIN A0
#define PIEZO_2_PIN A1
#define PIEZO_3_PIN A2

#define DEFAULT_HIT_THRESHOLD 30


// LEDs
#define LED_R_1_PIN 2
#define LED_G_1_PIN 3

#define LED_R_2_PIN 4
#define LED_G_2_PIN 5

#define LED_R_3_PIN 6
#define LED_G_3_PIN 7

const int led_pins[] = {LED_R_1_PIN, LED_G_1_PIN,
                        LED_R_2_PIN, LED_G_2_PIN,
                        LED_R_3_PIN, LED_G_3_PIN,
                      };

bool hitRegistered = false;

int enabledTargetIndex = 0;

Target* targets[CONNECTED_TARGETS];

unsigned long currentTime = 0;

void setup() {

  // Initialize - TODO REFACTOR STATIC ASSIGNMENTS - system should detect connected targets and adapt accordingly
  targets[0] = new Target(PIEZO_1_PIN, LED_R_1_PIN, LED_G_1_PIN, DEFAULT_HIT_THRESHOLD);
  targets[1] = new Target(PIEZO_2_PIN, LED_R_2_PIN, LED_G_2_PIN, DEFAULT_HIT_THRESHOLD);
  targets[2] = new Target(PIEZO_3_PIN, LED_R_3_PIN, LED_G_3_PIN, DEFAULT_HIT_THRESHOLD);

  // Pick Random Target
  enabledTargetIndex = rand() % CONNECTED_TARGETS;

  // Set Target To Stand By
  targets[enabledTargetIndex]->enable();

  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  // Read Sensors & Update Targets
  for(int i = 0; i < CONNECTED_TARGETS; i++) {
    targets[i]->update(currentTime);
  }
  
  // If the Enabled Target was hit, pick a new one
  if(targets[enabledTargetIndex]->wasHit()) {
    int newTargetIndex = enabledTargetIndex;
    
    // Randomly pick a new target that is different from the one that was hit
    while (newTargetIndex == enabledTargetIndex) {
      newTargetIndex = rand() % CONNECTED_TARGETS;
    } 
    enabledTargetIndex = newTargetIndex;
    targets[enabledTargetIndex]->enable();
  }

  // Update All Targets (send timer, and let them calculate whether they should transition from Hit to Off)
}

void turnOffAllLeds() {
  // Turns off all LEDs
  for(int x = 0; x < 6; x++) {
    digitalWrite(led_pins[x], HIGH);
  } 
}
