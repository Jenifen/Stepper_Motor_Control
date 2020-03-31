
#include "board.h"
#include "LiquidCrystal_I2C.h"

Board::Controller control;

#ifdef DISPLAY_LCD
  LiquidCrystal_I2C lcd(0x27, 16, 2); 
 
#endif

bool interrupt = false;

void setup()
{
    Serial.begin(DEBUG_BAUDRATE);
    control.begin();
    pinMode(READY_PIN, INPUT_PULLUP);
    pinMode(STOP_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(STOP_PIN), Stop, FALLING);
    Stop();
   
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

void Stop()
{
  interrupt = true;
}

void loop()
{

  /// FREQ : nbr rotation = m/s
          unsigned long period_cycle =  map(analogRead(POT_FREQ_PIN), MIN_ANALOG_READ, 
              MAX_ANALOG_READ, MIN_PERIOD_CYCLE, MAX_PERIOD_CYCLE);
    
          unsigned long pulse_cycle =  map( analogRead(POT_SPEED_PIN), MIN_ANALOG_READ, 
              MAX_ANALOG_READ, MAX_PERIOD_PULSE, MIN_PERIOD_PULSE);
          
    if (interrupt)
    { 
      while ( digitalRead(READY_PIN)) 
      {
        #ifdef DISPLAY_LCD
          /// FREQ : nbr rotation = m/s
          period_cycle =  map(analogRead(POT_FREQ_PIN), MIN_ANALOG_READ, 
              MAX_ANALOG_READ, MIN_PERIOD_CYCLE, MAX_PERIOD_CYCLE);
    
          pulse_cycle =  map( analogRead(POT_SPEED_PIN), MIN_ANALOG_READ, 
              MAX_ANALOG_READ, MAX_PERIOD_PULSE, MIN_PERIOD_PULSE);
          static unsigned long last_period_cycle = 0;
          static unsigned long last_pulse_cycle = 0;
          
          if ( abs(pulse_cycle - last_pulse_cycle) >= 2 ||  (period_cycle - last_period_cycle) >= 2 )
          {
            
            last_period_cycle = period_cycle;
            last_pulse_cycle = pulse_cycle ;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("pulse : " + (String)  pulse_cycle);
            lcd.setCursor(0, 1);
            lcd.print("period : " + (String) period_cycle);
          }
          delay(200); 
        #endif
      }
      
      interrupt = false;

      }
    
    control.changePeriodCycle(period_cycle);
    
    control.changeDutyCycle(pulse_cycle); // no block 
    #ifdef DEBUG_PRINTS
        Serial.println("[INFO] Tick");
    #endif
    
}
