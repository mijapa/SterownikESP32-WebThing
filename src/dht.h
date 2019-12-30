#ifndef STEROWNIKESP32_WEBTHING_DHT_H
#define STEROWNIKESP32_WEBTHING_DHT_H
#endif //STEROWNIKESP32_WEBTHING_DHT_H

#define DHTPIN 16 // Pin which is connected to the DHT sensor.

void sample();

void setupDHT();

int readDhtHeatIndex(double *heatIndex);

void readDHT(float *humidity, float *temperature);

double readDHTtemp();

double readDHThumi();
