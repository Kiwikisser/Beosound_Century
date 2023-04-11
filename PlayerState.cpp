#include "PlayerState.h"

bool PlayerState::playerIsOn(void){
  return this->m_powerState == true;
}

bool PlayerState::playerIsPlaying(void){
  return this->m_isPlayingSong == true;
}

void PlayerState::togglePower(void){
  this->m_powerState = !this->m_powerState;
  this->m_powerState ? this->m_feedbackController->feedbackTogglePowerOn() : this->m_feedbackController->feedbackTogglePowerOff();
}

void PlayerState::togglePlay(void){
  if (this->m_playerMode!=idle) {
    Serial.println("Pause unpause");
    this->m_isPlayingSong = !this->m_isPlayingSong;
    this->m_isPlayingSong ? this->m_nowPlayingNote = "Playing..." : this->m_nowPlayingNote = "Paused.";
    this->m_feedbackController->feedbackPlayingSong(this->m_nowPlayingNote, this->m_nowPlayingSongName);
  } else {
    // tell user to select a mode
  } 
}

void PlayerState::setPlayerMode(mode playerMode){
  this->m_playerMode = playerMode;
  switch (playerMode) {
    case cd:
      this->m_feedbackController->feedbackModeToCd();
      break;
    case radio:
      this->m_feedbackController->feedbackModeToRadio();
      break;
    case aux:
      this->m_feedbackController->feedbackModeToAUX();
      break;
    case tape:
      this->m_feedbackController->feedbackModeToTape();
      break;
    case idle:
      break;
  }
}

void PlayerState::openCDCover(void){
  this->m_feedbackController->feedbackOpenCDCover();
}

void PlayerState::updateVolume(uint8_t volume){
  this->m_playerVolume = volume;
  this->m_feedbackController->updateVolume(this->m_playerVolumeMessage, this->m_playerVolume);
}

void PlayerState::updateFrequency(float frequency){
  this->m_playerFrequency = frequency;
  this->m_feedbackController->updateFrequency(this->m_playerFrequencyMessage, this->m_playerFrequency);
}

void PlayerState::updateFrequencyModulation(modulation mod){
  this->m_feedbackController->updateFrequencyModulation(this->m_frequencySwitchMessage,  mod == fm ? "FM" : "AM");
}

void PlayerState::menuNavigateNext(void){
  /*
  retrieve menu items
  retrieve current selected item from list
  selected + 1
  write out visible items to feedbackhandler

  +1
  displayvisible menu items
*/  
  String* menuItems = this->m_playerMenu->getMenuItems();
  if(this->m_selectedMenuItem<this->m_playerMenu->getMenuItemsCount()-1){
    this->m_selectedMenuItem++;
  }
  this->m_feedbackController->displayMenu(menuItems, this->m_selectedMenuItem);
  Serial.println((this->m_selectedMenuItem+1)%2);
  Serial.println((this->m_selectedMenuItem)%2);
}

void PlayerState::menuNavigatePrevious(void){
  String* menuItems = this->m_playerMenu->getMenuItems();
  if(this->m_selectedMenuItem>0){
    this->m_selectedMenuItem--;
  }
  this->m_feedbackController->displayMenu(menuItems, this->m_selectedMenuItem);
  Serial.println(menuItems[this->m_selectedMenuItem%2]);
  Serial.println(menuItems[this->m_selectedMenuItem+1%2]);

}

void PlayerState::menuSelect(void){
  if (this->m_insideMenu){
    // go into submenu
  } else {
    String* menuItems = this->m_playerMenu->getMenuItems();
    this->m_feedbackController->displayMenu(menuItems, this->m_selectedMenuItem);
    Serial.println(menuItems[this->m_selectedMenuItem%2]);
    Serial.println(menuItems[this->m_selectedMenuItem+1%2]);
  }

  // Serial.println(testString[0]);
  // Serial.println(testString[1]);

/*
  enter menu
  set selected
  display visible menu items
  highlight item
  if menu open -> nest into item for sub items
    (retrieve sub items)
    keep parent menu item known?
  Reset after ~3s in activity
  
*/  
}