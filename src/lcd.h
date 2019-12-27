#ifndef STEROWNIKESP32_WEBTHING_LCD_H
#define STEROWNIKESP32_WEBTHING_LCD_H

#endif //STEROWNIKESP32_WEBTHING_LCD_H

void setupLCD();

void loopLCD();

void displayTemp(double temp);

void displayBasic(double Setpoint, double Setpoint2, double hic, double thermocouple, int servoPercentage);