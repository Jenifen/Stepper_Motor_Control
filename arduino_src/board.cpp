
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
    pinMode(READY_PIN, INPUT_PULLUP);
    pinMode(STOP_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(STOP_PIN), Controller::Stop, FALLING);
    
    delay(STARTUP_DELAY);
    #ifdef DEBUG_PRINTS
        Serial.println("\n [respirator Starting]\n");
    #endif

}
void Controller::stop() const
{
    digitalWrite(DRIVER_PUL_PIN, LOW);
    digitalWrite(DRIVER_DIR_PIN, LOW);
    while(digitalRead(READY_PIN));
}


void Controller::setDirection(const Direction &dir)
{
    digitalWrite(DRIVER_DIR_PIN, dir);
    #ifdef DEBUG_PRINTS
        Serial.println("\n Direction Changed \n");
    #endif
}


bool Controller::getTimer()
{
    unsigned long currentMillis = millis();
    
    if (abs(currentMillis - previousMillis_) >= pulseDelayPeriod_) 
    {   
        // save the last time you blinked the LED
        previousMillis_ = currentMillis;
        #ifdef DEBUG_PRINTS
            Serial.println("[INFO] period passed !");
        #endif
        return true ;
    }
    else 
    {
      #ifdef DEBUG_PRINTS
        Serial.println("[INFO] timer is ", (currentMillis-previousMillis_));
      #endif
  
      return false;
    }
}

void Controller::changeDuty(const unsigned int &period ) 
{
    pulseDelayPeriod_ = period; 
    finishProcess_ = getTimer();

    switch (state_)
    {
    case Controller::PULState::eReady :
    {    
        digitalWrite(DRIVER_PUL_PIN, HIGH);
        state_ = Controller::PULState::eHIGH;
        break;
    } 
    case Controller::PULState::eHIGH :
    {
        if (finishProcess_)
        {
            digitalWrite(DRIVER_PUL_PIN, LOW);
            state_ = Controller::PULState::eLOW; 
        }
        break;

    }
    case Controller::PULState::eLOW :
    {
        if (finishProcess_)
        {
            digitalWrite(DRIVER_PUL_PIN, HIGH);
            state_ = Controller::PULState::eHIGH; 
        }
        break;
    }
    default:
    {
        #ifdef DEBUG_PRINTS
            Serial.println("[WARN] default Sate called");
        #endif
        break;
    
    }
    }

    #ifdef DEBUG_PRINTS
        Serial.println("StatePul is ", state_);
    #endif
    
}
