#include "Globals.h"

Timer         timer;
RelayManager  relayManager;
SensorManager sensorManager;
DHT22         dht22(PIN_DHT22);

uint8_t rtcHour   = 0;
uint8_t rtcMinute = 0;
uint8_t rtcSecond = 0;
