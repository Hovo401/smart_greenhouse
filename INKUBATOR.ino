#include <Wire.h>
#include "Globals.h"


// ---- my libry ----
#include "Button.h"
#include "Pin.h"
// =================

#include "App.h"
App app;

RTC_DS3231 rtc;

void setup() {

  Serial.begin(115200);
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL); // SDA, SCL

  // Инициализация DS3231
  if (!rtc.begin()) {
    Serial.println("RTC DS3231 not found");
  } else {
    if (rtc.lostPower()) {
      // Один раз установить время (можете поменять на свое)
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
  }

  // Инициализация 8 реле
  initRelays();

  app.setup();
}

void loop() {
  // Обновляем датчики
  t = dht22.getTemperature();
  h = dht22.getHumidity();

  sensor_1_Value_HUM = analogRead(PIN_SENSOR1_HUM);
  sensor_2_Value = analogRead(PIN_SENSOR2);
  sensor_3_Value = analogRead(PIN_SENSOR3);
  sensor_4_Value = analogRead(PIN_SENSOR4);
  sensor_5_Value = analogRead(PIN_SENSOR5);

  Serial.println(sensor_1_Value_HUM);

  // Обновляем время с DS3231
  DateTime now = rtc.now();
  rtcHour = now.hour();
  rtcMinute = now.minute();
  rtcSecond = now.second();

  app.loop();
  timer.update();

}


// SetInterval creat id = 0; rotation_interval
// SetInterval creat id = 1; flicker cursor 
// setInterval creat id = 2; canvas loop

// setTimeout creat id = 0; beck to glavni menu 