#include "servo.h"
#include <ESP32Servo.h>
#include <Ticker.h>

#define SERVO_PIN 25


Servo myservo;
Ticker servoTickeer;
int oldPos = SERVO_ZAMKN_MAX;

void set_servo_at_begining() {
    myservo.attach(SERVO_PIN);  // attaches the servo on pin 5 to the servo object

    for (oldPos = SERVO_ZAMKN_MAX; oldPos >= SERVO_ZAMKN_MIN; oldPos -= 1) {
        // in steps of 1 degree
        myservo.write(oldPos);              // tell servo to go to position in variable 'pos'
        delay(10);                       // waits 15ms for the servo to reach the position
    }
    myservo.detach();
}

void set_servo_new_pos(int pos) {
    if (pos != oldPos) { //sprawdzanie czy zadana pozycja dla serva się zmieniła
        myservo.attach(SERVO_PIN);
        delay(10);
        myservo.write(pos);
        if (pos - oldPos < 5 && pos - oldPos > -5) {
            delay(200);
        } else {
            delay(2000);
        }
        myservo.detach();

        oldPos = pos;//zmiana starej pozycji na nową
    }
}

int i = 0;

void servoRoutine() {
//    Serial.println("Servo routine");
    myservo.write(i);
    i++;
    i = i % 2500;
    if (i < 500) i = 500;
}

void setupServo() {
    myservo.attach(SERVO_PIN);
    servoTickeer.attach_ms(100, servoRoutine);
}

