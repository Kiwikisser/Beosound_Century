#ifndef ievent_controller_h_INCLUDED
#define ievent_controller_h_INCLUDED

#include <stdint.h>
#include <Arduino.h>
#include "Events.h"
#include "FeedbackController.h"
#include "PlayerState.h"
#include <SimpleRotary.h>

class IEventController {
  public:
//    IEventController(FeedbackController* fbc) : m_feedbackController(fbc){};

    virtual void listenForEvent() = 0;

  protected:
    virtual void executeEvent(event) = 0;
//    FeedbackController* m_feedbackController;
};

#endif
