#include "pid.h"
#include "servo.h"
#include <PID_v1.h>
#include <HardwareSerial.h>
#include <Arduino.h>
#include "lcd.h"
#include "webthings.h"
#include "maxThermocouple.h"
#include "dht.h"

#define RoomTempSetpoint_START 20 //wstępnie zadana temperatura (DHT)
#define MAX_TEMP_ZAD_MAX 260 //maksymalna możliwa do zadania temperatura
#define MIN_TEMP_ZAD_MIN 120 //minimalna możlliwa do zadania temperatura
#define TEMP_ZAD_MAX_PRZY_ROZPALANIU 200 //temperatura
#define TEMP_ZAD_MIN_PRZY_ROZPALANIU 170
#define CZAS_ROZPALANIA 1200000 //czas rozpalania w milisekundach
#define TEMP_ZAD_MAX 360 //zdefinioweanie zakresu temperatur termopara w kominie
#define TEMP_ZAD_MIN 240

int dystansPid = 30;// do przełączania agresywny/łagodnie sterowanie
double ThermoSetpoint, ThermoInput, ServoOutput; //Define Variables we'll be connecting to
double RoomTempSetpoint, RoomTempInput, ThermoSetpointOutput; //

double aggKp = 1, aggKi = 0.1, aggKd = 0.5; //Define the aggressive  Tuning Parameters
double consKp = 0.5, consKi = 0.025, consKd = 0.125;//Define the conservative Tuning Parameters
PID servoPID(&ThermoInput, &ServoOutput, &ThermoSetpoint, consKp, consKi, consKd,
             DIRECT); //PID SERVO Specify the links and initial tuning parameters
PID thermoPID2(&RoomTempInput, &ThermoSetpointOutput, &RoomTempSetpoint, 1, 0.05, 0.25, DIRECT);//PID TEMPERATURA


void setupThermoPID() {
    RoomTempSetpoint = RoomTempSetpoint_START;
    thermoPID2.SetSampleTime(3000); //determines how often the PID algorithm evaluates
    thermoPID2.SetOutputLimits(TEMP_ZAD_MIN,
                               TEMP_ZAD_MAX); //zakres wyjściowy przy rozpalaniu
    thermoPID2.SetControllerDirection(
            DIRECT); //wybranie trybu pracy DIRECT/REVERSE (reverse - aby input wzrósł output musi zmaleć)
    thermoPID2.SetMode(AUTOMATIC);//turn the PID on
    thermoPID2.SetTunings(1, 0.05, 0.25);
}

void setupServoPID() {
    ThermoSetpoint = SERVO_ZAMKN_MAX;
    servoPID.SetSampleTime(3000); //determines how often the PID algorithm evaluates
    servoPID.SetOutputLimits(SERVO_ZAMKN_MIN,
                             SERVO_ZAMKN_MAX - 10); //zakres wyjściowy, większy parametr serva większe zamknięcie
    servoPID.SetControllerDirection(
            REVERSE); //wybranie trybu pracy DIRECT/REVERSE (reverse - aby input wzrósł output musi zmaleć)
    servoPID.SetMode(AUTOMATIC);//turn the PID on
    servoPID.SetTunings(consKp, consKi, consKd);
}

void setupPIDs() {
    setupServoPID();
    setupThermoPID();
}

void computeThermoSetpoint() {
    if (!readDhtHeatIndex(&RoomTempInput)) {
        Serial.println("Failed to read DHT temp");
        RoomTempInput = RoomTempSetpoint;
    }

    RoomTempInput *= 100;
    RoomTempInput = (int) RoomTempInput;
    RoomTempInput /= 100;

//    Serial.println(RoomTempInput);
//    Serial.println(ThermoSetpointOutput);
//    Serial.println(RoomTempSetpoint);

    thermoPID2.Compute();//obliczanie PID2


}

void computeServoPoition() {
    if (ThermoSetpointOutput > 10 && ThermoSetpointOutput < 500) {
        ThermoSetpoint = ThermoSetpointOutput;//przekazanie obliczonej zadanej temperatury w kominie do ThermoSetpoint servoPID
    } else {
        Serial.println("ThermoSetpointOutput is NAN");
        ThermoSetpoint = TEMP_ZAD_MIN;
    }

    ThermoInput = readThermocouple();
    //todo remove - test purpose only
    ThermoInput *= 10;
//    Serial.println(ThermoInput);
//    Serial.println(ServoOutput);
//    Serial.println(ThermoSetpoint);

//    double gap = abs(ThermoSetpoint - ThermoInput); //distance away from setpoint
//    if (gap < dystansPid) //jeśli dalej od zadanej to agressive, jeśli bliżej conservative
//    {
//        servoPID.SetTunings(consKp, consKi, consKd);//we're close to setpoint, use conservative tuning parameters
//    } else {
//        servoPID.SetTunings(aggKp, aggKi, aggKd);//we're far from setpoint, use aggressive tuning parameters
//    }
    servoPID.Compute();//obliczanie PID

}

void changeRoomTempSetpoint(double newRoomTempSetpoint) {
    if (newRoomTempSetpoint == 0) {
        return;
    }
    RoomTempSetpoint = newRoomTempSetpoint;
}

void calculatePIDs() {
    changeRoomTempSetpoint(readSetpointRoomTempFromGateway());
    computeThermoSetpoint();
    computeServoPoition();

    set_servo_new_pos(ServoOutput);//przekazanie obliczonej pozycji do zmiennej serva
    Serial.print("ThermoSetpoint: ");
    Serial.println(ThermoSetpoint);
    int servoPercentage = map(ServoOutput, SERVO_ZAMKN_MAX, SERVO_ZAMKN_MIN, 0, 100);
    displayBasic(ThermoSetpoint, RoomTempSetpoint, RoomTempInput, ThermoInput,
                 servoPercentage);
    updatePIDWebThing(servoPercentage, ThermoSetpoint, RoomTempSetpoint);
}
