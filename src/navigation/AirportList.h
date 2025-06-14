#pragma once

#include "GeographicObjectList.h"

namespace OpenGC {
  class AirportList : public GeographicObjectList {
  public:
    AirportList();
    virtual ~AirportList();

    /** Read binary file containing airport database,
     * returns true if successful, else false */
    bool LoadData(const std::string& fileName);
  };
} // end namespace OpenGC

