#ifndef BOARD_H
#define BOARD_H

#define STARTUP_DELAY 2000

//#define DEBUG_PRINTS //would disable comments when you need debug with serial monitor
#define DEBUG_BAUDRATE 9600

#define POT_SPEED_PIN A0 // used for speed variation
#define POT_FREQ_PIN A1 

#define DRIVER_PUL_PIN 7
#define DRIVER_DIR_PIN 6


class Controller
{
public:

    enum Direction
    {
        eAntiClockWise = 0,
        eClockWise = 1
    };

    Controller(void);
    void begin();
    void init();
    void changeDirection(Direction &dir);

};




#endif 
