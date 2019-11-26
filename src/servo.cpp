#include "servo.h"
#include <ESP32Servo.h>
#include <Ticker.h>

#define SERVO_PIN 4

Servo myservo;
Ticker servoTickeer;

int i = 0;

void servoRoutine() {
    myservo.write(i);
    i++;
    i = i % 2500;
    if (i < 500) i = 500;
}

void setupServo() {
    myservo.attach(SERVO_PIN);
    servoTickeer.attach_ms(100, servoRoutine);
}

