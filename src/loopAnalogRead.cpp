#include "loopAnalogRead.h"
#include <HardwareSerial.h>

#define MEASURE_PIN1 35
#define MEASURE_PIN2 34

void loopAnalogRead() {
    Serial.print("Analog read: ");
    Serial.print(analogRead(MEASURE_PIN1));
    Serial.print(" ");
    Serial.println(analogRead(MEASURE_PIN2));
}

int analogRead2() {
    return (analogRead(MEASURE_PIN2));
}