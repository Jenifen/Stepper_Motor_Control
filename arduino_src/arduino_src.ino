#include "board.h"

Board::Controller* control;


void setup()
{
    if (control == nullptr) while(1)
    Serial.begin(DEBUG_BAUDRATE);
    control->begin();
    control->Stop();
    

    control->setDirection(control->eClockWise);
    #ifdef TEST_STEP
        control->TEST();
    #endif 
}
void loop()
{

    
    unsigned long period = map(analogRead(POT_SPEED_PIN), MIN_ANALOG_READ, 
        MAX_ANALOG_READ, MAX_PERIOD_STEP, MIN_PERIOD_STEP);
    
    control->changeDuty(period); // no block 
    
    /// FREQ : nbr rotation = 
    
    
    #ifdef DEBUG_PRINTS
        Serial.println("[INFO] Tick")
    #endif
}
