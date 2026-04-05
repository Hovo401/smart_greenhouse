#pragma once
#include <Arduino.h>
#include "Config.h"

// Pin — обёртка над одним цифровым выходом.
// Корректно использует RELAY_ON_LEVEL / RELAY_OFF_LEVEL из Config.h.
// Используется для реле, которым нужен отдельный объект (например, подсветка LCD).
// Для системных реле — используй RelayManager.

class Pin {
private:
  bool    state;
  uint8_t pin;

public:
  Pin(uint8_t pin_, bool initialOn = false)
    : pin(pin_), state(initialOn)
  {
    pinMode(pin, OUTPUT);
    _apply();
  }

  void on()     { state = true;   _apply(); }
  void off()    { state = false;  _apply(); }
  void toggle() { state = !state; _apply(); }

  // Псевдонимы для обратной совместимости
  void setPinON()    { on(); }
  void setPinOff()   { off(); }
  void setPinClick() { toggle(); }

  bool getPinStatus() const { return state; }

private:
  void _apply() {
    digitalWrite(pin, state ? RELAY_ON_LEVEL : RELAY_OFF_LEVEL);
  }
};
