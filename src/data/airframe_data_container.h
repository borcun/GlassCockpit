/*
  =========================================================================

  Copyright (c) 2001-2004 Damion Shelton
  Copyright (c) 2005-2010 Hugo Vincent <hugo.vincent@gmail.com>
  All rights reserved.
  
  This project is distributed under the terms of the GNU General Public License
  Version 3 <http://www.gnu.org/licenses/gpl.html>.
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, specifically version 3 of the License.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  =========================================================================
*/

#ifndef AIRFRAME_DATA_CONTAINER_H
#define AIRFRAME_DATA_CONTAINER_H

#include "data_container.h"
#include "property_generator.h"

namespace OpenGC {
  class AirframeDataContainer : public DataContainer {
  public:
    AirframeDataContainer() : DataContainer() {}
    ~AirframeDataContainer()  {}
    
    // Heading and Location
    GENPROP(Roll, float, 0.0f); // Roll in degrees around the axis of flight, right roll +
    GENPROP(Pitch, float, 0.0f); // Pitch in degrees from horizontal, pitch up +
    GENPROP(True_Heading, float, 0.0f); // True heading in degrees
    GENPROP(Track_Heading, float, 0.0f); // Track over ground heading in degrees
    GENPROP(Latitude, double, 0.0); // Latitude in degrees (with fractional degrees) North +, South -
    GENPROP(Longitude, double, 0.0); // Longitude in degrees (with fractional degrees) East +, West -
    // Accelerations in body frame (used for turn coordinator), G's.
    GENPROP(Accel_Body_Fwd, float, 0.0f);
    GENPROP(Accel_Body_Right, float, 0.0f);
    GENPROP(Accel_Body_Down, float, 0.0f);

    // Speed
    GENPROP(Airspeed_KT, float, 0.0f); // True airspeed in knots
    GENPROP(Ground_Speed_MS, float, 0.0f); // Ground speed in meters/sec
    GENPROP(Vertical_Speed_FPM, float, 0.0f); // Rate of climb or descent, in feet per minute

    // Altitude
    GENPROP(Altitude_AGL_Feet, float, 0.0f); // Altitude in feet above ground level
    GENPROP(Altitude_MSL_Feet, float, 0.0f); // Altitude in feet above sea level
    GENPROP(Barometric_Pressure, float, 0.0f); // Barometric pressure hPa

    // Engine Parameters
    GENPROP(Engine_RPM, float, 0.0f); // Engine revolutions per minute
    GENPROP(Engine_CHT, float, 0.0f); // Engine cylinder head temperature (deg. C)
    GENPROP(Engine_EGT, float, 0.0f); // Engine exhaust gas temperature (deg. C)
    GENPROP(Engine_Mixture, float, 0.0f); // Engine mixture (as a percentage, 0 for lean, 100 for rich)
    GENPROP(Voltage_Alternator, float, 0.0f); // Alternator voltage
    GENPROP(Voltage_Battery, float, 0.0f); // Battery voltage

    // Flight Director
    GENPROP(Director_Active, bool, false); // Flight director Active
    GENPROP(Director_Roll, float, 0.0f);  // Flight director Bank
    GENPROP(Director_Pitch, float, 0.0f); // Flight director Pitch
    GENPROP(Director_Heading, float, 0.0f); // Flight director Heading
    GENPROP(Director_Altitude, float, 0.0f); // Flight director Altitude
    GENPROP(Director_Airspeed, float, 0.0f); // Flight director Airspeed
    GENPROP(Director_Vertical_Speed, float, 0.0f); // Flight director Vertical Speed (FPM)

    // Albatross Specific Stuff	
    GENPROP(Got_Data, bool, false); // Do we have incoming data
    GENPROP(Status_Active, bool, false); // Status indicator panel Active
    GENPROP(GPS_Mode, int32_t, 0); // Albatross GPS Mode
    GENPROP(GPS_Sats, int32_t, 0); // Albatross GPS Number of Satellites in view
    GENPROP(Internal_Temp, float, 0.0f); // Albatross internal temperature
    GENPROP(External_Temp, float, 0.0f); // Albatross external temperature
    GENPROP(Wind_Direction, float, 0.0f); // Albatross wind direction estimate
    GENPROP(Wind_Speed, float, 0.0f); // Albatross wind speed estimate
    // Albatross status text strings (max 3 chars)
    GENPROP(Status_Text1, std::string, "");
    GENPROP(Status_Text2, std::string, "");
    GENPROP(Status_Text3, std::string, "");
    GENPROP(Status_Text4, std::string, "");
    // Albatross status text colour (0 = off, 1 = red, 2 = green)
    GENPROP(Status_Colour1, int32_t, 0);
    GENPROP(Status_Colour2, int32_t, 0);
    GENPROP(Status_Colour3, int32_t, 0);
    GENPROP(Status_Colour4, int32_t, 0);
    // Text area for when we have no incoming data
    GENPROP(Status_Text_NoData, std::string, "");	
    // Time stamp
    GENPROP(TimeStamp, double, 0.0);
  };
}

#endif
