#pragma once
#include <Arduino.h>
#include <DHT22.h>
#include "Sensor.h"

// SensorManager — единственное место, где читаются датчики.
//
// Добавление нового датчика:
//   1. В Config.h: добавь пин и новый SensorId
//   2. В setup():  sensorManager.add("name", PIN_..., SensorType::ANALOG)
//   3. Читай значение: sensorManager.getValue(SENSOR_ID_...)
//
// Новый тип датчика (не ANALOG и не DHT):
//   1. Добавь значение в enum SensorType (Sensor.h)
//   2. Добавь ветку в SensorManager::update() ниже
//   3. В setup(): sensorManager.add(...)

class SensorManager {
public:
  static const uint8_t MAX_SENSORS = 12;

private:
  Sensor  sensors[MAX_SENSORS];
  uint8_t count = 0;
  DHT22*  dht   = nullptr;

public:
  // Вызвать до add(), передать указатель на DHT22
  void setDHT(DHT22* d) { dht = d; }

  // Зарегистрировать датчик. Возвращает его ID (= индекс в порядке регистрации)
  uint8_t add(const char* name, uint8_t pin, SensorType type, bool invert = false) {
    if (count >= MAX_SENSORS) {
      Serial.println("[SensorManager] ERROR: MAX_SENSORS reached");
      return 255;
    }
    sensors[count] = { name, pin, type, 0.0f, invert };
    return count++;
  }

  // Обновить все датчики. Вызывать каждый loop()
void update() {
    for (uint8_t i = 0; i < count; i++) {
      Sensor& s = sensors[i];
      switch (s.type) {
        case SensorType::SENSOR_ANALOG:
          s.value = s.invert
            ? (4096.0f - (float)analogRead(s.pin))
            : (float)analogRead(s.pin);
          break;
        case SensorType::DHT_TEMP:
          if (dht) s.value = dht->getTemperature();
          break;
        case SensorType::DHT_HUM:
          if (dht) s.value = dht->getHumidity();
          break;
        // ДОБАВЬ НОВЫЕ ТИПЫ ЗДЕСЬ
      }
    }
  }

  // Получить значение по ID
  float getValue(uint8_t id) const {
    return id < count ? sensors[id].value : 0.0f;
  }

  // Получить имя датчика по ID (для отладки)
  const char* getName(uint8_t id) const {
    return id < count ? sensors[id].name : "?";
  }

  uint8_t getCount() const { return count; }
};
