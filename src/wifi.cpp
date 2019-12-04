#include <ESPAsyncWiFiManager.h>
#include <Ticker.h>
#include <ESPmDNS.h>
#include "wifi.h"


AsyncWebServer server(80);
DNSServer dns;
Ticker ledTicker;

void blink() {
    //toggle state
    int state = digitalRead(BUILTIN_LED);  // get the current state of GPIO1 pin
    digitalWrite(BUILTIN_LED, !state);     // set pin to the opposite state
}

void configModeCallback(AsyncWiFiManager *myWiFiManager) {
    Serial.println("Entered config mode");
    Serial.println(WiFi.softAPIP());
    //if you used auto generated SSID, print it
    Serial.println(myWiFiManager->getConfigPortalSSID());
    //entered config mode, make led toggle faster
    ledTicker.attach_ms(100, blink);
}

void setupWiFi() {

    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);
    Serial.begin(115200);


    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    AsyncWiFiManager wifiManager(&server, &dns);
    //reset settings - for testing
    //wifiManager.resetSettings();

    //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
    wifiManager.setAPCallback(configModeCallback);

    wifiManager.setConfigPortalTimeout(60);

    //fetches ssid and pass and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration
    if (!wifiManager.autoConnect()) {
        return;
//        Serial.println("failed to connect and hit timeout");
//        //reset and try again, or maybe put it to deep sleep
//        ESP.restart();
//        delay(1000);
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(WiFi.BSSIDstr());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

//    if (MDNS.begin("esp32")) {// Start the mDNS responder for esp8266.local
//        MDNS.addService("http", "tcp", 80);
//        MDNS.addServiceTxt("http", "tcp", "url", "http://esp32.local");
//        MDNS.addServiceTxt("http", "tcp", "webthing", "true");
//        Serial.println("MDNS responder started");
//    } else {
//        Serial.println("Error setting up MDNS responder!");
//    }
    ledTicker.detach();
}

void tryConnectWiFi() {
    Serial.println("tryConnectWiFi");
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    AsyncWiFiManager wifiManager(&server, &dns);
    wifiManager.setConfigPortalTimeout(1);
    wifiManager.autoConnect();
}