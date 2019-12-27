#include <HardwareSerial.h>
#include "touch.h"

#define  TOUCH_PIN1 13
#define  TOUCH_PIN2 12
#define  TOUCH_PIN3 14
#define  TOUCH_PIN4 27
#define  TOUCH_PIN5 15

void printAllTouchValues() {
    Serial.print("Touch sensors: ");
    Serial.print(touchRead(TOUCH_PIN1));
    Serial.print(", ");
    Serial.print(touchRead(TOUCH_PIN2));
    Serial.print(", ");
    Serial.print(touchRead(TOUCH_PIN3));
    Serial.print(", ");
    Serial.print(touchRead(TOUCH_PIN4));
    Serial.print(", ");
    Serial.println(touchRead(TOUCH_PIN5));
}

int isTouched(int touchValue, int treshold) {
    if (touchValue < treshold) {
        return true;
    } else {
        return false;
    }
}

void printAllTouchReadings() {
    Serial.print("Touch sensors: ");
    Serial.print(isTouched(touchRead(TOUCH_PIN1), 56));
    Serial.print(", ");
    Serial.print(isTouched(touchRead(TOUCH_PIN2), 55));
    Serial.print(", ");
    Serial.print(isTouched(touchRead(TOUCH_PIN3), 54));
    Serial.print(", ");
    Serial.print(isTouched(touchRead(TOUCH_PIN4), 55));
    Serial.print(", ");
    Serial.println(isTouched(touchRead(TOUCH_PIN5), 51));

}

void printAllTouch() {
    printAllTouchValues();
    printAllTouchReadings();
}