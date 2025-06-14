/**
 * NavDatabase is the container that stores all other nav information
 * used by OpenGC.
 */

#ifndef NavDatabase_h
#define NavDatabase_h

#include <string>
#include "NavaidList.h"
#include "AirportList.h"
#include "WaypointList.h"
#include "FlightCourse.h"
#include "GeographicHash.h"

namespace OpenGC {
  class NavDatabase {
  public:
    static NavDatabase *getInstance(void);
    virtual ~NavDatabase();

    /** Load the nav data */
    void InitDatabase();

    /** Get the hashed navaid list */
    GeographicHash* GetNavaidHash() {return m_NavaidHash;}

    /** Get the hashed airport list */
    GeographicHash* GetAirportHash() {return m_AirportHash;}

    /** Get the waypoint list */
    WaypointList* GetWaypointList() {return m_WaypointList;}

    /** Get the flight path */
    FlightCourse* GetFlightCourse() {return m_FlightCourse;}

  private:
    static NavDatabase *m_instance;
    
    /** The flight path/course */
    FlightCourse *m_FlightCourse;
		
    /** A list of all waypoints */
    WaypointList *m_WaypointList;

    /** Airport list */
    AirportList *m_AirportList;

    /** Airport list hashed by lat/lon */
    GeographicHash *m_AirportHash;

    /** Navaid list */
    NavaidList *m_NavaidList;
		
    /** Navaid list hashed by lat/lon */
    GeographicHash *m_NavaidHash;

    /// default constructor
    NavDatabase();
  };

} // end namespace OpenGC

#endif

