#pragma once

#include <cmath>
#include "Constants.h"

namespace OpenGC {
  class Conversion {
  public:
    /** Convert Lat/Lon into Mercator Meters */
    static void LatLonToMercator(float lat, float lon, float &northing, float &easting)
    {
      easting = EARTH_RADIUS * (lon * DEG_TO_RAD);
      northing = EARTH_RADIUS * log(tan(M_PI / 4.0 + (lat * DEG_TO_RAD) / 2.0));

      return;
    }
  };
}
