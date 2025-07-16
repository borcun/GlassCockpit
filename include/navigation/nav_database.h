/**
 * NavDatabase is the container that stores all other nav information
 * used by OpenGC.
 */

#pragma once

#include <string>
#include "nav_aid_list.h"
#include "airport_list.h"
#include "waypoint_list.h"
#include "flight_course.h"
#include "geographic_hash.h"

namespace OpenGC {
  class NavDatabase {
  public:
    static NavDatabase *getInstance(void);
    virtual ~NavDatabase();

    /** Load the nav data */
    void InitDatabase();
    /** Get the hashed navaid list */
    GeographicHash* GetNavaidHash() { return m_NavaidHash; }
    /** Get the hashed airport list */
    GeographicHash* GetAirportHash() { return m_AirportHash; }
    /** Get the waypoint list */
    WaypointList* GetWaypointList() { return m_WaypointList; }
    /** Get the flight path */
    FlightCourse* GetFlightCourse() { return m_FlightCourse; }

  private:
    static NavDatabase *m_instance;
    
    FlightCourse *m_FlightCourse;
    WaypointList *m_WaypointList;
    AirportList *m_AirportList;
    GeographicHash *m_AirportHash;
    NavaidList *m_NavaidList;
    GeographicHash *m_NavaidHash;

    /// default constructor
    NavDatabase();
  };
}
