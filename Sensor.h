#pragma once
#include <Arduino.h>

// Тип датчика — определяет логику считывания в SensorManager
enum class SensorType : uint8_t {
  SENSOR_ANALOG,    // analogRead(pin) — переименовано из-за конфликта с ESP32
  DHT_TEMP,         // dht22.getTemperature()
  DHT_HUM,          // dht22.getHumidity()
  // Добавь новые типы сюда и обработай их в SensorManager::update()
};

struct Sensor {
  const char* name;
  uint8_t     pin;
  SensorType  type;
  float       value  = 0;
  bool        invert = false; // для датчиков, где значение = MAX - analogRead
};