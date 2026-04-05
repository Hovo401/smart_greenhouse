#pragma once
#include "Globals.h"
#include "MenuModule.h"
#include "Button.h"

class ButtonControl {
private:
  MenuModule& menuModule;

  Button menuBut;
  Button kursorBtn;
  Button plus;
  Button minus;

public:
  ButtonControl(MenuModule& menuModule_)
    : menuModule(menuModule_),
      menuBut   (PIN_BTN_MENU),
      kursorBtn (PIN_BTN_CURSOR),
      plus      (PIN_BTN_PLUS),
      minus     (PIN_BTN_MINUS)
  {}

  void update() {
    if (menuBut.isPressed(false)) {
      menuModule.next();
    }

    switch (menuModule.getMenu()) {
      case 0: _menu_0(); break;
      case 1: _menu_1(); break;
      case 2: _menu_2(); break;
    }

    // Сброс в главное меню через 10 мин без активности
    if (Button::newActivityCall > 0) {
      timer.deliteTimeoutById(0);
      if (menuModule.getMenu() != 0) {
        static MenuModule& ref = menuModule;
        timer.setTimeout([]() { ref.setMenu(0); }, 600000, 0);
      }
      Button::newActivityCall = 0;
    }
  }

private:
  void _menu_0() {
    // + / - переключают подсветку инкубатора
    if (plus.isPressed(false) || minus.isPressed(false)) {
      relayManager.toggle(RELAY_ID_LIGHT);
      data.setInkubatorLight(relayManager.get(RELAY_ID_LIGHT));
    }
  }

  void _menu_1() {
    if (menuModule.kursor == 0) {
      // TODO: логика меню полива
    }

    if (kursorBtn.isPressed()) {
      menuModule.kursor++;
      if (menuModule.kursor >= 6) menuModule.kursor = 0;
    }
  }

  void _menu_2() {
    if (menuModule.kursor == 1) {
      if (plus.isPressed(true, 42))  data.setSave_temperature(data.getSave_temperature() + 0.1f);
      if (minus.isPressed(true, 42)) data.setSave_temperature(data.getSave_temperature() - 0.1f);
    }
    if (menuModule.kursor == 2) {
      if (plus.isPressed(true, 100))  data.setSave_humidity(data.getSave_humidity() + 1.0f);
      if (minus.isPressed(true, 100)) data.setSave_humidity(data.getSave_humidity() - 1.0f);
    }

    if (kursorBtn.isPressed()) {
      menuModule.kursor++;
      if (menuModule.kursor >= 6) menuModule.kursor = 0;
    }
  }
};
