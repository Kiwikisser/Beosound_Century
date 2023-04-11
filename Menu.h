#ifndef menu_h_INCLUDED
#define menu_h_INCLUDED

#include <stdint.h>
#include <Arduino.h>

class Menu {
  public:
    // Menu();

    String* getMenuItems(void);
    uint8_t getMenuItemsCount(void);

  protected:
    static const uint8_t   m_menuItemsCount = 2;
    String    m_menuItems[m_menuItemsCount] = {
                "Radio stations",
                "Sound modes"
              };

};

#endif
