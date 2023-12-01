//#define DEBUG_SERIAL    1
//#define DEBUG_MQTT      1 
//#define useModulPower   1

#define SERIAL_RATE     115200    // Serial speed for status info
#define MAX485_DE       D0        // D1, DE pin on the TTL to RS485 converter
#define MAX485_RE_NEG   D0        // D2, RE pin on the TTL to RS485 converter
#define MAX485_RX       D1        // D5, RO pin on the TTL to RS485 converter
#define MAX485_TX       D2        // D6, DI pin on the TTL to RS485 converter
#define STATUS_LED      2         // Status LED on the Wemos D1 mini (D4)
#define UPDATE_MODBUS   2         // 1: modbus device is read every second
#define UPDATE_STATUS   30        // 10: status mqtt message is sent every 10 seconds
#define WIFICHECK       500       // how often check lost wifi connection

/*
// Update the below parameters for your project
// Also check NTP.h for some parameters as well
const char* ssid = "xxxx";           // Wifi SSID
const char* password = "xxxx";    // Wifi password
const char* mqtt_server = "192.168.x.xx";     // MQTT server
const char* mqtt_user = "xxxx";             // MQTT userid
const char* mqtt_password = "xxxx";         // MQTT password
const char* clientID = "growatt";                // MQTT client ID
const char* topicRoot = "growatt";             // MQTT root topic for the device, keep / at the end
*/


/*
// Comment the entire second below for dynamic IP (including the define)
// #define FIXEDIP   1
IPAddress local_IP(192, 168, 1, 205);         // Set your Static IP address
IPAddress gateway(192, 168, 1, 254);          // Set your Gateway IP address
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(192, 168, 1, 254);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional
*/