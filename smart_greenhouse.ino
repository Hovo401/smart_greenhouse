// ===========================================================================
//  smart_greenhouse.ino
//  Точка входа. Здесь:
//    - Регистрируются все датчики (SensorManager)
//    - Регистрируются все реле   (RelayManager)
//    - Запускается приложение    (App)
//
//  Добавить датчик: см. Config.h (SensorId) и блок "Датчики" в setup()
//  Добавить реле:   см. Config.h (RelayId)  и блок "Реле"    в setup()
// ===========================================================================

#include "utils.h"
#include "Data.h"
Data data; // определяем здесь; extern объявлен в Globals.h

#include <Wire.h>
#include "Globals.h"
#include "Button.h"
#include "Pin.h"
#include "App.h"

RTC_DS3231 rtc;
App* app = nullptr;

void setup() {
  Serial.begin(115200);
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);

  // 1. Загружаем сохранённые данные из EEPROM
  data.begin();

  // 2. Инициализируем RTC
  if (!rtc.begin()) {
    Serial.println("[RTC] DS3231 not found");
  } else if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // ---- Датчики (порядок = SensorId enum в Config.h) ----
sensorManager.setDHT(&dht22);
  sensorManager.add("temp",  PIN_DHT22,       SensorType::DHT_TEMP);         // SENSOR_ID_TEMP  = 0
  sensorManager.add("hum",   PIN_DHT22,       SensorType::DHT_HUM);          // SENSOR_ID_HUM   = 1
  sensorManager.add("soil1", PIN_SENSOR1_HUM, SensorType::SENSOR_ANALOG, true); // SENSOR_ID_SOIL1 = 2 (инверт)
  sensorManager.add("s2",    PIN_SENSOR2,     SensorType::SENSOR_ANALOG);    // SENSOR_ID_S2    = 3
  sensorManager.add("s3",    PIN_SENSOR3,     SensorType::SENSOR_ANALOG);    // SENSOR_ID_S3    = 4
  sensorManager.add("s4",    PIN_SENSOR4,     SensorType::SENSOR_ANALOG);    // SENSOR_ID_S4    = 5
  sensorManager.add("s5",    PIN_SENSOR5,     SensorType::SENSOR_ANALOG);    // SENSOR_ID_S5    = 6

  // ---- Реле (порядок = RelayId enum в Config.h) ----
  relayManager.add(RELAY_1_HEATER,     "heater");      // RELAY_ID_HEATER     = 0
  relayManager.add(RELAY_2_HUMIDIFIER, "humidifier");  // RELAY_ID_HUMIDIFIER = 1
  relayManager.add(RELAY_3_LIGHT,      "light");       // RELAY_ID_LIGHT      = 2
  relayManager.add(RELAY_4_WINDOW1,    "window1");     // RELAY_ID_WINDOW1    = 3
  relayManager.add(RELAY_5_WINDOW2,    "window2");     // RELAY_ID_WINDOW2    = 4
  relayManager.add(RELAY_6_SPARE1,     "vent");        // RELAY_ID_VENT       = 5
  relayManager.add(RELAY_7_SPARE2,     "spare1");      // RELAY_ID_SPARE1     = 6
  relayManager.add(RELAY_8_SPARE3,     "spare2");      // RELAY_ID_SPARE2     = 7

  // 5. Запускаем приложение
  app = new App();
  app->setup();
}

void loop() {
  // Обновляем все датчики через SensorManager
  sensorManager.update();

  // Обновляем время с DS3231
  DateTime now = rtc.now();
  rtcHour   = now.hour();
  rtcMinute = now.minute();
  rtcSecond = now.second();

  app->loop();
  timer.update();
}

// ---- Таймер IDs (справка) ----
// Intervals:
//   ID  1 — мигание курсора        (MenuModule)
//   ID  2 — отрисовка меню         (MenuModule)
//   ID 10+ — PinTimerModule        (автоматически)
// Timeouts:
//   ID  0 — возврат в главное меню (ButtonControl)
