#ifndef STEROWNIKESP32_WEBTHING_WEBTHING_H
#define STEROWNIKESP32_WEBTHING_WEBTHING_H
#endif //STEROWNIKESP32_WEBTHING_WEBTHING_H

void setupWebThing();

void updateWebThing(double temp, double hum, double d);

void updatePIDWebThing(double servo, double setpointChimney, double setpointRoom, double tempChimney, double tempRoom);

double readSetpointRoomTempFromGateway();