#ifndef radio_controller_h_INCLUDED
#define radio_controller_h_INCLUDED

#include <stdint.h>
#include "IEventController.h"

class RadioController : public IEventController {
  public:
    RadioController(PlayerState* playerState, SimpleRotary* rotaryEncoder) 
      :   m_playerState(playerState),
          m_radioKnob(rotaryEncoder){};

    void  listenForEvent(void) override;
    float getFrequency(void);

  protected:
    void executeEvent(event) override;
    void increaseFrequencyFM(void);
    void increaseFrequencyAM(void);
    void decreaseFrequencyFM(void);
    void decreaseFrequencyAM(void);
    void toggleAMFM(void);
    void setFrequency(void);

    PlayerState*    m_playerState;
    SimpleRotary*   m_radioKnob;
    modulation      m_modulation = fm;
    float           m_frequencyFM        = 96.9;
    float           m_minimumFrequencyFM = 87.5;
    float           m_maximumFrequencyFM = 108.0;
    float           m_stepFrequencyFM    = 0.1;
    uint16_t        m_frequencyAM        = 605;
    uint16_t        m_minimumFrequencyAM = 535; // 535-1605 kHz.
    uint16_t        m_maximumFrequencyAM = 1605;
    uint8_t         m_stepFrequencyAM    = 10;

};

#endif