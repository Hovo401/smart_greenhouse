#include "Globals.h"

class TH_Controller {
  private:
    unsigned char t_Pin;
    unsigned char h_Pin;

  public:
    TH_Controller(unsigned char t_Pin_, unsigned char h_Pin_) {
      t_Pin = t_Pin_;
      h_Pin = h_Pin_;
      pinMode(t_Pin, OUTPUT);
      pinMode(h_Pin, OUTPUT);
    }

    void loop() {
      // Включаем нагреватель если текущая температура НИЖЕ заданной
      if (t < data.getSave_temperature()) {
        digitalWrite(t_Pin, RELAY_ON_LEVEL);
      } else {
        digitalWrite(t_Pin, RELAY_OFF_LEVEL);
      }

      // Включаем увлажнитель если текущая влажность НИЖЕ заданной почви
      if (h < data.getSave_humidity()) {
        digitalWrite(h_Pin, RELAY_ON_LEVEL);
      } else {
        digitalWrite(h_Pin, RELAY_OFF_LEVEL);
      }
    }
};