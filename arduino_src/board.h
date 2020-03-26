#ifndef BOARD_H
#define BOARD_H

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
#define MIN_PERIOD_STEP 20
#define MAX_PERIOD_STEP 2000

class Controller
{
public:

    enum Direction
    {
        eAntiClockWise = 0,
        eClockWise = 1
    };

    enum PULState
    {   
        eReady = 0,
        eLOW = 1,
        eHIGH = 2
    };

    Controller(void);
    void begin();
    /*
     *
     * 
     */ 
    void setDirection(const Direction &dir) ;
    
    /* 
     * @brief change duty 
     * @param pwm : value [., . ]
     * 
     */ 
    
    void changeDuty(const unsigned int &period);
    
    void stop() const ;
    
private:

    bool getTimer();

    
    unsigned int pulseDelayPeriod_ = 500; //value pot 

    unsigned long previousMillis_ = 0;     // will store last time 
    
    bool finishProcess_ = false;

    PULState state_ = PULState::eReady ;
};




#endif 
