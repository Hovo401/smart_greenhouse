#pragma once
#include <Arduino.h>
#include "Config.h"

// RelayManager — единственное место, которое управляет физическими реле.
//
// ВСЕ записи на реле проходят только через него.
// Это гарантирует: корректный уровень (RELAY_ON/OFF_LEVEL), единое состояние.
//
// Добавление нового реле:
//   1. В Config.h: добавь пин и новый RelayId (enum)
//   2. В setup():  relayManager.add(RELAY_X_..., "name") — строго в порядке RelayId!
//   3. Управляй:   relayManager.set(RELAY_ID_X, true/false)
//                  relayManager.toggle(RELAY_ID_X)
//                  relayManager.get(RELAY_ID_X)

class RelayManager {
public:
  static const uint8_t MAX_RELAYS = 12;
  static const uint8_t NONE       = 255; // "нет реле"

private:
  struct Relay {
    uint8_t     pin;
    bool        state;
    const char* name;
  };

  Relay   relays[MAX_RELAYS];
  uint8_t count = 0;

public:
  // Зарегистрировать реле. Вызывать в setup() в порядке RelayId enum.
  // Возвращает ID (= индекс).
  uint8_t add(uint8_t pin, const char* name, bool initialState = false) {
    if (count >= MAX_RELAYS) {
      Serial.println("[RelayManager] ERROR: MAX_RELAYS reached");
      return NONE;
    }
    uint8_t id     = count++;
    relays[id]     = { pin, initialState, name };
    pinMode(pin, OUTPUT);
    _apply(id);
    return id;
  }

  // Установить состояние реле (true = включить, false = выключить)
  void set(uint8_t id, bool on) {
    if (id >= count) return;
    relays[id].state = on;
    _apply(id);
  }

  // Переключить реле
  void toggle(uint8_t id) {
    if (id >= count) return;
    set(id, !relays[id].state);
  }

  // Получить текущее состояние (true = включено)
  bool get(uint8_t id) const {
    return id < count ? relays[id].state : false;
  }

  const char* getName(uint8_t id) const {
    return id < count ? relays[id].name : "?";
  }

  uint8_t getCount() const { return count; }

  // Отладка: вывести состояние всех реле в Serial
  void printAll() const {
    for (uint8_t i = 0; i < count; i++) {
      Serial.print("[relay] ");
      Serial.print(relays[i].name);
      Serial.print(": ");
      Serial.println(relays[i].state ? "ON" : "OFF");
    }
  }

private:
  // Единственное место физической записи на пин
  void _apply(uint8_t id) {
    digitalWrite(relays[id].pin,
      relays[id].state ? RELAY_ON_LEVEL : RELAY_OFF_LEVEL);
  }
};
