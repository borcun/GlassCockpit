#pragma once

#include "geographic_object.h"

namespace OpenGC {
  class WaypointGeoObj : public GeographicObject {
  public:
    enum {STYLE_FUNDAMENTAL, STYLE_INTERP};
    
    WaypointGeoObj() {}
    virtual ~WaypointGeoObj() {}
    void SetStyle(int style) { m_Style = style; }

  protected:
    int m_Style;
  };
}
