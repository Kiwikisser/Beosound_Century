#include "FeedbackController.h"

void FeedbackController::initialise(){
  this->m_lcd->init();
  this->m_lcd->createChar(0, m_block);
  this->m_lcd->createChar(1, m_empty);
  this->m_lcd->createChar(2, m_arrow);
}

void FeedbackController::updateFeedback(unsigned long currentTime){
  if(currentTime > this->m_eventTimestamp + this->m_revertDelay && this->m_displayingActiveFeedback == true){
    Serial.println("Updating feedback");
    displayStoredMessage();
    this->m_displayingActiveFeedback = false;
  }
}

void FeedbackController::setRevertDelay(uint16_t newDelay){
  this->m_revertDelay = newDelay;
}

void FeedbackController::displayStoredMessage(){
  this->m_lcd->clear();
  this->m_lcd->home();
  this->m_lcd->print(this->m_messageOnTop);
  this->m_lcd->setCursor(0, 1);
  this->m_lcd->print(this->m_messageOnBot);
}

void FeedbackController::displayMenu(String* menuItems, uint8_t selectedItem){
  this->m_lcd->clear();
  this->m_lcd->setCursor(1, 0);
  uint8_t topOrBottomPosition = (selectedItem+1) % 2;
  
  if (topOrBottomPosition != 0){ // +1 to get to human numbers and % 2 to see if top or bottom needs highlight
    // get pos and pos +1 items and highlight topmost
    Serial.println("top selected");
    this->m_lcd->print(menuItems[selectedItem]);
    this->m_lcd->setCursor(1, 1);
    this->m_lcd->print(menuItems[selectedItem+1]);
    this->m_lcd->setCursor(0, selectedItem%2);
    this->m_lcd->write(byte(2)); // arrow for highlight
  } else {
    // get pos and pos -1 items and highlight botmost
    Serial.println("bot selected");
    this->m_lcd->print(menuItems[selectedItem-1]);
    this->m_lcd->setCursor(1, 1);
    this->m_lcd->print(menuItems[selectedItem]);
    this->m_lcd->setCursor(0, selectedItem%2);
    this->m_lcd->write(byte(2)); // arrow for highlight
  }
  setRevertDelay(3000);
  flagForActiveFeedback();
}

void FeedbackController::updateVolume(String message, uint8_t meterCount){
  uint8_t row = 1;
  this->m_lcd->clear();
  this->m_lcd->home();
  this->m_lcd->print(message);
  for(uint8_t i=0; i<meterCount; i++){
    this->m_lcd->setCursor(i, row);
    this->m_lcd->write(byte(0));
  }
  setRevertDelay(1500);
  flagForActiveFeedback();
}
void FeedbackController::updateFrequency(String message, float frequency){
  this->m_lcd->clear();
  this->m_lcd->home();
  this->m_lcd->print(message);
  this->m_lcd->setCursor(0, 1);
  this->m_lcd->print(frequency);
  setRevertDelay(1500);
  flagForActiveFeedback();
}

void FeedbackController::updateFrequencyModulation(String message, String mod){
  this->m_lcd->clear();
  this->m_lcd->home();
  this->m_lcd->print(message);
  this->m_lcd->setCursor(0, 1);
  this->m_lcd->print(mod);
  setRevertDelay(1500);
  flagForActiveFeedback();
}

void FeedbackController::feedbackModeToCd(){
  showMessageRevert("Changed mode to:", "CD", 1500);
}

void FeedbackController::feedbackModeToRadio(){
  showMessageRevert("Changed mode to:", "Radio", 1500);
}

void FeedbackController::feedbackModeToAUX(){
  showMessageRevert("Changed mode to:", "AUX", 1500);
}

void FeedbackController::feedbackModeToTape(){
  showMessageRevert("Changed mode to:", "Tape", 1500);
}

void FeedbackController::feedbackOpenCDCover(){
  showMessageRevert("CD cover open", "Insert CD", 3000);
}

//void FeedbackController::feedbackChangeMode(event media){
//  updatePlaybackMode(media);
//}

void FeedbackController::feedbackTogglePowerOn(){
  this->m_lcd->backlight();  
  showMessagePersist("Bang & Olufsen", "Beosound Century");
}

void FeedbackController::feedbackTogglePowerOff(){
  this->m_lcd->noBacklight();
  clearMessage();
}

void FeedbackController::feedbackPlayingSong(String playingNote, String songName){
  showMessagePersist(playingNote, songName);
}

void FeedbackController::flagForActiveFeedback(void){
  this->m_displayingActiveFeedback = true;
  this->m_eventTimestamp = millis();
}

void FeedbackController::showMessagePersist(String msgTop, String msgBot){
  Serial.println("printing persisting message");
  this->m_messageOnTop = msgTop;
  this->m_messageOnBot = msgBot;
  this->m_lcd->clear();
  this->m_lcd->home();
  this->m_lcd->print(msgTop);
  this->m_lcd->setCursor(0, 1);
  this->m_lcd->print(msgBot);
}

void FeedbackController::showMessageRevert(String msgTop, String msgBot, uint16_t revertDelay){
  Serial.println("printing reverting message");
  this->m_lcd->clear();
  this->m_lcd->home();
  this->m_lcd->print(msgTop);
  this->m_lcd->setCursor(0, 1);
  this->m_lcd->print(msgBot);
  setRevertDelay(revertDelay);
  flagForActiveFeedback();
  
  // delay(this->m_revertDelay);
  // this->m_lcd->clear();
  // this->m_lcd->home();
  // this->m_lcd->print(this->m_messageOnTop);
  // this->m_lcd->setCursor(0, 1);
  // this->m_lcd->print(this->m_messageOnBot);
}

void FeedbackController::clearMessage(){
  this->m_lcd->clear();
}
