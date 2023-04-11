#include "VolumeController.h"

void VolumeController::listenForEvent(){
  uint8_t encoderPushed;
  uint8_t encoderRotated;
  event registeredEvent = none;

  // 0 = not pushed, 1 = pushed
  encoderPushed = this->m_volumeKnob->push();
  encoderRotated = this->m_volumeKnob->rotate();

  if (encoderPushed == 1){
    registeredEvent = pause_play;
    Serial.println(registeredEvent);
  }

  if(encoderRotated == 1){
    registeredEvent = volume_up;
    Serial.println(registeredEvent);
  } else if(encoderRotated == 2){
    registeredEvent = volume_down;
    Serial.println(registeredEvent);
  }

  if(registeredEvent != none){
    executeEvent(registeredEvent);
  }
}

void VolumeController::executeEvent(event volumeEvent){
  switch(volumeEvent){
    case volume_up:
      increaseVolume();
      break;
    case volume_down:
      decreaseVolume();
      break;
    case pause_play:
      pauseOrPlay();
      break;
  }
}

void VolumeController::increaseVolume(){
  if(this->m_volume<16){
    this->m_volume++;
  } else {
    
  }
  this->setVolume();
}

void VolumeController::decreaseVolume(){
  if(this->m_volume>0){
    this->m_volume--;
  } else {
    
  }
  this->setVolume();
}

void VolumeController::setVolume(){
  this->m_playerState->updateVolume(this->m_volume);
}

void VolumeController::pauseOrPlay(){
//  if(this->feedbackController->checkIfPlayingSong() == true){
    // this->m_feedbackController->updatePlayback();
    this->m_playerState->togglePlay();
//  }
}
