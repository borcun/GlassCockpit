/*=========================================================================

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

  =========================================================================*/

#include <math.h>
#include "Debug.h"
#include "test_data_source.h"

OpenGC::TestDataSource::TestDataSource()
    : OpenGC::DataSource()
{
    // Set initial state
    m_airframe->SetStatus_Active(false);
    m_airframe->SetDirector_Active(false);
    m_airframe->SetGot_Data(false);
    m_airframe->SetStatus_Text_NoData("WAITING FOR CONNECTION");
    m_state = STATE_WAITING;

    m_airframe->SetStatus_Text1("YAW");
    m_airframe->SetStatus_Text2("ALT");
    m_airframe->SetStatus_Text3("BNK");
    m_airframe->SetStatus_Text4("VEL");
    m_airframe->SetStatus_Colour1(1);
    m_airframe->SetStatus_Colour2(1);
    m_airframe->SetStatus_Colour3(1);
    m_airframe->SetStatus_Colour4(1);
}

OpenGC::TestDataSource::~TestDataSource() {

}

bool OpenGC::TestDataSource::OnIdle(void) {
    // Generate Data
    static double t = 0.0;
    t += 1.0 / 24.0;

    switch (m_state) { 
    case STATE_WAITING: {
	if (t >= 1.0) {
	    m_airframe->SetStatus_Text_NoData("CONNECTED (TEST)");
	    m_state = STATE_CONNECTING;
	    LogPrintf("TestDataSource: Connected (test mode).\n");
	    return true;
	}
	else {
	    return false;
	}
	
	break;
    }
    case STATE_CONNECTING: {
	if (t >= 1.5) {
	    m_airframe->SetBarometric_Pressure(1010.0); // hPa ambient
	    m_airframe->SetGPS_Mode(3);
	    m_airframe->SetGPS_Sats(5);
	    m_airframe->SetGot_Data(true);
	    m_airframe->SetStatus_Active(true);
	    m_state = STATE_FD;
	    LogPrintf("TestDataSource: Activated status display.\n");
	}
	
	return false;
    }
    case STATE_FD: {
	if (t >= 5.0) {
	    m_airframe->SetStatus_Colour1(2);
	    m_airframe->SetStatus_Colour2(2);
	    m_airframe->SetStatus_Colour3(2);
	    m_airframe->SetStatus_Colour4(2);
	    m_airframe->SetDirector_Active(true);
	    m_state = STATE_RUNNING;
	    LogPrintf("TestDataSource: Flight Director on.\n");
	}
	
	break;
    }
    case STATE_RUNNING:
	break;
    }

    double roll = 0.3 * sin(t) * 180 / M_PI;
    double pitch = 0.15 * cos(t) * 180 / M_PI;
    double heading = fmodf(t * 15.0, 360.0);
    //double trueHeading = fmodf((t * 15) + 2 * sin(t), 360.0);
    //double heading = 60.0 * sin(t/4);

    if (heading < 0.0) {
	heading += 360.0;
    }
    
    double airspeed = t * 4;
    double vertSpeed = 200 * sin(t/2 + 0.5); // should be calculated
    //double alt = 200 + (30 * sin(t/6));
    double alt = t * 15;

    // Update Data
    
    // -------Orientation--------------
    m_airframe->SetRoll(roll);
    m_airframe->SetPitch(pitch);
    m_airframe->SetTrue_Heading(heading);
    m_airframe->SetTrack_Heading(360 - heading);

    // -------Speeds-------------------
    m_airframe->SetAirspeed_KT(airspeed);
    m_airframe->SetVertical_Speed_FPM(vertSpeed);
    m_airframe->SetGround_Speed_MS(0.0); // Knots

    // -------Accelerations------------
    m_airframe->SetAccel_Body_Fwd(0.0);
    m_airframe->SetAccel_Body_Right(0.0);
    m_airframe->SetAccel_Body_Down(1.0);

    // -------Altitude-----------------
    m_airframe->SetAltitude_MSL_Feet(alt);
    m_airframe->SetAltitude_AGL_Feet(0.0);
    m_airframe->SetBarometric_Pressure(1010.0);

    // -------Position-----------------
    m_airframe->SetLatitude(-43.479 + 0.005 * t); // }
    m_airframe->SetLongitude(172.523);            // } Christchurch
    //	m_airframe->SetLatitude(37.621134 + 0.005 * t); // }
    //	m_airframe->SetLongitude(-122.374530);          // } San Francisco
		
    // -------Engine-------------------
    m_airframe->SetEngine_RPM(4500.0 + 4500.0 * sin(t/2.2));
    m_airframe->SetEngine_CHT(125.0 + 125.0 * sin(t/2.5));
    m_airframe->SetEngine_EGT(500.0 + 500 * sin (t/3));
    m_airframe->SetEngine_Mixture(8.0 + 8.0 * sin(t/2));
    m_airframe->SetVoltage_Alternator(0.0);
    m_airframe->SetVoltage_Battery(0.0);

    // -------Extra Stuff--------------
    m_airframe->SetInternal_Temp(30 + 2*sin(t / 100.0));
    m_airframe->SetExternal_Temp(10 - 2*sin(t / 100.0));
    m_airframe->SetWind_Speed(10.0);
    m_airframe->SetWind_Direction(360.0 - heading);

    // -------Flight Director---------- (aka autopilot)
    m_airframe->SetDirector_Pitch(0.0);
    m_airframe->SetDirector_Roll(0.0);
    m_airframe->SetDirector_Heading(10.0);
    m_airframe->SetDirector_Altitude(400.0);
    m_airframe->SetDirector_Airspeed(80.5);

    return true;
}
