#pragma once

#include "geographic_object_list.h"

#define NUM_BINS_LAT	(90)
#define NUM_BINS_LONG	(180)

namespace OpenGC {
  /* GeographicHash stores geographic objects in 2x2 degree bins for
   * efficient rendering access. */
  class GeographicHash {
  public:
    GeographicHash(void);
    virtual ~GeographicHash();
    /** Insert all of the members of a geographics list into the hash */
    void InsertGeographicList(GeographicObjectList *pList);
    /** Get the object list for a bin containing lat/lon */
    std::list<GeographicObject *> &GetListAtLatLon(double lat, double lon);

  protected:
    /** Add a geographic object to the hash - for internal use */
    void InsertGeographicObject(GeographicObject* pObj);
    /** The spatial hash of geographic objects */
    std::list<GeographicObject *> m_GeoHash[NUM_BINS_LAT][NUM_BINS_LONG];
  };
}
