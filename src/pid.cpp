#include "pid.h"
#include <PID_v1.h>
#include <cstdlib>
#include <HardwareSerial.h>

int dystansPid = 30;// do przełączania agresywny/łagodnie sterowanie
double Setpoint, Input, Output; //Define Variables we'll be connecting to

double aggKp = 1, aggKi = 0.1, aggKd = 0.5; //Define the aggressive  Tuning Parameters
double consKp = 0.5, consKi = 0.025, consKd = 0.125;//Define the conservative Tuning Parameters

PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd,
          DIRECT); //PID SERVO Specify the links and initial tuning parameters



void setupPID() {
    Setpoint = 100;
    myPID.SetSampleTime(3000); //determines how often the PID algorithm evaluates
    myPID.SetOutputLimits(0, 100); //zakres wyjściowy, większy parametr serva większe zamknięcie
    myPID.SetControllerDirection(
            REVERSE); //wybranie trybu pracy DIRECT/REVERSE (reverse - aby input wzrósł output musi zmaleć)
    myPID.SetMode(AUTOMATIC);//turn the PID on
}

void updatePID(double input) {
    Input = input;

    double gap = abs(Setpoint - Input); //distance away from setpoint
    if (gap < dystansPid) //jeśli dalej od zadanej to agressive, jeśli bliżej conservative
    {
        myPID.SetTunings(consKp, consKi, consKd);//we're close to setpoint, use conservative tuning parameters
    } else {
        myPID.SetTunings(aggKp, aggKi, aggKd);//we're far from setpoint, use aggressive tuning parameters
    }

    myPID.Compute();//obliczanie PID

    Serial.print("Obliczony przez PID output: ");
    Serial.println(Output);
}