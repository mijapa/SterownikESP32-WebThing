#include "maxThermocouple.h"
#include <max6675.h>


MAX6675 thermocouple(THERMO_CLK_PIN, THERMO_CS_PIN, THERMO_DO_PIN);

double readThermocouple() {
    double temp = thermocouple.readCelsius();
    Serial.print("Termocouple: ");
    Serial.println(temp);
    return temp;
}
