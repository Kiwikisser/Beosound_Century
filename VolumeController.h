#ifndef volume_controller_h_INCLUDED
#define volume_controller_h_INCLUDED

#include "IEventController.h"

class VolumeController : public IEventController {
  public:
    VolumeController(PlayerState* playerState, SimpleRotary* rotaryEncoder) 
      :   m_playerState(playerState),
          m_volumeKnob(rotaryEncoder){};
  
    void listenForEvent() override;

  protected:
    void executeEvent(event) override;
    void printCurrentVolume(void);
    void increaseVolume(void);
    void decreaseVolume(void);
    void pauseOrPlay(void);
    void setVolume(void);

    uint8_t               m_volume = 2; // value between 0 and 16
    PlayerState*          m_playerState;
    SimpleRotary*         m_volumeKnob;
};

#endif
