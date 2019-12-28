#include "pid.h"
#include "servo.h"
#include <PID_v1.h>
#include <cstdlib>
#include <HardwareSerial.h>
#include <Arduino.h>
#include "lcd.h"

#define Setpoint2_START 20 //wstępnie zadana temperatura (DHT)
#define MAX_TEMP_ZAD_MAX 260 //maksymalna możliwa do zadania temperatura
#define MIN_TEMP_ZAD_MIN 120 //minimalna możlliwa do zadania temperatura
#define TEMP_ZAD_MAX_PRZY_ROZPALANIU 200 //temperatura
#define TEMP_ZAD_MIN_PRZY_ROZPALANIU 170
#define CZAS_ROZPALANIA 1200000 //czas rozpalania w milisekundach
#define TEMP_ZAD_MAX 360 //zdefinioweanie zakresu temperatur termopara w kominie
#define TEMP_ZAD_MIN 180

int dystansPid = 30;// do przełączania agresywny/łagodnie sterowanie
double Setpoint, Input, Output; //Define Variables we'll be connecting to
double Setpoint2, Input2, Output2; //

double aggKp = 1, aggKi = 0.1, aggKd = 0.5; //Define the aggressive  Tuning Parameters
double consKp = 0.5, consKi = 0.025, consKd = 0.125;//Define the conservative Tuning Parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd,
          DIRECT); //PID SERVO Specify the links and initial tuning parameters
PID myPID2(&Input2, &Output2, &Setpoint2, 1, 0.05, 0.25, DIRECT);//PID TEMPERATURA



void setupPID() {
    //PID SERVO initialize the variables we're linked to
    Setpoint = SERVO_ZAMKN_MAX;
    myPID.SetSampleTime(3000); //determines how often the PID algorithm evaluates
    myPID.SetOutputLimits(SERVO_ZAMKN_MIN,
                          SERVO_ZAMKN_MAX - 10); //zakres wyjściowy, większy parametr serva większe zamknięcie
    myPID.SetControllerDirection(
            REVERSE); //wybranie trybu pracy DIRECT/REVERSE (reverse - aby input wzrósł output musi zmaleć)
    myPID.SetMode(AUTOMATIC);//turn the PID on
//    //PID TEMPERATURA initialize the variables we're linked to
//    myPID.SetTunings(consKp, consKi, consKd);

    Setpoint2 = Setpoint2_START;
    myPID2.SetSampleTime(2000); //determines how often the PID algorithm evaluates
    myPID2.SetOutputLimits(TEMP_ZAD_MIN,
                           TEMP_ZAD_MAX); //zakres wyjściowy przy rozpalaniu
    myPID2.SetControllerDirection(
            DIRECT); //wybranie trybu pracy DIRECT/REVERSE (reverse - aby input wzrósł output musi zmaleć)
    myPID2.SetMode(AUTOMATIC);//turn the PID on
}

void updatePID(double thermocoupleTemp, double heatIndex) {
    Input = thermocoupleTemp;

    double gap = abs(Setpoint - Input); //distance away from setpoint
    if (gap < dystansPid) //jeśli dalej od zadanej to agressive, jeśli bliżej conservative
    {
        myPID.SetTunings(consKp, consKi, consKd);//we're close to setpoint, use conservative tuning parameters
    } else {
        myPID.SetTunings(aggKp, aggKi, aggKd);//we're far from setpoint, use aggressive tuning parameters
    }
    myPID.Compute();//obliczanie PID

    Input2 = heatIndex;
    myPID2.Compute();//obliczanie PID2
    if (Output2) {
        Setpoint = Output2;//przekazanie obliczonej zadanej temperatury w kominie do Setpoint myPID
    } else {
        Serial.println("Output2 is NAN");
        Setpoint = TEMP_ZAD_MIN;
    }
    set_servo_new_pos(Output);//przekazanie obliczonej pozycji do zmiennej serva
    Serial.print("Setpoint: ");
    Serial.println(Setpoint);
    displayBasic(Setpoint, Setpoint2, heatIndex, thermocoupleTemp,
                 map(Output, SERVO_ZAMKN_MAX, SERVO_ZAMKN_MIN, 0, 100));
}