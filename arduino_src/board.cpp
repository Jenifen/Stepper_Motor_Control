
#include "board.h"
#include "Arduino.h"

// Constructor
Controller::Controller() {
  // Empty constructor
}

void Controller::begin()
{
    pinMode(DRIVER_DIR_PIN, OUTPUT);
    pinMode(DRIVER_PUL_PIN, OUTPUT);

}

void Controller::init()
{
    delay(STARTUP_DELAY);
    Serial.println("\n [respirator Starting]\n");
    
}


void Controller::changeDirection(Direction &dir)
{
    digitalWrite(DRIVER_DIR_PIN, dir);
    #ifdef DEBUG_PRINTS
        Serial.println("\n Direction Changed \n");
    #endif
}
