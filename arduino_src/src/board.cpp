
#include "../include/board.h"


// Constructor
Board::Controller::Controller() {
  // Empty constructor
}

void Board::Controller::begin() const 
{
    pinMode(DRIVER_DIR_PIN, OUTPUT);
    pinMode(DRIVER_PUL_PIN, OUTPUT);

    
    delay(STARTUP_DELAY);
    #ifdef DEBUG_PRINTS
        Serial.println("\n [respirator Starting]\n");
    #endif

}

void Board::Controller::setDirection(const Direction& dir) 
{
    digitalWrite(DRIVER_DIR_PIN, dir);
    delayMicroseconds(2);
    progress_direction_ = dir;
    #ifdef DEBUG_PRINTS
        Serial.println("\n Direction Changed \n");
    #endif
}


bool Board::Controller::getTimer()
{ 
    static unsigned long previousMicros_ = 0;     // will store last time 
    unsigned long currentMicros = micros();

    if (abs(currentMicros - previousMicros_) >= pulseDelayPeriod_) 
    {   
        // save the last time you blinked the LED
        previousMicros_ = currentMicros;
        #ifdef DEBUG_PRINTS
            Serial.println("[INFO] period passed !");
        #endif
        return true ;
    }
    else 
    {
      #ifdef DEBUG_PRINTS
   //      Serial.println("[INFO] timer is ", (String)h );
      #endif
  
      return false;
    }
}

void Board::Controller::changeDutyCycle(const unsigned long& period_cycle ) 
{   
    pulseDelayPeriod_ = period_cycle; 
    finish_period_process_ = getTimer();
    switch (state_)
    {
    case Board::Controller::PulseState::eReady :
    {   
        digitalWrite(DRIVER_PUL_PIN, HIGH);
        state_ = Board::Controller::PulseState::eHIGH;
        break;
    } 
    case Board::Controller::PulseState::eHIGH :
    {    
        if (finish_period_process_)
        {   
            digitalWrite(DRIVER_PUL_PIN, LOW);
            state_ = Board::Controller::PulseState::eLOW;
             
        }
        break;

    }
    case Board::Controller::PulseState::eLOW :
    {    
        if (finish_period_process_)
        {
            digitalWrite(DRIVER_PUL_PIN, HIGH);
            state_ = Board::Controller::PulseState::eHIGH;
            
        }
        break;
    }
    default:
    {   
        state_ = Board::Controller::PulseState::eError;
        #ifdef DEBUG_PRINTS
            Serial.println("[WARN] default Sate called");
        #endif
        break;
    
    }
    }

    #ifdef DEBUG_PRINTS
        //Serial.println("StatePul is ", state_);
    #endif
    
}

void Board::Controller::changePeriodCycle(const unsigned long& period_pulse)
{
    cyclePeriod_ = period_pulse ;
    static unsigned long previousMillis_ = 0;     // will store last time 
    unsigned long currentMillis = millis();
    
    if (abs(currentMillis - previousMillis_) >= cyclePeriod_) 
    {
        previousMillis_ = currentMillis;
        if (progress_direction_ == Board::Controller::Direction::eClockWise)
            Board::Controller::setDirection(Board::Controller::Direction::eAntiClockWise);
        else if (progress_direction_ == Board::Controller::Direction::eAntiClockWise)
            Board::Controller::setDirection(Board::Controller::Direction::eClockWise);
    }

}

void Board::Controller::TEST() const 
{
    while (1)
    { 
      #ifdef TEST_DIRECTION_CLOCKWISE
        #ifndef TEST_DIRECTION_ANTICLOCKWISE
        Board::Controller::setDirection(Board::Controller::Direction::eClockWise);
        digitalWrite(DRIVER_PUL_PIN, HIGH);
        delayMicroseconds(50);
        digitalWrite(DRIVER_PUL_PIN, LOW);
        delayMicroseconds(50);
        #endif
      #endif

      #ifdef TEST_DIRECTION_ANTICLOCKWISE
        #ifndef TEST_DIRECTION_CLOCKWISE
            Board::Controller::setDirection(Board::Controller::Direction::eAntiClockWise);
            digitalWrite(DRIVER_PUL_PIN, HIGH);
            delayMicroseconds(50);
            digitalWrite(DRIVER_PUL_PIN, LOW);
            delayMicroseconds(50);
        #endif  
      #endif
      
        #ifdef DEBUG_PRINTS
            Serial.println("\n*** TickTEST ***\n");
        #endif
        
    }
}
