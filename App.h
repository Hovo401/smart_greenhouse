#pragma once
#include "Globals.h"
#include "Inkubator_MiniApp.h"

class App {
private:
  Inkubator_MiniApp inkubatorApp;

public:
  App() {}

  void setup() {
    inkubatorApp.setup();
  }

  void loop() {
    inkubatorApp.loop();
  }
};
