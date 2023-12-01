#include <Arduino.h>
#include <ModbusMaster.h>
#include <SoftwareSerial.h>
/*
RX      D1
TX      D2
RE_NEG  D0
*/

#define MAX485_DE D2
#define MAX485_RE_NEG D0

ModbusMaster node;

void preTransmission()
{
digitalWrite(MAX485_RE_NEG, 1);
digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
digitalWrite(MAX485_RE_NEG, 0);
digitalWrite(MAX485_DE, 0);
}

void setup()
{
pinMode(MAX485_RE_NEG, OUTPUT);
pinMode(MAX485_DE, OUTPUT);
// Init in receive mode
digitalWrite(MAX485_RE_NEG, 0);
digitalWrite(MAX485_DE, 0);

// Modbus communication runs at 115200 baud
Serial.begin(115200);

// Modbus slave ID 1
node.begin(1, Serial);
// Callbacks allow us to configure the RS485 transceiver correctly
node.preTransmission(preTransmission);
node.postTransmission(postTransmission);
}

void loop()
{
uint8_t result;

result = node.readInputRegisters(0x3100, 15);
if (result == node.ku8MBSuccess)
{
Serial.println(" - - - - - - - - - - - - - - ");
Serial.println("MAIN DETAILS:");
Serial.print("Input Voltage: ");
Serial.println(node.getResponseBuffer(0x00) / 100.0f);
Serial.print("Input Current: ");
Serial.println(node.getResponseBuffer(0x01) / 100.0f);
Serial.print("Input Power: ");
Serial.println((node.getResponseBuffer(0x02) +
node.getResponseBuffer(0x03) << 16) / 100.0f);
Serial.print("-: ");
Serial.println(node.getResponseBuffer(0x04) / 100.0f);
Serial.print("-: ");
Serial.println(node.getResponseBuffer(0x05) / 100.0f);
Serial.print("Charging Power: ");
Serial.println((node.getResponseBuffer(0x06) +
node.getResponseBuffer(0x07) << 16) / 100.0f);
Serial.print("-: ");
Serial.println(node.getResponseBuffer(0x08) / 100.0f);
Serial.print("-: ");
Serial.println(node.getResponseBuffer(0x09) / 100.0f);
Serial.print("-: ");
Serial.println(node.getResponseBuffer(0x0A) / 100.0f);
Serial.print("-: ");
Serial.println(node.getResponseBuffer(0x0B) / 100.0f);
Serial.print("Load Voltage: ");
Serial.println(node.getResponseBuffer(0x0C) / 100.0f);
Serial.print("Load Current: ");
Serial.println(node.getResponseBuffer(0x0D) / 100.0f);
Serial.print("Load Power: ");
Serial.println((node.getResponseBuffer(0x0E) +
node.getResponseBuffer(0x0F) << 16) / 100.0f);
}

node.clearResponseBuffer();

delay(1500);

result = node.readInputRegisters(0x3110, 4);
if (result == node.ku8MBSuccess)
{
Serial.println(" - - - - - - - - - - - - - - ");
Serial.println("TEMPERATURES:");
Serial.print("Battery Temperature: ");
Serial.println(node.getResponseBuffer(0x00) / 100.0f);
Serial.print("Temperature Inside Case: ");
Serial.println(node.getResponseBuffer(0x01) / 100.0f);
Serial.print("Battery SOC: ");
Serial.println(node.getResponseBuffer(0x02) / 100.0f);
Serial.print("Remote Battery Temperature: ");
Serial.println(node.getResponseBuffer(0x03) / 100.0f);
Serial.print("Battery Real Rated Power: ");
Serial.println(node.getResponseBuffer(0x04) / 100.0f);
}

node.clearResponseBuffer();

delay(1500);

result = node.readInputRegisters(0x3200, 2);
if (result == node.ku8MBSuccess)
{
Serial.println(" - - - - - - - - - - - - - - ");
Serial.println("STATUS:");
Serial.print("Battery Status: ");
Serial.println(node.getResponseBuffer(0x00));
Serial.print("Equipment Status: ");
Serial.println(node.getResponseBuffer(0x01));
Serial.print("Discharging Equipment Status: ");
Serial.println(node.getResponseBuffer(0x02));
}

node.clearResponseBuffer();

delay(1500);

result = node.readInputRegisters(0x3300, 24);
if (result == node.ku8MBSuccess)
{
Serial.println(" - - - - - - - - - - - - - - ");
Serial.println("STATISTICS:");
Serial.print("Max. PV Today: ");
Serial.println(node.getResponseBuffer(0x00) / 100.0f);
Serial.print("Min. PV Today: ");
Serial.println(node.getResponseBuffer(0x01) / 100.0f);
Serial.print("Max. Battery Voltage Today: ");
Serial.println((node.getResponseBuffer(0x02) +
node.getResponseBuffer(0x03) << 16) / 100.0f);
Serial.print("Min. Battery Voltage Today: ");
Serial.println((node.getResponseBuffer(0x04) +
node.getResponseBuffer(0x05) << 16) / 100.0f);
Serial.print("Consumed Energy Today: ");
Serial.println((node.getResponseBuffer(0x06) +
node.getResponseBuffer(0x07) << 16) / 100.0f);
Serial.print("Consumed Energy This Month: ");
Serial.println((node.getResponseBuffer(0x08) +
node.getResponseBuffer(0x09) << 16) / 100.0f);
Serial.print("Consumed Energy This Year: ");
Serial.println((node.getResponseBuffer(0x0A) +
node.getResponseBuffer(0x0B) << 16) / 100.0f);
Serial.print("Consumed Total Energy: ");
Serial.println((node.getResponseBuffer(0x0C) +
node.getResponseBuffer(0x0D) << 16) / 100.0f);
Serial.print("Generated Energy Today: ");
Serial.println((node.getResponseBuffer(0x0E) +
node.getResponseBuffer(0x0F) << 16) / 100.0f);
Serial.print("Generated Energy This Month: ");
Serial.println(node.getResponseBuffer(0x10) / 100.0f);
Serial.print("Generated Energy This Year: ");
Serial.println((node.getResponseBuffer(0x11) +
node.getResponseBuffer(0x12) << 16) / 100.0f);
Serial.print("Generated Energy Total: ");
Serial.println((node.getResponseBuffer(0x13) +
node.getResponseBuffer(0x14) << 16) / 100.0f);
Serial.print("Battery Voltage: ");
Serial.println(node.getResponseBuffer(0x15) / 100.0f);
Serial.print("Battery Current: ");
Serial.println((node.getResponseBuffer(0x16) +
node.getResponseBuffer(0x17) << 16) / 100.0f);
}

node.clearResponseBuffer();

delay(1500);
}