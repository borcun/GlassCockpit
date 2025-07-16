#pragma once

#include "geographic_object_list.h"

namespace OpenGC {
  class NavaidList : public GeographicObjectList {
  public:
    NavaidList();
    virtual ~NavaidList();
    /** Read a file contain navaids, returns true if successful, else false */
    bool LoadData(const std::string &fileName);
  };
}
