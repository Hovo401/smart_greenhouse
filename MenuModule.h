#pragma once
#include "Canvas.h"
#include "Globals.h"

class MenuModule {
private:
  Canvas canvas;
  int    menu = 0;

public:
  static bool   fliker;
  unsigned char kursor = 0;

  MenuModule()
    : canvas(&MenuModule::fliker, &kursor)
  {}

  // ---- Геттеры ----
  int  getMenu()   { return menu; }
  bool getFliker() { return MenuModule::fliker; }

  // ---- Сеттеры ----
  bool setMenu(int num) {
    if (num < 0 || num > canvas.max_menu) return false;
    kursor = 0;
    menu   = num;
    return true;
  }

  void next() {
    setMenu(menu + 1 > canvas.max_menu ? 0 : menu + 1);
  }

  void setup() {
    canvas.init();

    // ID 1: мигание курсора
    timer.setInterval([]() {
      MenuModule::fliker = !MenuModule::fliker;
    }, 400, 1);

    // ID 2: отрисовка меню
    static int&    menu__ref   = menu;
    static Canvas& canvas__ref = canvas;
    timer.setInterval([]() {
      canvas__ref.Rednder(menu__ref);
    }, 100, 2);
  }
};

bool MenuModule::fliker = false;
