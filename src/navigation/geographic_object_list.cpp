#include "geographic_object_list.h"
#include "conversion.h"

OpenGC::GeographicObjectList::GeographicObjectList()
  : std::list<GeographicObject *>()
{
  
}

OpenGC::GeographicObjectList::~GeographicObjectList() {
  for (auto it = begin(); it != end(); ++it) {
    if(nullptr != *it) {
      delete *it;
      *it = nullptr;
    }
  }
}

void OpenGC::GeographicObjectList::initialize(const std::string &path) {
  /*
    In general this function would compute all additional coordinate systems
    used for mapping, but for now it does only Mercator, as defined below

    L = latitude in radians (positive north)
    Lo = longitude in radians (positive east)
    E = easting (meters)
    N = northing (meters)

    For the sphere 

    E = r Lo
    N = r ln [ tan (pi/4 + L/2) ]

    where 

    r = radius of the sphere (meters)
    ln() is the natural logarithm
  */

  float lat, lon;
  bool isInSouthernHemisphere;
  float northing, easting;

  for (auto it = begin(); it != end(); ++it) {
      isInSouthernHemisphere = false;

      lat = (*it)->GetDegreeLat();
      lon = (*it)->GetDegreeLon();

      if (lat < 0.0f) {
	isInSouthernHemisphere = true;
	lat = lat * -1.0;
      }

      Conversion::LatLonToMercator(lat, lon, northing, easting);
      
      if (isInSouthernHemisphere) {
	northing = northing * -1.0;
      }

      (*it)->SetMercatorMeters(northing, easting);
  }

  return;
}
