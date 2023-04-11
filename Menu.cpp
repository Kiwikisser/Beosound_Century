#include "Menu.h"

String* Menu::getMenuItems(void){
  return this->m_menuItems;
}

uint8_t Menu::getMenuItemsCount(void){
  return this->m_menuItemsCount;
}