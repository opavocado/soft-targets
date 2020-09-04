#include <Arduino.h>
#include <Target.h>

#define CONNECTED_TARGETS 3   // Increase value if more targets have been connected

// Sensors
#define PIEZO_1_PIN A0
#define PIEZO_2_PIN A1
#define PIEZO_3_PIN A2


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

const int hitThreshold = 50;
bool hitRegistered = false;

Target* targets[CONNECTED_TARGETS];

unsigned long currentTime = 0;

void setup() {

  // Initialize - TODO REFACTOR STATIC ASSIGNMENTS - system should detect connected targets and adapt accordingly
  targets[0] = new Target(PIEZO_1_PIN, LED_R_1_PIN, LED_G_1_PIN);
  targets[1] = new Target(PIEZO_2_PIN, LED_R_2_PIN, LED_G_2_PIN);
  targets[2] = new Target(PIEZO_3_PIN, LED_R_3_PIN, LED_G_3_PIN);

  // Pick Random Target
  int randomIndex = rand() % CONNECTED_TARGETS;

  // Set Target To Stand By
  targets[randomIndex]->setState(Target::StandBy);

  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  // Read Sensors
  // If Stand by Target was hit, set it to Hit
    // Set a new target to Stand By
  // Update All Targets (send timer, and let them calculate whether they should transition from Hit to Off)
  Serial.println("Online");
  delay(250);
}

void turnOffAllLeds() {
  // Turns off all LEDs
  for(int x = 0; x < 6; x++) {
    digitalWrite(led_pins[x], HIGH);
  } 
}
