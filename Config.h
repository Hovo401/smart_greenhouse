#pragma once

#include <Arduino.h>

// Глобальные настройки проекта и пины

// ---- I2C (DS3231, LCD и т.п.) ----
const uint8_t PIN_I2C_SDA = 21;
const uint8_t PIN_I2C_SCL = 22;

// ---- Датчики ----
// DHT22
const uint8_t PIN_DHT22 = 27;

// ---- Кнопки управления меню ----
// Четыре соседних цифровых пина под кнопки (не конфликтуют с ADC1 датчиков)
// Порядок: MENU, CURSOR, PLUS, MINUS
const uint8_t PIN_BTN_MENU   = 16;
const uint8_t PIN_BTN_CURSOR = 17;
const uint8_t PIN_BTN_PLUS   = 18;
const uint8_t PIN_BTN_MINUS  = 19;

// ---- Аналоговые датчики (ADC1, не конфликтуют с Wi‑Fi) ----
// ADC1: GPIO32,32,33,34,35,36
const uint8_t PIN_SENSOR1_HUM = 32;
const uint8_t PIN_SENSOR2 = 33;
const uint8_t PIN_SENSOR3 = 34;
const uint8_t PIN_SENSOR4 = 35;
const uint8_t PIN_SENSOR5 = 36;

// ---- Реле (8 штук) ----
// Отдельные переменные для каждого реле
const uint8_t RELAY_1_HEATER = 13;       // нагреватель
const uint8_t RELAY_2_HUMIDIFIER = 14;   // увлажнитель
const uint8_t RELAY_3_LIGHT = 15;        // основное освещение инкубатора
const uint8_t RELAY_4_WINDOW1 = 2;       // реле окон
const uint8_t RELAY_5_WINDOW2 = 4;       // реле окон
const uint8_t RELAY_6_SPARE1  = 5;       // VENT
const uint8_t RELAY_7_SPARE2 = 25;       // свободное реле 1
const uint8_t RELAY_8_SPARE3 = 26;       // свободное реле 2

// Уровни управления реле
// ВАЖНО: у вас LOW = выключено, HIGH = включено
const uint8_t RELAY_ON_LEVEL = HIGH;
const uint8_t RELAY_OFF_LEVEL = LOW;

