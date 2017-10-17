#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial
#define TARGET_URL "http://******"
#define WIFI_SSID "******"
#define WIFI_PWD "******"
#define PERIOD 3600 // every minute
#define RAIN_PIN 14

ESP8266WiFiMulti WiFiMulti;

void setup() {

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(RAIN_PIN, INPUT);

    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFiMulti.addAP(WIFI_SSID, WIFI_PWD);

}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] ping...\n");
        
        if (digitalRead(RAIN_PIN) == LOW) {
          digitalWrite(LED_BUILTIN, LOW);
          USE_SERIAL.print("[STATUS] leak !\n");
          http.begin(TARGET_URL);
          int httpCode = http.GET();
          http.end();
          USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
        } else {
          USE_SERIAL.printf("[STATUS] no leak\n");
        }

    }

    delay(PERIOD);
}
