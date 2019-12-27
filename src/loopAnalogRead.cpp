#include "loopAnalogRead.h"
#include <HardwareSerial.h>

#define MEASURE_PIN1 35 //UPS1
#define MEASURE_PIN2 34 //UPS2
#define MEASURE_PIN3 32 //Fireplace

void loopAnalogRead() {
    Serial.print("Analog read: ");
    Serial.print(analogRead(MEASURE_PIN1));
    Serial.print(" ");
    Serial.print(analogRead(MEASURE_PIN2));
    Serial.print(" ");
    Serial.println(analogRead(MEASURE_PIN3));
}

int analogRead2() {
    return (analogRead(MEASURE_PIN3));
}