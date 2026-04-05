#pragma once
#include <Arduino.h>
#include "Config.h"
#include "Timer.h"
#include "RelayManager.h"
#include "SensorManager.h"
#include "Data.h"
#include <DHT22.h>
#include <RTClib.h>

// ---- Глобальные объекты (определены в Globals.cpp) ----
extern Timer         timer;
extern RelayManager  relayManager;
extern SensorManager sensorManager;
extern DHT22         dht22;

// ---- Глобальный объект данных (определён в .ino) ----
extern Data          data;

// ---- RTC (определён в .ino, нужен в Canvas) ----
extern RTC_DS3231    rtc;

// ---- Время с RTC (обновляется в loop()) ----
extern uint8_t rtcHour;
extern uint8_t rtcMinute;
extern uint8_t rtcSecond;
