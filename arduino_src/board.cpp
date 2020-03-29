
#include "board.h"


// Constructor
Board::Controller::Controller() {
  // Empty constructor
}

void Board::Controller::begin()
{
    pinMode(DRIVER_DIR_PIN, OUTPUT);
    pinMode(DRIVER_PUL_PIN, OUTPUT);
    pinMode(READY_PIN, INPUT_PULLUP);
    pinMode(STOP_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(STOP_PIN), Board::Controller::Stop, FALLING);
    
    delay(STARTUP_DELAY);
    #ifdef DEBUG_PRINTS
        Serial.println("\n [respirator Starting]\n");
    #endif

}

static void Board::Controller::Stop() 
{
    digitalWrite(DRIVER_PUL_PIN, LOW);
    digitalWrite(DRIVER_DIR_PIN, LOW);
    while(digitalRead(READY_PIN));
}


void Board::Controller::setDirection(const Direction &dir)
{
    digitalWrite(DRIVER_DIR_PIN, dir);
    #ifdef DEBUG_PRINTS
        Serial.println("\n Direction Changed \n");
    #endif
}


bool Board::Controller::getTimer()
{
    unsigned long currentMillis = micros();
    
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
      float h=currentMillis-previousMillis_;
   //      Serial.println("[INFO] timer is ", (String)h );
      #endif
  
      return false;
    }
}

void Board::Controller::changeDuty(const unsigned int &period ) 
{   
    //Serial.print("change duty called : ");
    //Serial.println(state_);
    pulseDelayPeriod_ = period; 
    finishProcess_ = getTimer();
    switch (state_)
    {
    case Board::Controller::PULState::eReady :
    {   
        Serial.println("ready");
        digitalWrite(DRIVER_PUL_PIN, HIGH);
        state_ = Board::Controller::PULState::eHIGH;
        break;
    } 
    case Board::Controller::PULState::eHIGH :
    {     
        Serial.println("eHIGH");
        if (finishProcess_)
        {   
            digitalWrite(DRIVER_PUL_PIN, LOW);
            state_ = Board::Controller::PULState::eLOW;
             
        }
        break;

    }
    case Board::Controller::PULState::eLOW :
    {   
        Serial.println("eLOW"); 
        if (finishProcess_)
        {
            digitalWrite(DRIVER_PUL_PIN, HIGH);
            state_ = Board::Controller::PULState::eHIGH;
            
        }
        break;
    }
    default:
    {   Serial.println("default");
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
