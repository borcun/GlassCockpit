#ifndef NavDisplay_h
#define NavDisplay_h

#include "Gauge.h"
#include "geographic_object.h"

namespace OpenGC
{

  class NavDisplay : public Gauge
  {
  public:

    NavDisplay();
    virtual ~NavDisplay();

    void Render();

    /** Called if the down mouse click applies to this object */
    void OnMouseDown(int button, float physicalX, float physicalY);

  protected:

    //////////// Graphics Functions ///////////////////////////////////////

    void PlotCourse();
    void PlotWaypoints();
    void PlotWindSpeedDirection();
    void PlotMap();

    /** Display geographic objects such as airports or navaids on the map */
    void PlotGeoObjs(std::list<GeographicObject*> &geoList);

    //////////// Helper functions /////////////////////////////////////////
		
    /** Convert mercator coordinates in meters into pixels relative to
     *  gauge center (where the aircraft is) */
    void PointToPixelCoord(float objNorthing, float objEasting, float &xPos, float &yPos);

    /** Check if an object is visible */
    bool PixelCoordIsVisible(float xPos, float yPos);
		
    //////////// Variables ////////////////////////////////////////////////
		
    /** The height (and width) of the component in nautical miles */
    float m_SizeNM;

    /** The font number provided to us by the font manager */
    int m_Font;

    /** Coordinates etc. used in graphics functions */
    float aircraftLat, aircraftLon, aircraftHeading;
    float mercatorNorthing, mercatorEasting;
		
    /** Compile-time layout options */
    static float CENTER_X, CENTER_Y, OVERLAY_Y;
    static int compass_interval; // interval in degrees between compass markings
	
    /** Raster map tile texture handles */
    static GLuint m_TileTextures[49];
    static bool m_TilesInitted;
	
  };

} // end namespace OpenGC

#endif
