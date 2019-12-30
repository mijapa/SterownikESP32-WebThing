#include "servo.h"
#include <ESP32Servo.h>
#include <Ticker.h>

#define SERVO_PIN 25

Servo myservo;
Ticker detachTicker;
int oldPos = SERVO_ZAMKN_MAX;

void servoDetach() {
    myservo.detach();
}

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
    if (pos >= 0 && pos <= 100) {
        if (pos != oldPos) { //sprawdzanie czy zadana pozycja dla serva się zmieniła
            detachTicker.detach();
            myservo.attach(SERVO_PIN);
            delay(10);
            myservo.write(pos);
            if (pos - oldPos < 5 && pos - oldPos > -5) {
                detachTicker.once_ms(200, servoDetach);
            } else {
                detachTicker.once_ms(2000, servoDetach);
            }
            oldPos = pos;//zmiana starej pozycji na nową
        }
    } else {
        Serial.println("Wrong servo pos parameter");
    }
}

