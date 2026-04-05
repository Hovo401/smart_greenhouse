#include "Canvas.h"
#include "Globals.h"

class MenuModule {
  private:
    Canvas canvas;
    int menu = 0;

  public:
    static bool fliker;
    unsigned char kursor = 0;

    MenuModule(Pin& pinLight_):
      canvas(&MenuModule::fliker, &kursor, pinLight_)
    {}

    // ---- get ----
    int  getMenu()   { return menu; }
    bool getFliker() { return MenuModule::fliker; }

    // ---- set ----
    bool setMenu(int num) {
      if (0 <= num && num <= canvas.max_menu) {
        // if (num == 1) {
        //   kursor = 2;
        // } else if (num == 2) {
        //   kursor = 1;
        // }
        kursor = 0;
        menu = num;
        return true;
      }
      return false;
    }

    void next() {
      if (menu + 1 > canvas.max_menu) {
        setMenu(0);
      } else {
        setMenu(menu + 1);
      }
    }

    void setup() {
      canvas.init();

      timer.setInterval([]() {
        MenuModule::fliker = !MenuModule::fliker;
      }, 400, 1);

      static int&    menu__ref   = menu;
      static Canvas& canvas__ref = canvas;
      timer.setInterval([]() {
        canvas__ref.Rednder(menu__ref);
      }, 100, 2);
    }
};

bool MenuModule::fliker = false;