#pragma once

#include <list>
#include "geographic_object.h"

namespace OpenGC {
  class GeographicObjectList : public std::list<GeographicObject *> {
  public:
    GeographicObjectList();
    virtual ~GeographicObjectList();
    
    /** Initialize the object list - this consists of loading the data and 
     * computing positions in coordinates other than lat / lon. The data
     * loading stage should be overridden when implementing a derived 
     * class. Will automatically call either LoadDataBin or LoadDataAscii
     * depending on extension of filename (.bin->binary, .dat->ASCII */
    virtual void initialize(const std::string &path);
  };
}
