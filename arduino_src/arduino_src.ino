#include "board.h"

Board::Controller* control;


void setup()
{
    Serial.begin(DEBUG_BAUDRATE);
    control->begin();
    //control->Stop();
    
    #ifdef START_DIRECTION_CLOCKWISE
      #ifndef START_DIRECTION_ANTICLOCKWISE
      control->setDirection(control->eClockWise);
      #endif
    #endif
    
    #ifdef START_DIRECTION_ANTICLOCKWISE
      #ifndef START_DIRECTION_CLOCKWISE
      control->setDirection(control->eAntiClockWise);
      #endif
    #endif
    
    #ifdef TEST_STEP
        control->TEST();
    #endif 
}
void loop()
{

    
    //unsigned long period =  map(analogRead(POT_SPEED_PIN), MIN_ANALOG_READ, 
      //  MAX_ANALOG_READ, MAX_PERIOD_STEP, MIN_PERIOD_STEP);
    
    control->changeDuty(50); // no block 
    
    /// FREQ : nbr rotation = 
    
    
    #ifdef DEBUG_PRINTS
        Serial.println("[INFO] Tick");
    #endif
    
}
