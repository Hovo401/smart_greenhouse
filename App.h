#include "Globals.h"
#include "Inkubator_MiniApp.h"

class App{
  private:
    Inkubator_MiniApp Inkubator_MiniApp;
  public:
    App(){}

    void setup() {
      // timer.setInterval([](){
      //     Serial.println( String(t) + "|" + String(h) );
      //     Serial.println( "mi casa su casa" );
      // }, 1000, 3 );
      Inkubator_MiniApp.setup();
    }
    void loop() {
      Inkubator_MiniApp.loop();
    }
};