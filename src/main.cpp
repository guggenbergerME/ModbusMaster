#include <Arduino.h>
#include <SoftwareSerial.h> 
#include <ModbusMaster.h>         // Modbus master library for ESP8266

#include "globals.h"
#include "settings.h"
#include "growattInterface.h"


/////////////////////////////////////////////////////////////////////////// Funktionsprototypen
void ReadInputRegisters();



void ReadInputRegisters() {
  char json[1024];
  char topic[80];

  uint8_t result;

  digitalWrite(STATUS_LED, 0);

  result = growattInterface.ReadInputRegisters(json);
  if (result == growattInterface.Success) {
    leds[0] = CRGB::Green;
    FastLED.show();
    lastRGB = millis();
    ledoff = true;

#ifdef DEBUG_SERIAL
    Serial.println(result);
#endif
    sprintf(topic, "%s/data", topicRoot);
    mqtt.publish(topic, json);
    Serial.println("Data MQTT sent");

  } else if (result != growattInterface.Continue) {
    leds[0] = CRGB::Red;
    FastLED.show();
    lastRGB = millis();
    ledoff = true;

    Serial.print(F("Error: "));
    String message = growattInterface.sendModbusError(result);
    Serial.println(message);
    char topic[80];
    sprintf(topic, "%s/error", topicRoot);
    mqtt.publish(topic, message.c_str());
    delay(5);
  }
  digitalWrite(STATUS_LED, 1);
}