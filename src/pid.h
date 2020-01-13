#ifndef STEROWNIKESP32_WEBTHING_PID_H
#define STEROWNIKESP32_WEBTHING_PID_H

#define RoomTempSetpoint_START 20 //wstępnie zadana temperatura (DHT)
#define TEMP_ZAD_MAX 360 //zdefinioweanie zakresu temperatur termopara w kominie
#define TEMP_ZAD_MIN 240
#define SMALL_DIFF 10
#endif //STEROWNIKESP32_WEBTHING_PID_H

void setupPIDs();

void loopPID();

void printAllPid();