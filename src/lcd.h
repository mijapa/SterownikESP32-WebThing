#ifndef STEROWNIKESP32_WEBTHING_LCD_H
#define STEROWNIKESP32_WEBTHING_LCD_H

#define DIM_LAG 5
#define LCD_COLS 16
#define LCD_ROWS 2
#define LCD_I2C_ADD 0x27
#endif //STEROWNIKESP32_WEBTHING_LCD_H

void setupLCD();

void setLcdOnThanOff();

void displayBasic(double Setpoint, double Setpoint2, double hic, double thermocouple, int servoPercentage);