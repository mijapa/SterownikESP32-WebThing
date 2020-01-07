#ifndef STEROWNIKESP32_WEBTHING_SERVO_H
#define STEROWNIKESP32_WEBTHING_SERVO_H

#define SERVO_PIN 25
#define SMALL_POS_DIFF 5
#define SERVO_ZAMKN_MAX 170 //zdefinowanie parametrów dla serwa przy piecu kominkowym, większy parametr serva większe zamknięcie
#define SERVO_ZAMKN_MIN  30
#endif //STEROWNIKESP32_WEBTHING_SERVO_H

void set_servo_at_begining();

void setServoNewPos(int pos);
