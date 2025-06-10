/**
 * AppObject is the functional piece of the OpenGC example program.
 * It is responsible for creating gauges and allocating/deallocating
 * the various objects used in OpenGC.
 */

#pragma once

#include "FLTKRenderWindow.h"
#include "XMLNode.h"

namespace OpenGC {
  class AppObject {
  public:
    AppObject();
    virtual ~AppObject();
    /** Setup and run the glass cockpit - enters message loop */
    bool Go(XMLNode rootNode);
    /** The idle function used to repeatedly update the display */
    void IdleFunction();

  private:
    /** Main pieces of the application */
    FLTKRenderWindow* m_pRenderWindow;
  };
}
