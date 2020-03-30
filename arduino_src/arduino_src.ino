#include "board.h"
#include "LiquidCrystal_I2C.h"

Board::Controller control;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup()
{
    Serial.begin(DEBUG_BAUDRATE);
    control.begin();
    //control.Stop();
    lcd.begin();
    lcd.backlight();
    
    #ifdef START_DIRECTION_CLOCKWISE
      #ifndef START_DIRECTION_ANTICLOCKWISE
      control.setDirection(control.eClockWise);
      #endif
    #endif
    
    #ifdef START_DIRECTION_ANTICLOCKWISE
      #ifndef START_DIRECTION_CLOCKWISE
      control.setDirection(control.eAntiClockWise);
      #endif
    #endif
    
    #ifdef TEST_STEP
        control.TEST();
    #endif 
}
void loop()
{
   
    /// FREQ : nbr rotation = m/s
    unsigned long periodCycle =  map(analogRead(POT_FREQ_PIN), MIN_ANALOG_READ, 
        MAX_ANALOG_READ, MIN_PERIOD_CYCLE, MAX_PERIOD_CYCLE);
    
    control.changePeriodCycle(periodCycle);
    
    unsigned long period =  map( analogRead(POT_SPEED_PIN), MIN_ANALOG_READ, 
        MAX_ANALOG_READ, MAX_PERIOD_PULSE, MIN_PERIOD_PULSE);
    
    
    control.changeDutyCycle(period); // no block 
    
    
    /*
    #ifdef DEBUG_PRINTS
        Serial.println("[INFO] Tick");
    #endif
    */
}
