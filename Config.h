#pragma once
#include <Arduino.h>

// ---- I2C (DS3231, LCD и т.п.) ----
const uint8_t PIN_I2C_SDA = 21;
const uint8_t PIN_I2C_SCL = 22;

// ---- Датчики ----
const uint8_t PIN_DHT22       = 27;
const uint8_t PIN_SENSOR1_HUM = 32;
const uint8_t PIN_SENSOR2     = 33;
const uint8_t PIN_SENSOR3     = 34;
const uint8_t PIN_SENSOR4     = 35;
const uint8_t PIN_SENSOR5     = 36;

// ---- Кнопки управления меню ----
const uint8_t PIN_BTN_MENU   = 16;
const uint8_t PIN_BTN_CURSOR = 17;
const uint8_t PIN_BTN_PLUS   = 18;
const uint8_t PIN_BTN_MINUS  = 19;

// ---- Реле (физические пины) ----
const uint8_t RELAY_1_HEATER     = 13;
const uint8_t RELAY_2_HUMIDIFIER = 14;
const uint8_t RELAY_3_LIGHT      = 15;
const uint8_t RELAY_4_WINDOW1    = 2;
const uint8_t RELAY_5_WINDOW2    = 4;
const uint8_t RELAY_6_SPARE1     = 5;
const uint8_t RELAY_7_SPARE2     = 25;
const uint8_t RELAY_8_SPARE3     = 26;

// ВАЖНО: LOW = выключено, HIGH = включено
const uint8_t RELAY_ON_LEVEL  = LOW;
const uint8_t RELAY_OFF_LEVEL = HIGH;

// ---- ID реле в RelayManager (регистрируются в setup() в этом порядке!) ----
// Чтобы добавить реле: 1) добавь пин выше, 2) добавь ID сюда, 3) вызови relayManager.add() в setup()
enum RelayId : uint8_t {
  RELAY_ID_HEATER     = 0,
  RELAY_ID_HUMIDIFIER = 1,
  RELAY_ID_LIGHT      = 2,
  RELAY_ID_WINDOW1    = 3,
  RELAY_ID_WINDOW2    = 4,
  RELAY_ID_VENT       = 5,
  RELAY_ID_SPARE1     = 6,
  RELAY_ID_SPARE2     = 7,
};

// ---- ID датчиков в SensorManager (регистрируются в setup() в этом порядке!) ----
// Чтобы добавить датчик: 1) добавь пин выше, 2) добавь ID сюда, 3) вызови sensorManager.add() в setup()
enum SensorId : uint8_t {
  SENSOR_ID_TEMP  = 0,
  SENSOR_ID_HUM   = 1,
  SENSOR_ID_SOIL1 = 2,
  SENSOR_ID_S2    = 3,
  SENSOR_ID_S3    = 4,
  SENSOR_ID_S4    = 5,
  SENSOR_ID_S5    = 6,
};
