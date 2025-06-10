#pragma once

#include "GaugeComponent.h"

namespace OpenGC {
  // Boeing 777 style altitude tape
  class AltitudeTape : public GaugeComponent {
  public:
    AltitudeTape();
    virtual ~AltitudeTape();
    void Render();

  protected:
    /** The font number provided to us by the font manager */
    int m_Font;
  };
}
