#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <Ticker.h>
#include "lcd.h"

LiquidCrystal_PCF8574 lcd(LCD_I2C_ADD); // set the LCD address to 0x27 for a 16 chars and 2 line display

Ticker dimTicker;
bool isLcdOff = true;

void turnOffLcd(){
    lcd.setBacklight(0);
    isLcdOff = true;
}

void setLcdOnThanOff(){
    dimTicker.detach();
    if(isLcdOff){
        lcd.setBacklight(255);
        isLcdOff = false;
    }
    dimTicker.once(DIM_LAG, turnOffLcd);
}

void setupLCD() {
    int error;

    Serial.println("LCD...");
    Serial.println("Dose: check for LCD");

    // See http://playground.arduino.cc/Main/I2cScanner how to test for a I2C device.
    Wire.begin();
    Wire.beginTransmission(LCD_I2C_ADD);
    error = Wire.endTransmission();
    Serial.print("Error: ");
    Serial.print(error);

    if (error == 0) {
        Serial.println(": LCD found.");
        lcd.begin(LCD_COLS, LCD_ROWS); // initialize the lcd

    } else {
        Serial.println(": LCD not found.");
    } // if
    lcd.clear();
    turnOffLcd();
    isLcdOff = true;
}

void displayBasic(double Setpoint, double Setpoint2, double hic, double thermocouple, int servoPercentage) {
    lcd.setCursor(0,
                  1);// set the cursor to column 0, line 1 (note: line 1 is the second row, since counting begins with 0)
    lcd.print(Setpoint2);//temperatura zadana DHT
    lcd.print(" ");
    lcd.print(hic); //temperatura odczuwalna DHT22
    lcd.print(" ");
    lcd.print(servoPercentage);//procent otwarcia przepustnicy obliczony na podstawie ServoOutput z PID
    lcd.print("   ");
    lcd.setCursor(7, 0);
    lcd.print(" ");
    lcd.print(thermocouple);//temperatura termopara
    lcd.setCursor(0, 0);
    lcd.print(Setpoint);//ThermoSetpoint z PID
    lcd.print(" ");
}