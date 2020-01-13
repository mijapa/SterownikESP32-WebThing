#ifndef STEROWNIKESP32_WEBTHING_ANALOGREAD_H
#define STEROWNIKESP32_WEBTHING_ANALOGREAD_H

#define MEASURE_PIN1 35 //UPS1
#define MEASURE_PIN2 34 //UPS2
#define MEASURE_PIN3 32 //Fireplace
#define EXTERNAL_POWER_THRESHOLD 400
#define BATTERY_FULL_THRESHOLD 1300
#endif //STEROWNIKESP32_WEBTHING_ANALOGREAD_H

void printAnalogReads();

void setupAnalogReads();

void loopAnalogReads();

void poweringSetup();