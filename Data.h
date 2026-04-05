#pragma once
#include <Arduino.h>
#include <Preferences.h>

// ----------------------------- Структуры данных -----------------------------
struct ClimateControlData {
    float save_temperature = 37.7f;
    float save_humidity    = 60.0f;
};

struct PinTimerRotationData {
    unsigned long time_pin_on  = 3000;
    unsigned long time_pin_off = 3600000;
    bool          timer_on_    = false;
};

struct SettingsData {
    bool inkubatorLight = true;
};

struct Data_ {
    ClimateControlData   climateControlData;
    PinTimerRotationData pinTimerRotationData;
    SettingsData         settingsData;
};

// ----------------------------- Класс управления -----------------------------
class Data {
private:
    Preferences  prefs;
    Data_        data_;
    const char*  NS = "app_st";

    void saveAll() {
        prefs.begin(NS, false);
        prefs.putFloat("temp",     data_.climateControlData.save_temperature);
        prefs.putFloat("hum",      data_.climateControlData.save_humidity);
        prefs.putULong("t_on",     data_.pinTimerRotationData.time_pin_on);
        prefs.putULong("t_off",    data_.pinTimerRotationData.time_pin_off);
        prefs.putBool ("timer_on", data_.pinTimerRotationData.timer_on_);
        prefs.putBool ("light",    data_.settingsData.inkubatorLight);
        prefs.end();
    }

public:
    Data() {} // пустой — читаем только в begin()

    // Вызывать ПЕРВЫМ в setup(), до всего остального
    void begin() {
        prefs.begin(NS, false);
        if (!prefs.isKey("temp")) {
            // Первый запуск — записываем дефолты
            prefs.end();
            saveAll();
        } else {
            // Загружаем сохранённые данные
            data_.climateControlData.save_temperature  = prefs.getFloat("temp",     37.7f);
            data_.climateControlData.save_humidity     = prefs.getFloat("hum",      60.0f);
            data_.pinTimerRotationData.time_pin_on     = prefs.getULong("t_on",     3000);
            data_.pinTimerRotationData.time_pin_off    = prefs.getULong("t_off",    3600000);
            data_.pinTimerRotationData.timer_on_       = prefs.getBool ("timer_on", false);
            data_.settingsData.inkubatorLight          = prefs.getBool ("light",    true);
            prefs.end();
        }
    }

    // ---------------------------- Сеттеры ----------------------------

    void setSave_temperature(float val) {
        if (val < 30.0f || val > 41.0f) return;
        data_.climateControlData.save_temperature = val;
        prefs.begin(NS, false);
        prefs.putFloat("temp", val);
        prefs.end();
    }

    void setSave_humidity(float val) {
        if (val < 40.0f || val > 95.0f) return;
        data_.climateControlData.save_humidity = val;
        prefs.begin(NS, false);
        prefs.putFloat("hum", val);
        prefs.end();
    }

    void setPinTime_pin_on(unsigned long val) {
        if (val < 1800000 || val > 86400000) return;
        data_.pinTimerRotationData.time_pin_on = val;
        prefs.begin(NS, false);
        prefs.putULong("t_on", val);
        prefs.end();
    }

    void setPinTime_pin_off(unsigned long val) {
        if (val < 1800000 || val > 86400000) return;
        data_.pinTimerRotationData.time_pin_off = val;
        prefs.begin(NS, false);
        prefs.putULong("t_off", val);
        prefs.end();
    }

    void setPinTimer_on_(bool val) {
        data_.pinTimerRotationData.timer_on_ = val;
        prefs.begin(NS, false);
        prefs.putBool("timer_on", val);
        prefs.end();
    }

    void setInkubatorLight(bool val) {
        data_.settingsData.inkubatorLight = val;
        prefs.begin(NS, false);
        prefs.putBool("light", val);
        prefs.end();
    }

    // ---------------------------- Геттеры ----------------------------
    float         getSave_temperature()  const { return data_.climateControlData.save_temperature; }
    float         getSave_humidity()     const { return data_.climateControlData.save_humidity; }
    unsigned long getPinTime_pin_on()    const { return data_.pinTimerRotationData.time_pin_on; }
    unsigned long getPinTime_pin_off()   const { return data_.pinTimerRotationData.time_pin_off; }
    bool          getPinTimer_on_()      const { return data_.pinTimerRotationData.timer_on_; }
    bool          getInkubatorLight()    const { return data_.settingsData.inkubatorLight; }
};
