#include <HardwareSerial.h>
#include <Ticker.h>
#include "touch.h"
#include "webthings.h"
#include "lcd.h"

Ticker updateTouchTicker;

uint8_t touch_pin1_threshold = 0;
uint8_t touch_pin2_threshold = 0;
uint8_t touch_pin3_threshold = 0;
uint8_t touch_pin4_threshold = 0;
uint8_t touch_pin5_threshold = 0;

bool timeToUpdateTouch = false;

void setThreshold() {
    touch_pin1_threshold = touchRead(TOUCH_PIN1) - TOUCH_THRESHOLD_DIFF;
    touch_pin2_threshold = touchRead(TOUCH_PIN2) - TOUCH_THRESHOLD_DIFF;
    touch_pin3_threshold = touchRead(TOUCH_PIN3) - TOUCH_THRESHOLD_DIFF;
    touch_pin4_threshold = touchRead(TOUCH_PIN4) - TOUCH_THRESHOLD_DIFF;
    touch_pin5_threshold = touchRead(TOUCH_PIN5) - TOUCH_THRESHOLD_DIFF;
    Serial.print("Set thresholds: ");
    Serial.print(touch_pin1_threshold);
    Serial.print(", ");
    Serial.print(touch_pin2_threshold);
    Serial.print(", ");
    Serial.print(touch_pin3_threshold);
    Serial.print(", ");
    Serial.print(touch_pin4_threshold);
    Serial.print(", ");
    Serial.print(touch_pin5_threshold);
    Serial.println("");
}

void printAllTouchValues() {
    Serial.print("Touch thresholds: ");
    Serial.print(touch_pin1_threshold);
    Serial.print(", ");
    Serial.print(touch_pin2_threshold);
    Serial.print(", ");
    Serial.print(touch_pin3_threshold);
    Serial.print(", ");
    Serial.print(touch_pin4_threshold);
    Serial.print(", ");
    Serial.println(touch_pin5_threshold);
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

void updateTouch(){
    bool up = isTouched(touchRead(TOUCH_PIN1), touch_pin1_threshold);
    bool down = isTouched(touchRead(TOUCH_PIN5), touch_pin5_threshold);
    bool left = isTouched(touchRead(TOUCH_PIN4), touch_pin4_threshold);
    bool right = isTouched(touchRead(TOUCH_PIN3), touch_pin3_threshold);
    bool middle = isTouched(touchRead(TOUCH_PIN2), touch_pin2_threshold);
    updateTouchWebThing(up, down, left, right, middle);
    if(up || down || left|| right||middle){
        setLcdOnThanOff();
    }
}

void touchReady(){
    timeToUpdateTouch = true;
}

void setupTouch() {
    setThreshold();
    setThreshold();
    updateTouchTicker.attach_ms(500, touchReady);
}

void loopTouch(){
    if(timeToUpdateTouch){
        timeToUpdateTouch = false;
        updateTouch();
    }
}

void printAllTouchReadings() {
    Serial.print("Touch sensors: ");
    Serial.print(isTouched(touchRead(TOUCH_PIN1), touch_pin1_threshold));
    Serial.print(", ");
    Serial.print(isTouched(touchRead(TOUCH_PIN2), touch_pin2_threshold));
    Serial.print(", ");
    Serial.print(isTouched(touchRead(TOUCH_PIN3), touch_pin3_threshold));
    Serial.print(", ");
    Serial.print(isTouched(touchRead(TOUCH_PIN4), touch_pin4_threshold));
    Serial.print(", ");
    Serial.println(isTouched(touchRead(TOUCH_PIN5), touch_pin5_threshold));
}

void printAllTouch() {
    printAllTouchValues();
    printAllTouchReadings();
}