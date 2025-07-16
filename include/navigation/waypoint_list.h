#pragma once

#include "geographic_object_list.h"

namespace OpenGC {
  class WaypointList : public GeographicObjectList {
  public:
    WaypointList();
    virtual ~WaypointList();
    // Read a file contain waypoints, returns true if successful, else false
    bool LoadData(const std::string& fileName);
  };
}
