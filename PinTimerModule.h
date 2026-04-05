#pragma once
#include "Globals.h"

// PinTimerModule — таймерное управление реле (вкл/выкл по расписанию).
// Использует RelayManager — никаких прямых digitalWrite.
// Каждый экземпляр получает уникальный ID таймера автоматически.
//
// Диаграмма цикла (timer_interval = time_pin_on + time_pin_off):
//   [<--- time_pin_on --->][<--- time_pin_off --->][<--- повтор --->]
//        реле ВКЛЮЧЕНО           реле ВЫКЛЮЧЕНО

class PinTimerModule {
private:
  short   timerId;   // ID в Timer (назначается автоматически)
  uint8_t relayId;   // ID в RelayManager
  bool    pin_on_ = true;

  // Статический счётчик ID таймеров для PinTimerModule.
  // Начинается с 10, чтобы не конфликтовать с ID MenuModule (1, 2).
  static short nextTimerId;

public:
  unsigned long timer_interval; // time_pin_on + time_pin_off
  unsigned long time_pin_on;
  unsigned long time_pin_off;
  bool          timer_on_;

  PinTimerModule(uint8_t relayId_,
                 unsigned long time_pin_on_,
                 unsigned long time_pin_off_,
                 bool timer_on__ = false)
    : relayId(relayId_),
      time_pin_on(time_pin_on_),
      time_pin_off(time_pin_off_),
      timer_on_(timer_on__)
  {
    timerId        = nextTimerId++;
    timer_interval = time_pin_on + time_pin_off;

    // Регистрируем пустой интервал — используем его только как таймер отсчёта
    timer.setIntervalDynamic([]() {}, &timer_interval, timerId);

    // Начальное состояние реле — выключено
    relayManager.set(relayId, false);
  }

  // ---- Сеттеры ----
  void setTime_pin_on(unsigned long v)  { time_pin_on  = v; timer_interval = time_pin_on + time_pin_off; }
  void setTime_pin_off(unsigned long v) { time_pin_off = v; timer_interval = time_pin_on + time_pin_off; }

  // ---- Геттеры (сколько времени прошло/осталось) ----
  unsigned long getElapsed() {
    float rem = timer.getIntervalTimeById(timerId);
    if (rem < 0) return 0;
    unsigned long out = timer_interval - (unsigned long)rem;
    return out > timer_interval ? 0 : out;
  }
  unsigned long getTime_pin_off_remaining() {
    float rem = timer.getIntervalTimeById(timerId);
    if (rem < 0) return 0;
    unsigned long r = (unsigned long)rem;
    return r > time_pin_off ? 0 : r;
  }
  bool isRelayOn() const { return pin_on_; }

  // Вызывать в каждом loop()
  void loop() {
    if (!timer_on_) {
      timer.setintervalLastExecutionTimeById(timerId);
    }

    // Реле включено в первой части цикла (time_pin_on), выключено во второй
    float rem        = timer.getIntervalTimeById(timerId);
    bool shouldBeOn  = (rem >= 0) && ((unsigned long)rem > time_pin_off);

    if (pin_on_ != shouldBeOn) {
      pin_on_ = shouldBeOn;
      relayManager.set(relayId, pin_on_);
    }
  }
};

short PinTimerModule::nextTimerId = 10;
