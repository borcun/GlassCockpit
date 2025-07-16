/**
 * Boeing 777 style primary flight display
 */

#ifndef PFD_h
#define PFD_h

#include "Gauge.h"

namespace OpenGC
{

  class PFD : public Gauge  
  {
  public:
    PFD();
    virtual ~PFD();

    /** Overloaded render function */
    void Render();
  };

} // end namespace OpenGC

#endif
