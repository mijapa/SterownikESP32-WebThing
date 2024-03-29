#include "loopAnalogRead.h"
#include "webthings.h"
#include <HardwareSerial.h>
#include <Ticker.h>

Ticker updatePoweringTicker;

bool external = false;
bool full = false;
bool updateAnalogReads = false;

void setupAnalogReads(){
    pinMode(MEASURE_PIN1, INPUT);
    pinMode(MEASURE_PIN2, INPUT_PULLUP);
    pinMode(MEASURE_PIN3, INPUT);
}

void printAnalogReads() {
    Serial.print("Analog read: ");
    Serial.print(analogRead(MEASURE_PIN1));
    Serial.print(" ");
    Serial.print(analogRead(MEASURE_PIN2));
    Serial.print(" ");
    Serial.println(analogRead(MEASURE_PIN3));
}

void updatePowreing(){
    int pin1 = analogRead(MEASURE_PIN1);
    if (pin1 > EXTERNAL_POWER_THRESHOLD){
        external = true;
    } else {
        external = false;
    }
    int pin3 = analogRead(MEASURE_PIN3);
    if (pin3 > BATTERY_FULL_THRESHOLD){
        full = true;
    } else {
        full = false;
    }
    updatePowerWebThing(external, full);
}

void analogReady(){
    updateAnalogReads = true;
}

void loopAnalogReads(){
    if(updateAnalogReads){
        updateAnalogReads = false;
        updatePowreing();
    }
}

void poweringSetup(){
    updatePoweringTicker.attach_ms(500, analogReady);
}