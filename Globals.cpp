#include "Globals.h"

Data data;
Timer timer;

DHT22 dht22(PIN_DHT22);

int sensor_1_Value_HUM = 0;
int sensor_2_Value = 0;
int sensor_3_Value = 0;
int sensor_4_Value = 0;
int sensor_5_Value = 0;


// Все реле по умолчанию выключены
uint8_t relayStates[8] = {
  RELAY_OFF_LEVEL, // 0 - нагреватель
  RELAY_OFF_LEVEL, // 1 - увлажнитель
  RELAY_OFF_LEVEL, // 2 - освещение
  RELAY_OFF_LEVEL, // 3 - окна 1
  RELAY_OFF_LEVEL, // 4 - окна 2
  RELAY_OFF_LEVEL, // 5 - вентиляция
  RELAY_OFF_LEVEL, // 6 - свободное 1
  RELAY_OFF_LEVEL  // 7 - свободное 2
};

float t = 0;
float h = 0;

uint8_t rtcHour   = 0;
uint8_t rtcMinute = 0;
uint8_t rtcSecond = 0;