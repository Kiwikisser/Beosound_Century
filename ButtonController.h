#ifndef button_controller_h_INCLUDED
#define button_controller_h_INCLUDED

#include "IEventController.h"

class ButtonController : public IEventController {
  public:
    ButtonController(PlayerState* playerState, event* buttons) 
      :   m_playerState(playerState),
          m_buttons(buttons){};

    void initialise(void);
    void listenForEvent(void) override;

  protected:
    void executeEvent(event) override;
    bool isButtonPressed(void);
    
    PlayerState*          m_playerState;
    event*                m_buttons;
    const uint8_t         m_buttonCount = 6;
    unsigned long         m_previousMillis = 0;
};

#endif
