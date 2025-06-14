#ifndef GeographicObjectList_h
#define GeographicObjectList_h

#include <list>
#include "GeographicObject.h"

namespace OpenGC
{

  class GeographicObjectList : public std::list<GeographicObject*>
  {
  public:

    GeographicObjectList();
    virtual ~GeographicObjectList();

    /** Initialize the object list - this consists of loading the data and 
     * computing positions in coordinates other than lat / lon. The data
     * loading stage should be overridden when implementing a derived 
     * class. Will automatically call either LoadDataBin or LoadDataAscii
     * depending on extension of filename (.bin->binary, .dat->ASCII */
    bool InitializeList(const std::string& filename);

    /** Read binary or ASCII file that contains data, returns true if
     * successful,  else false. */
    virtual bool LoadData(const std::string& fileName) { return false; };

    /** Computes additional coordinate positions for the objects in the 
     * list. This is called by InitializeList(). */
    void ComputeAdditionalCoordinates();
  };

} // end namespace OpenGC

#endif

