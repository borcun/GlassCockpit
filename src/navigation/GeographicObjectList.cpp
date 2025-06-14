#include <stdio.h>
#include "Debug.h"
#include "GeographicObjectList.h"
#include "Conversion.h"

namespace OpenGC
{
  using namespace std;

  GeographicObjectList::GeographicObjectList()
  {

  }

  GeographicObjectList::~GeographicObjectList()
  {
    // Delete all of the objects in this list
    GeographicObjectList::iterator it;

    for (it = this->begin(); it != this->end(); ++it)
      {
	if( (*it) != 0)
	  {
	    delete (*it);
	    (*it) = 0;
	  }
      }

  }

  bool GeographicObjectList::InitializeList(const std::string& filename)
  {
    // Try to load the data
    Assert(this->LoadData(filename), "unable to read data");

    // Do the fancy coordinate math
    this->ComputeAdditionalCoordinates();
    return true;
  }

  void GeographicObjectList::ComputeAdditionalCoordinates()
  {
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

    // lat/lon of geo object in degrees
    float lat, lon;

    // whether or not the coordinate is in the southern hemisphere
    bool isInSouthernHemisphere;

    // mercator coordinates
    float northing, easting;

    GeographicObjectList::iterator it;

    for (it = this->begin(); it != this->end(); ++it)
      {
	isInSouthernHemisphere = false;

	lat = (*it)->GetDegreeLat();
	lon = (*it)->GetDegreeLon();

	if(lat < 0)
	  {
	    isInSouthernHemisphere = true;
	    lat = lat * -1.0;
	  }

	Conversion::LatLonToMercator(lat, lon, northing, easting);

	if(isInSouthernHemisphere)
	  northing = northing * -1.0;

	(*it)->SetMercatorMeters(northing, easting);
      }
  }

} // end namespace OpenGC

