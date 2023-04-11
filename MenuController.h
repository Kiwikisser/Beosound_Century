#ifndef menu_controller_h_INCLUDED
#define menu_controller_h_INCLUDED

#include <stdint.h>
#include "IEventController.h"

class MenuController : public IEventController {
  public:
    MenuController(PlayerState* playerState, SimpleRotary* rotaryEncoder) 
      :   m_playerState(playerState),
          m_menuKnob(rotaryEncoder){};

    void  listenForEvent(void) override;

  protected:
    void executeEvent(event) override;

    void menuNavigateUp(void);
    void menuNavigateDown(void);
    void menuOk(void);

    PlayerState*    m_playerState;
    SimpleRotary*   m_menuKnob;

};

#endif