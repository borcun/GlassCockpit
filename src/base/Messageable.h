#pragma once

#include "MessageableList.h"

namespace OpenGC {
  /** Abstract base class for objects that can receive messages (i.e. are
   * messageable). Inherit from it and implement OnMessage() to receive
   * messages. */
  class Messageable {
  public:
    /** When a Messageable is constructed, add it to the global list
     * of messageable objects */
    Messageable() {
      MessageableList::getInstance()->Add(this);
    }
	
    /** When a Messageable is destructed, remove it from the global list
     * of messageable objects */
    virtual ~Messageable() {
      MessageableList::getInstance()->Remove(this);
    }
	
    /** Called when a message is triggered somewhere */
    virtual void OnMessage(Message message, void *data) = 0;
  };
} // end namespace OpenGC
