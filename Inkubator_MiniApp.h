#pragma once
#include "MenuModule.h"
#include "ButtonControl.h"
#include "TH_Controller.h"
#include "Globals.h"

class Inkubator_MiniApp {
private:
  MenuModule    menuModule;
  ButtonControl buttonControl;
  TH_Controller th_Controller;

public:
  Inkubator_MiniApp()
    : menuModule(),
      buttonControl(menuModule),
      th_Controller(RELAY_ID_HEATER, RELAY_ID_HUMIDIFIER)
  {
    // Восстанавливаем состояние подсветки из EEPROM
    // (реле уже зарегистрированы в setup() до создания App)
    relayManager.set(RELAY_ID_LIGHT, data.getInkubatorLight());
  }

  void setup() {
    menuModule.setup();
  }

  void loop() {
    buttonControl.update();
    th_Controller.loop();
  }
};
