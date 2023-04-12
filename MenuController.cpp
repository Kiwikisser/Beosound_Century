#include "MenuController.h"

void MenuController::listenForEvent(){
  uint8_t encoderPushed;
  uint8_t encoderRotated;
  event registeredEvent = none;

  // 0 = not pushed, 1 = pushed
  encoderPushed = this->m_menuKnob->push();
  encoderRotated = this->m_menuKnob->rotate();

  if (encoderPushed == 1){
    registeredEvent = menu_ok;
    Serial.println(registeredEvent);
  }

  if(encoderRotated == 1){
    registeredEvent = menu_down;
    Serial.println(registeredEvent);
  } else if(encoderRotated == 2){
    registeredEvent = menu_up;
    Serial.println(registeredEvent);
  }

  if(registeredEvent != none){
    executeEvent(registeredEvent);
  }
}

void MenuController::executeEvent(event menuEvent){
  switch(menuEvent){
    case menu_up:
      menuNavigateUp();
      break;
    case menu_down:
      menuNavigateDown();
      break;
    case menu_ok:
      menuOk();
      break;
  }
}

void MenuController::menuNavigateUp(void){
  this->m_playerState->menuNavigateNext();
  // skip through media if not inside menu
}

void MenuController::menuNavigateDown(void){
  this->m_playerState->menuNavigatePrevious();
  // skip through media if not inside menu
}

void MenuController::menuOk(void){
  this->m_playerState->menuSelect();
}  
