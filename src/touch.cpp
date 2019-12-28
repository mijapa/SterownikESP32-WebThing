#include <HardwareSerial.h>
#include <Ticker.h>
#include "touch.h"

#define  TOUCH_PIN1 13
#define  TOUCH_PIN2 12
#define  TOUCH_PIN3 14
#define  TOUCH_PIN4 27
#define  TOUCH_PIN5 15
#define TOUCH_THRESHOLD_DIFF 10

Ticker interruptTicker;

uint8_t touch_pin1_threshold = 0;
uint8_t touch_pin2_threshold = 0;
uint8_t touch_pin3_threshold = 0;
uint8_t touch_pin4_threshold = 0;
uint8_t touch_pin5_threshold = 0;

void set_threshold() {
    delay(5000);
    touch_pin1_threshold = touchRead(TOUCH_PIN1) - TOUCH_THRESHOLD_DIFF;
    touch_pin2_threshold = touchRead(TOUCH_PIN2) - TOUCH_THRESHOLD_DIFF;
    touch_pin3_threshold = touchRead(TOUCH_PIN3) - TOUCH_THRESHOLD_DIFF;
    touch_pin4_threshold = touchRead(TOUCH_PIN4) - TOUCH_THRESHOLD_DIFF;
    touch_pin5_threshold = touchRead(TOUCH_PIN5) - TOUCH_THRESHOLD_DIFF;
    Serial.print("Set thresholds: ");
    Serial.print(touch_pin1_threshold + ", ");
    Serial.print(touch_pin2_threshold + ", ");
    Serial.print(touch_pin3_threshold + ", ");
    Serial.print(touch_pin4_threshold + ", ");
    Serial.print(touch_pin5_threshold + ", ");
    Serial.println("");
}

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

void enable_touch_interrupt() {
    Serial.println("Enable touch interrupt");
    interruptTicker.detach();
    touch_pad_intr_enable();
}

void gotTouch() {//callback should be very short
    touch_pad_intr_disable();
    interruptTicker.attach_ms(5000, enable_touch_interrupt);
}

void setupTouch() {
    set_threshold();
//    touchAttachInterrupt(TOUCH_PIN1, gotTouch, touch_pin1_threshold);
//    touchAttachInterrupt(TOUCH_PIN2, gotTouch, touch_pin2_threshold);
//    touchAttachInterrupt(TOUCH_PIN3, gotTouch, touch_pin3_threshold);
//    touchAttachInterrupt(TOUCH_PIN4, gotTouch, touch_pin4_threshold);
//    touchAttachInterrupt(TOUCH_PIN5, gotTouch, touch_pin5_threshold);
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