#pragma once

#include "GeographicObject.h"

namespace OpenGC {
  class WaypointGeoObj : public GeographicObject {
  public:
    WaypointGeoObj() {}
    virtual ~WaypointGeoObj() {}
    void SetStyle(int style) { m_Style = style; }
    enum {STYLE_FUNDAMENTAL, STYLE_INTERP};

  protected:
    int m_Style;
  };
}
