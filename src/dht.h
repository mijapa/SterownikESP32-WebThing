#ifndef STEROWNIKESP32_WEBTHING_DHT_H
#define STEROWNIKESP32_WEBTHING_DHT_H
#endif //STEROWNIKESP32_WEBTHING_DHT_H

#define DHTPIN 16 // Pin which is connected to the DHT sensor.

void setupDHT();

int readDhtHeatIndex(double *heatIndex);

double readDHTtemp();

double readDHThumi();
