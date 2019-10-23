#include "webthings.h"
#include "Thing.h"

const char *sensorTypes[] = {"TemperatureSensor", "MultiLevelSensor", "Sensor", nullptr};
ThingDevice dhtSensor("dht4", "DHT22 Temperature & Humidity sensor", sensorTypes);
ThingProperty tempSensorProperty("temperature", "Temperature", NUMBER, "TemperatureProperty");
ThingProperty humiditySensorProperty("humidity", "Humidity", NUMBER, "LevelProperty");

void setupWebThing() {
    adapter = new WebThingAdapter("NodeMCU1", WiFi.localIP());

    dhtSensor.addProperty(&tempSensorProperty);
    dhtSensor.addProperty(&humiditySensorProperty);
    adapter->addDevice(&dhtSensor);

    adapter->begin();
    Serial.println("HTTP server started");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.print("/things/");
    Serial.println(dhtSensor.id);
}