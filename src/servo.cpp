#include "servo.h"
#include <ESP32Servo.h>
#include <Ticker.h>

Servo myservo;
Ticker detachTicker;
Ticker waitToAttach;
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

void write_pos(int pos) {
    Serial.print("Writing new servo pos: ");
    Serial.println(pos);
    ledcAttachPin(SERVO_PIN, 5);
    myservo.write(pos);
    if (abs(pos - oldPos) < SMALL_POS_DIFF) {
        detachTicker.once_ms(200, servoDetach);
    } else {
        detachTicker.once_ms(2000, servoDetach);
    }
    oldPos = pos;//zmiana starej pozycji na nową
}

void setServoNewPos(int pos) {
    if (pos != oldPos) { //sprawdzanie czy zadana pozycja dla serva się zmieniła
        detachTicker.detach();
        myservo.attach(SERVO_PIN);
        waitToAttach.once_ms(5, write_pos, pos);
    }
}

