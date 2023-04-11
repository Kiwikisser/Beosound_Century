#ifndef feedback_controller_h_INCLUDED
#define feedback_controller_h_INCLUDED

#include <stdint.h>
#include "WString.h"
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

class FeedbackController {
  public:
    FeedbackController(LiquidCrystal_I2C* lcd) : m_lcd(lcd){};

    void initialise(void);
    void updateFeedback(unsigned long);
    void displayStoredMessage();

    void displayMenu(String*, uint8_t);

    void updateVolume(String, uint8_t);
    void updateFrequency(String, float);
    void updateFrequencyModulation(String, String);
    
    void feedbackModeToCd(void);
    void feedbackModeToRadio(void);
    void feedbackModeToAUX(void);
    void feedbackModeToTape(void);
    void feedbackOpenCDCover(void);
    void feedbackTogglePowerOn(void);
    void feedbackTogglePowerOff(void);
    void feedbackPlayingSong(String, String);

    void flagForActiveFeedback(void);
    void clearMessage(void);

  protected:
    void setRevertDelay(uint16_t);
    void showMessagePersist(String, String);
    void showMessageRevert(String, String, uint16_t);
  
    LiquidCrystal_I2C* m_lcd;
    String    m_messageOnTop;
    String    m_messageOnBot;
    uint16_t  m_revertDelay = 1500;
    String    m_brand = "BeoSound";
    String    m_model = "Century";
    unsigned long   m_eventTimestamp;
    bool      m_displayingActiveFeedback = false;

    byte m_block[8] = {
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
    };
    
    byte m_empty[8] = {
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
    };
    
    byte m_arrow[8] = {
      B10000,
      B11000,
      B11100,
      B11110,
      B11110,
      B11100,
      B11000,
      B10000,
    };
};

#endif
