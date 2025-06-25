#include <math.h>
#include "geographic_hash.h"

OpenGC::GeographicHash::GeographicHash(void) {

}

OpenGC::GeographicHash::~GeographicHash() {

}

/* Longitude:  -180------------0------------180
 * Bin:           0           90            180
 *
 * Lattitude: Bin:
 *    90       90
 *    |
 *    |
 *    0        45
 *    |
 *    |
 *   -90       0
 */
std::list<OpenGC::GeographicObject *> &OpenGC::GeographicHash::GetListAtLatLon(double lat, double lon) {
  int latBin = (int) floor(45.0 + lat / 2.0);
  int lonBin = (int) floor(90.0 + lon / 2.0);
  
  return m_GeoHash[latBin][lonBin];
}

void OpenGC::GeographicHash::InsertGeographicObject(GeographicObject *pObj) {
  GetListAtLatLon(pObj->GetDegreeLat(), pObj->GetDegreeLon()).push_back(pObj);
  return;
}

void OpenGC::GeographicHash::InsertGeographicList(GeographicObjectList* pList) {
  for (auto it = pList->begin(); it != pList->end(); ++it) {
    InsertGeographicObject(*it);
  }

  return;
}

