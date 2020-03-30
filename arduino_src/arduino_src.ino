
#include "board.h"
#include "LiquidCrystal_I2C.h"

Board::Controller control;

#ifdef DISPLAY_LCD
  LiquidCrystal_I2C lcd(0x27, 16, 2); 
#endif

bool last_interrupt_value = false;


void setup()
{
    Serial.begin(DEBUG_BAUDRATE);
    control.begin();
    //control.Stop();
    
    
    #ifdef DISPLAY_LCD
      lcd.begin();
      lcd.backlight();
      lcd.clear();
    #endif   
     
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
    unsigned long period_cycle =  map(analogRead(POT_FREQ_PIN), MIN_ANALOG_READ, 
        MAX_ANALOG_READ, MIN_PERIOD_CYCLE, MAX_PERIOD_CYCLE);
    
    control.changePeriodCycle(period_cycle);
    
    unsigned long pulse_cycle =  map( analogRead(POT_SPEED_PIN), MIN_ANALOG_READ, 
        MAX_ANALOG_READ, MAX_PERIOD_PULSE, MIN_PERIOD_PULSE);
    
    
    control.changeDutyCycle(pulse_cycle); // no block 
    
    bool current_interrupt_value = control.get_interrupt_state ();
    if (last_interrupt_value != current_interrupt_value)
    {
      last_interrupt_value = current_interrupt_value;
      
      while (control.get_ready_state()) 
      {
        #ifdef DISPLAY_LCD
          lcd.setCursor(0, 0);
          lcd.print("pulse : " + (String) pulse_cycle);
          lcd.setCursor(0, 1);
          lcd.print("period : " + (String) period_cycle);
          
        #endif
      } 
    }
    
    #ifdef DEBUG_PRINTS
        Serial.println("[INFO] Tick");
    #endif
    
}
