#include <HardwareSerial.h>
#include <ESP32Tone.h>
#include <Ticker.h>
#include "buzzer.h"

Ticker alarmTicker;

int freq = 2000;
int channel = 15;
int resolution = 8;
bool buzz = false;

void toneHello() {
    Serial.println("Tone Hello");
    ledcSetup(channel, freq, resolution);
    ledcAttachPin(BUZZER_PIN, channel);

//    ledcWrite(channel, 125);
//    ledcWriteTone(channel, 4000);
    delay(50);
    //todo change delay to timer
    ledcWrite(channel, 0);
//    ledcDetachPin(BUZZER_PIN);
//    digitalWrite(BUZZER_PIN, LOW);

}

void alarm() {
    Serial.println("ALARM");
    if (buzz) {
        buzz = false;
        ledcWrite(channel, 125);
    } else {
        buzz = true;
        ledcWrite(channel, 0);
    }
}

void startAlarm() {
    alarm();
    alarmTicker.attach(1, alarm);
}

void stopAlarm() {
    alarmTicker.detach();
    ledcWrite(channel, 0);
}
