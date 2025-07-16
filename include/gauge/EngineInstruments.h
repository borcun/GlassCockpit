/**
 * Albatross engine instruments.
 */

#ifndef EngineInstruments_h
#define EngineInstruments_h

#include "Gauge.h"

namespace OpenGC
{

  class EngineInstruments : public Gauge
  {
  public:
    EngineInstruments();
    virtual ~EngineInstruments();

    /** Overloaded render function */
    void Render();

  protected:
    /** The font number provided to us by the font manager */
    int m_Font;

    /** Calculates frames per second. */
    double GetFPS();
  };

} // end namespace OpenGC

#endif
