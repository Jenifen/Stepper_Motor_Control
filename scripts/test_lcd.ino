#include "../arduino_src/LiquidCrystal_I2C.h"


LiquidCrystal_I2C lcd(0x27, 16, 2);

int i = 125;
void setup()
{
    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("per_cycle " + (String) i);
}
void loop()
{}