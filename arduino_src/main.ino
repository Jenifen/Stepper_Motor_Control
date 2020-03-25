#include "board.h"

Controller* control;

void setup()
{
    Serial.begin(9600);
    control->begin();
    control->init();
    
}
void loop()
{

}
