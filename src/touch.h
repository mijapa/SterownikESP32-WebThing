#ifndef STEROWNIKESP32_WEBTHING_TOUCH_H
#define STEROWNIKESP32_WEBTHING_TOUCH_H

#define  TOUCH_PIN1 13
#define  TOUCH_PIN2 12
#define  TOUCH_PIN3 14
#define  TOUCH_PIN4 27
#define  TOUCH_PIN5 15
#define TOUCH_THRESHOLD_DIFF 3
#endif //STEROWNIKESP32_WEBTHING_TOUCH_H

void printAllTouch();

void setupTouch();

void loopTouch();