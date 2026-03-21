#include "MenuModule.h"
#include "ButtonControl.h"
#include "TH_Controller.h"
#include "Globals.h"

class Inkubator_MiniApp {
  public:
    Pin           pin_Light_3;
    MenuModule    menuModule;
    ButtonControl buttonControl;
    TH_Controller th_Controller;

    Inkubator_MiniApp() :
      pin_Light_3(RELAY_3_LIGHT, data.getInkubatorLight()),
      menuModule(pin_Light_3),
      buttonControl(menuModule, pin_Light_3),
      th_Controller(RELAY_1_HEATER, RELAY_2_HUMIDIFIER)
    {}

    void setup() {
      data.begin();
      menuModule.setup();
    }

    void loop() {
      buttonControl.update();
      th_Controller.loop();
    }
};