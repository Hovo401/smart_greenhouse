#pragma once

#include <Arduino.h>

#include "Config.h"
#include "Data.h"
#include "Timer.h"

#include <DHT22.h>
#include <RTClib.h>

// ---- Глобальные объекты проекта ----
extern Data data;
extern Timer timer;

extern DHT22 dht22;
extern RTC_DS3231 rtc;

// ---- Глобальное состояние реле (8 штук) ----
extern uint8_t relayStates[8];

// ---- Глобальные значения датчиков/времени ----
extern float t;
extern float h;

extern uint8_t rtcHour;
extern uint8_t rtcMinute;
extern uint8_t rtcSecond;

extern int sensor_1_Value_HUM;
extern int sensor_2_Value;
extern int sensor_3_Value;
extern int sensor_4_Value;
extern int sensor_5_Value;

// ---- Инициализация реле ----
inline void initRelays() {
  const uint8_t RELAY_PINS[8] = {
    RELAY_1_HEATER, RELAY_2_HUMIDIFIER, RELAY_3_LIGHT,
    RELAY_4_WINDOW1, RELAY_5_WINDOW2, RELAY_6_SPARE1,
    RELAY_7_SPARE2, RELAY_8_SPARE3
  };
  for (int i = 0; i < 8; i++) {
    pinMode(RELAY_PINS[i], OUTPUT);
    digitalWrite(RELAY_PINS[i], RELAY_OFF_LEVEL);
  }
}