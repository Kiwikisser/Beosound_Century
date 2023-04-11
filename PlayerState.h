#ifndef playerstate_h_INCLUDED
#define playerstate_h_INCLUDED

#include <stdint.h>
#include "Arduino.h"
#include "FeedbackController.h"
#include "Events.h"
#include "Menu.h"

class PlayerState {
  public:
    PlayerState(FeedbackController* feedbackController, Menu* menu) 
    : m_feedbackController(feedbackController),
      m_playerMenu(menu){};

    bool playerIsOn(void);
    bool playerIsPlaying(void);
    void togglePower(void);
    void togglePlay(void);
    void setPlayerMode(mode);
    void openCDCover(void);
    void updateVolume(uint8_t);
    void updateFrequency(float);
    void updateFrequencyModulation(modulation);
    void menuNavigateNext(void);
    void menuNavigatePrevious(void);
    void menuSelect(void);

  protected:
    FeedbackController* m_feedbackController;
    Menu*     m_playerMenu;
    uint8_t   m_selectedMenuItem = 0;
    bool      m_insideMenu = false;

    bool      m_powerState;
    bool      m_isPlayingSong = false;
    String    m_nowPlayingNote = "Paused"; // now playing or paused
    String    m_nowPlayingSongName = "Smash Mouth";
    mode      m_playerMode = idle;
    uint8_t   m_playerVolume; // defined in two places now
    String    m_playerVolumeMessage = "Volume:";
    float     m_playerFrequency; // defined in two places now
    String    m_playerFrequencyMessage = "Frequency:";
    String    m_frequencySwitchMessage = "Freq. modulation:";
};

#endif