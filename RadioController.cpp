#include "RadioController.h"

void RadioController::listenForEvent(){
  uint8_t encoderPushed;
  uint8_t encoderRotated;
  event registeredEvent = none;

  // 0 = not pushed, 1 = pushed
  encoderPushed = this->m_radioKnob->push();
  encoderRotated = this->m_radioKnob->rotate();

  if (encoderPushed == 1){
    registeredEvent = radio_fm_am;
    Serial.println(registeredEvent);
  }

  if(encoderRotated == 1){
    registeredEvent = radio_freq_up;
    Serial.println(registeredEvent);
  } else if(encoderRotated == 2){
    registeredEvent = radio_freq_down;
    Serial.println(registeredEvent);
  }

  if(registeredEvent != none){
    executeEvent(registeredEvent);
  }
}

void RadioController::executeEvent(event radioEvent){
  switch(radioEvent){
    case radio_freq_up:
      this->m_modulation == fm ? increaseFrequencyFM() : increaseFrequencyAM();
      break;
    case radio_freq_down:
      this->m_modulation == fm ? decreaseFrequencyFM() : decreaseFrequencyAM();
      break;
    case radio_fm_am:
      toggleAMFM();
      break;
  }
}

void RadioController::increaseFrequencyFM(void){
  if(this->m_frequencyFM < this->m_maximumFrequencyFM){
    this->m_frequencyFM += this->m_stepFrequencyFM;
  } else {
    
  }
  setFrequency();
}

void RadioController::increaseFrequencyAM(void){
  if(this->m_frequencyAM < this->m_maximumFrequencyAM){
    this->m_frequencyAM += this->m_stepFrequencyAM;
  } else {
    
  }
  setFrequency();  
}

void RadioController::decreaseFrequencyFM(void){
  if(this->m_frequencyFM > this->m_minimumFrequencyFM){
    this->m_frequencyFM -= this->m_stepFrequencyFM;
  } else {
    
  }
  setFrequency();
}

void RadioController::decreaseFrequencyAM(void){
  if(this->m_frequencyAM > this->m_minimumFrequencyAM){
    this->m_frequencyAM -= this->m_stepFrequencyAM;
  } else {
    
  }
  setFrequency();
}

void RadioController::setFrequency(void){
  Serial.println(this->m_frequencyAM);
  Serial.println(this->m_frequencyFM);
  this->m_playerState->updateFrequency(this->m_modulation == fm ? this->m_frequencyFM : this->m_frequencyAM);
}

void RadioController::toggleAMFM(void){
  this->m_modulation == fm ? this->m_modulation = am : this->m_modulation = fm;
  this->m_playerState->updateFrequencyModulation(this->m_modulation);
}