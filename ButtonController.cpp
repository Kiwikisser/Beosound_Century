#include "Arduino.h"
#include "ButtonController.h"

void ButtonController::initialise(){
  for(uint8_t i = 0; i<m_buttonCount; i++){
    pinMode(m_buttons[i], INPUT_PULLUP);
  }
}

void ButtonController::listenForEvent(){
  unsigned long currentMillis = millis();
  const long debounceTime     = 120;
  bool newButtonState[6] = {};
  for(uint8_t i = 0; i<m_buttonCount; i++){
    newButtonState[i] = digitalRead(m_buttons[i]);
    if (this->oldButtonState[i] != newButtonState[i] && currentMillis - this->m_previousMillis >= debounceTime){
      if (newButtonState[i] == 0){
        this->m_previousMillis = currentMillis;
        
        // Surely there is a way to do this better
        if(this->m_playerState->playerIsOn()){
          this->oldButtonState[i] = newButtonState[i];
          executeEvent(m_buttons[i]);
        } else if (m_buttons[i] == power) {
          this->oldButtonState[i] = newButtonState[i];
          executeEvent(m_buttons[i]);
        }
      }

    }
    this->oldButtonState[i] = newButtonState[i];
  }
}

void ButtonController::executeEvent(event buttonEvent){
  switch(buttonEvent){
    case mode_cd: 
      Serial.println("Changing mode to CD");
      this->m_playerState->setPlayerMode(cd);
      break;
    case mode_radio: 
      Serial.println("Changing mode to Radio");
      this->m_playerState->setPlayerMode(radio);
      break;
    case mode_aux: 
      Serial.println("Changing mode to AUX");
      this->m_playerState->setPlayerMode(aux);
      break;
    case mode_tape: 
      Serial.println("Changing mode to Tape");
      this->m_playerState->setPlayerMode(tape);
      break;
    case open_cd: 
      Serial.println("Open CD lid");
      this->m_playerState->openCDCover();
      break;
    case power: 
      this->m_playerState->togglePower();
      break;
    
  }
}

bool ButtonController::isButtonPressed(void){
  
}
