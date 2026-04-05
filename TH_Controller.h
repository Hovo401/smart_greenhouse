#pragma once
#include "Globals.h"

// TH_Controller — управляет нагревателем и увлажнителем через RelayManager.
// Читает температуру и влажность из SensorManager.
// Целевые значения берёт из Data.

class TH_Controller {
private:
  uint8_t relayTempId; // ID нагревателя в RelayManager
  uint8_t relayHumId;  // ID увлажнителя в RelayManager

public:
  TH_Controller(uint8_t relayTempId_, uint8_t relayHumId_)
    : relayTempId(relayTempId_), relayHumId(relayHumId_) {}

  void loop() {
    float t = sensorManager.getValue(SENSOR_ID_TEMP);
    float h = sensorManager.getValue(SENSOR_ID_HUM);

    // Включаем нагреватель если температура НИЖЕ заданной
    relayManager.set(relayTempId, t < data.getSave_temperature());

    // Включаем увлажнитель если влажность НИЖЕ заданной
    relayManager.set(relayHumId,  h < data.getSave_humidity());
  }
};
