#include "Globals.h"

class ButtonControl {
  private:
    MenuModule& menuModule;
    Pin&        pinLight;

    Button menuBut;
    Button kursor;
    Button plus;
    Button minus;

  public:
    ButtonControl(MenuModule& menuModule_, Pin& pinLight_) :
      menuModule(menuModule_),
      pinLight(pinLight_),
      menuBut(PIN_BTN_MENU),
      kursor(PIN_BTN_CURSOR),
      plus(PIN_BTN_PLUS),
      minus(PIN_BTN_MINUS)
    {}

    void update() {
      if (menuBut.isPressed(false)) {
        menuModule.next();
      }

      switch (menuModule.getMenu()) {
        case 0: menu_0(); break;
        case 1: menu_1(); break;
        case 2: menu_2(); break;
      }

      if (Button::newActivityCall > 0) {
        timer.deliteTimeoutById(0);
        if (menuModule.getMenu() != 0) {
          static MenuModule& menuModule__ = menuModule;
          timer.setTimeout([]() {
            menuModule__.setMenu(0);
          }, 600000, 0);
        }
        Button::newActivityCall = 0;
      }
    }

    void menu_0() {
      if (plus.isPressed(false) || minus.isPressed(false)) {
        pinLight.setPinClick();
        data.setInkubatorLight(pinLight.getPinStatus());
      }
    }

    void menu_1() {
      if(menuModule.kursor == 0){
        if (plus.isPressed(true, 42)) {
          
        }

      }
      // if (menuModule.kursor == 2) {
      //   if (plus.isPressed(true, 42)) {
      //     data.setSave_temperature(data.getSave_temperature() + 0.1);
      //   }
      //   if (minus.isPressed(true, 42)) {
      //     data.setSave_temperature(data.getSave_temperature() - 0.1);
      //   }
      // }
      // if (menuModule.kursor == 3) {
      //   if (plus.isPressed(true, 100)) {
      //     data.setSave_humidity(data.getSave_humidity() + 1);
      //   }
      //   if (minus.isPressed(true, 100)) {
      //     data.setSave_humidity(data.getSave_humidity() - 1);
      //   }
      // }

      if (kursor.isPressed()) {
        menuModule.kursor = menuModule.kursor + 1 ;
        if(menuModule.kursor >= 6){ menuModule.kursor = 0; }
      }
    }

    void menu_2() {
      if (kursor.isPressed()) {
        menuModule.kursor = menuModule.kursor + 1 ;
        if(menuModule.kursor >= 6){ menuModule.kursor = 0; }
      }
    }
};