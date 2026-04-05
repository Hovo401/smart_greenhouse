#pragma once
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Globals.h"
#include "utils.h"

// Canvas — отрисовка LCD-меню.
// Читает датчики через sensorManager, реле через relayManager.
// Не хранит ссылок на Pin — всё через глобальные менеджеры.

class Canvas {
private:
  bool*          flicker;
  unsigned char* kursor;
  LiquidCrystal_I2C lcd;
  int this_position_menu = -1; // -1 = принудительная очистка при первом render

public:
  int max_menu = 3;

  Canvas(bool* flicker_, unsigned char* kursor_)
    : flicker(flicker_), kursor(kursor_), lcd(0x27, 16, 4)
  {}

  void init() {
    lcd.init();
    delay(200);
    lcd.backlight();
    lcd.clear();
  }

  void clear() { lcd.clear(); }

  void Rednder(int menu) {
    if (this_position_menu != menu) {
      lcd.clear();
      this_position_menu = menu;
    }
    switch (menu) {
      case 0: menu_0(); break;
      case 1: menu_1(); break;
      case 2: menu_2(); break;
      case 3: menu_3(); break;
    }
  }

private:
  void menu_0() {
    float t    = sensorManager.getValue(SENSOR_ID_TEMP);
    float h    = sensorManager.getValue(SENSOR_ID_HUM);
    int   soil = (int)sensorManager.getValue(SENSOR_ID_SOIL1);
    bool  lightOn = relayManager.get(RELAY_ID_LIGHT);

    lcd.setCursor(0, 0);
    lcd.print("Temp:"); lcd.print(t, 1);
    lcd.setCursor(10, 0);
    lcd.print(rtcHour); lcd.print(":"); lcd.print(rtcMinute); lcd.print(" ");
    lcd.print(pad4(soil));

    lcd.setCursor(0, 1);
    lcd.print("AirH:"); lcd.print(h, 1);

    lcd.setCursor(0, 2);
    lcd.print("->light ");
    lcd.print(lightOn ? "on " : "off");

    lcd.setCursor(0, 3);
    // Место для строки таймера (PinTimerModule)
  }

  void menu_1() {
    float soil = sensorManager.getValue(SENSOR_ID_SOIL1);

    lcd.setCursor(0, 0);
    lcd.print("watering");
    lcd.setCursor(11, 0);
    if (*kursor == 0 && *flicker) lcd.print(">"); else lcd.print(" ");
    lcd.setCursor(12, 0);
    lcd.print("Auto:"); lcd.print("onn");

    lcd.setCursor(0, 1);
    if (*kursor == 1 && *flicker) lcd.print(">"); else lcd.print(" ");
    lcd.setCursor(1, 1);
    lcd.print("val:"); lcd.print((int)soil);

    lcd.setCursor(9, 1);
    if (*kursor == 2 && *flicker) lcd.print(">"); else lcd.print(" ");
    lcd.setCursor(10, 1);
    lcd.print("minute:"); lcd.print(300);

    lcd.setCursor(0, 2);
    lcd.print("sensor: "); lcd.print(pad4((int)soil));

    lcd.setCursor(1, 3);
    lcd.print("w-time");
    lcd.setCursor(7, 3);
    if (*kursor == 3 && *flicker) lcd.print(">"); else lcd.print(" ");
    lcd.setCursor(8, 3);
    lcd.print(22);
    if (*kursor == 4 && *flicker) lcd.print(">"); else lcd.print(":");
    lcd.print(15);
    lcd.setCursor(13, 3);
    if (*kursor == 5 && *flicker) lcd.print(">"); else lcd.print(" ");
    lcd.setCursor(14, 3);
    lcd.print("rele:1");
  }

  void menu_2() {
    float t = sensorManager.getValue(SENSOR_ID_TEMP);

    lcd.setCursor(0, 0);
    lcd.print("temperature");
    lcd.setCursor(11, 0);
    if (*kursor == 0 && *flicker) lcd.print(">"); else lcd.print(" ");
    lcd.setCursor(12, 0);
    lcd.print("Auto:"); lcd.print("onn");

    lcd.setCursor(0, 1);
    if (*kursor == 1 && *flicker) lcd.print(">"); else lcd.print(" ");
    lcd.setCursor(1, 1);
    lcd.print("set:"); lcd.print(data.getSave_temperature(), 1);

    lcd.setCursor(9, 1);
    if (*kursor == 2 && *flicker) lcd.print(">"); else lcd.print(" ");
    lcd.setCursor(10, 1);
    lcd.print("cur:"); lcd.print(t, 1);

    lcd.setCursor(0, 2);
    lcd.print("hum set:"); lcd.print(data.getSave_humidity(), 0);

    lcd.setCursor(1, 3);
    lcd.print("w-time");
    lcd.setCursor(7, 3);
    if (*kursor == 3 && *flicker) lcd.print(">"); else lcd.print(" ");
    lcd.setCursor(8, 3);
    lcd.print(22);
    if (*kursor == 4 && *flicker) lcd.print(">"); else lcd.print(":");
    lcd.print(15);
    lcd.setCursor(13, 3);
    if (*kursor == 5 && *flicker) lcd.print(">"); else lcd.print(" ");
    lcd.setCursor(14, 3);
    lcd.print("rele:1");
  }

  void menu_3() {
    lcd.setCursor(0, 0);
    lcd.print("  timer control");
  }
};
