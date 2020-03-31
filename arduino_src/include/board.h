#ifndef BOARD_H
#define BOARD_H
#include "Arduino.h"

#define STARTUP_DELAY 2000

//#define DEBUG_PRINTS //would disable comments when you need debug with serial monitor
#define DEBUG_BAUDRATE 9600

#define POT_SPEED_PIN A0 // used for speed variation
#define POT_FREQ_PIN A1 

#define DRIVER_PUL_PIN 7
#define DRIVER_DIR_PIN 6

#define READY_PIN 5
#define STOP_PIN 2

// analog input arduino [0->1023]
#define MIN_ANALOG_READ 0
#define MAX_ANALOG_READ 1023

// max period for stepper 
#define MIN_PERIOD_PULSE 10
#define MAX_PERIOD_PULSE 2000

// Cycle in m/s  
#define MIN_PERIOD_CYCLE 1000
#define MAX_PERIOD_CYCLE 20000



// for testing 
//#define TEST_STEP
//#define TEST_DIRECTION_CLOCKWISE 
#define TEST_DIRECTION_ANTICLOCKWISE

//direction start
#define START_DIRECTION_CLOCKWISE
//#define START_DIRECTION_ANTICLOCKWISE

#define DISPLAY_LCD

namespace Board 
{


class Controller
{

public:

    enum Direction
    {
        eAntiClockWise = 0,
        eClockWise = 1
    };

    enum PulseState
    {   
        eReady = 0,
        eLOW = 1,
        eHIGH = 2,
        eError = 3
    };


    Controller(void);
    void begin() const ;
    /*
     *
     * 
     */ 
    void setDirection(const Direction &dir)  ;
    
    /* 
     * @brief change duty 
     * @param periodPulse : value [., . ]
     * 
     */ 
    
    void changeDutyCycle(const unsigned long& period_pulse);
    /*
     * @brief this is for changing period cycle 
     * @param period : period in [m/s]
     */
    void changePeriodCycle(const unsigned long& period_cycle) ; 
    
    
    void TEST() const ;
    
    inline unsigned long getPulsePeriod(){return pulseDelayPeriod_;}
    inline unsigned long getCyclePeriod(){return cyclePeriod_;}
    

private:
  
    bool getTimer();
    
    unsigned long pulseDelayPeriod_ = 50; 
    unsigned long cyclePeriod_ = 500; 
    bool finish_period_process_ = false;

    Board::Controller::PulseState state_ = Board::Controller::PulseState::eReady ;
    Board::Controller::Direction progress_direction_; 
};




}

#endif 
