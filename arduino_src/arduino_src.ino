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
    int last = micros();
    lcd.print("Hello, world!");
    int t = micros();
    Serial.println(t-last);
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

    control.changePeriodCycle(5000);

    unsigned long period =  map(analogRead(POT_SPEED_PIN), MIN_ANALOG_READ, 
        MAX_ANALOG_READ, MAX_PERIOD_STEP, MIN_PERIOD_STEP);
    
    
    control.changeDutyCycle(period); // no block 
    
    
    
    #ifdef DEBUG_PRINTS
        Serial.println("[INFO] Tick");
    #endif
    
}
