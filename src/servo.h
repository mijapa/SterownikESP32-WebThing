#ifndef STEROWNIKESP32_WEBTHING_SERVO_H
#define STEROWNIKESP32_WEBTHING_SERVO_H

#endif //STEROWNIKESP32_WEBTHING_SERVO_H

#define SERVO_ZAMKN_MAX 170 //zdefinowanie parametrów dla serwa przy piecu kominkowym, większy parametr serva większe zamknięcie
#define SERVO_ZAMKN_MIN  30

void set_servo_at_begining();

void setServoNewPos(int pos);
