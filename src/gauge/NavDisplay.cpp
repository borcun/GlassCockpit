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

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>

#include "Globals.h"
#include "NavDatabase.h"
#include "RasterMapManager.h"
#include "Constants.h"
#include "CircleEvaluator.h"
#include "data_source.h"
#include "NavDisplay.h"
#include "GeographicObject.h"
#include "WaypointGeoObj.h"
#include "AirportGeoObj.h"
#include "NavaidGeoObj.h"

namespace OpenGC
{    
  float NavDisplay::CENTER_X = 90.0, NavDisplay::CENTER_Y = 95.0, NavDisplay::OVERLAY_Y = 45.0;
  int NavDisplay::compass_interval = 20;
	
  GLuint NavDisplay::m_TileTextures[49];
  bool NavDisplay::m_TilesInitted;

  NavDisplay::NavDisplay()
  {
    //this->SetGaugeOutline(true);

    m_Font = FontManager::getInstance()->LoadDefaultFont();

    m_PhysicalPosition.first = 0;
    m_PhysicalPosition.second = 0;

    m_PhysicalSize.first = 181; // really 180, but give extra space so there is no nasty
    m_PhysicalSize.second = 262; // edge visible at the right hand edge of the window.

    m_Scale.second = 1.0;
    m_Scale.first = 1.0;

    // Set initial gauge size in nautical miles per side
    m_SizeNM = 2.0;
	
    m_TilesInitted = false;
  }

  NavDisplay::~NavDisplay()
  {
    glDeleteTextures(49, &m_TileTextures[0]);
  }

  void NavDisplay::Render()
  {
    Gauge::Render();

    ///////////////////////////////////////////////////////////////////////////
    // Get the data, and convert to mercator coordinates
    ///////////////////////////////////////////////////////////////////////////
	
    // Get the heading
    aircraftHeading = Globals::data_source->GetAirframe()->GetTrue_Heading();

    // Where is the aircraft?
    aircraftLat = Globals::data_source->GetAirframe()->GetLatitude();
    aircraftLon = Globals::data_source->GetAirframe()->GetLongitude();

    // FIXME what was this all about??
    //	bool isInSouthernHemisphere = false;
    //	if(aircraftLat < 0)
    //	{
    //		isInSouthernHemisphere = true;
    //		aircraftLat = aircraftLat * -1;
    //	}
	
    // Northing and Easting in nautical miles (Mercator Coordinates)
    GeographicObject::LatLonToMercator(aircraftLat, aircraftLon, mercatorNorthing, mercatorEasting);
    
    mercatorNorthing /= METER_PER_NM;
    mercatorEasting /= METER_PER_NM;

    //	if(isInSouthernHemisphere)
    //		mercatorNorthing = mercatorNorthing * -1.0;

    glMatrixMode(GL_MODELVIEW);
	
    ///////////////////////////////////////////////////////////////////////////
    // Draw Layer 0: the map
    ///////////////////////////////////////////////////////////////////////////
	
    glPushMatrix();
    glTranslatef(CENTER_X, CENTER_Y, 0.0);
    glRotatef(aircraftHeading, 0, 0, 1);

    PlotMap();
    glPopMatrix();
	
    ///////////////////////////////////////////////////////////////////////////
    // Draw Layer 1: the range circles and marks
    ///////////////////////////////////////////////////////////////////////////
	
    glColor3ub(255, 255, 255);
    glLineWidth(1.5);
	
    // Range circles
    CircleEvaluator *aCircle = Globals::circle_evaluator;
    aCircle->SetDegreesPerPoint(5.0);
    aCircle->SetRadius(40.0);
    aCircle->SetOrigin(CENTER_X, CENTER_Y);
    aCircle->SetArcStartEnd(0.0, 360.0);
	
    aCircle->ResetVertices();
    aCircle->Evaluate();
    aCircle->Render(GL_LINE_STRIP);
	
    aCircle->SetRadius(80.0);
    aCircle->SetArcStartEnd(0.0, 360.0);
    aCircle->ResetVertices();
    aCircle->Evaluate();
    aCircle->Render(GL_LINE_STRIP);

    aCircle->SetDegreesPerPoint(2.5);
    aCircle->SetRadius(120.0);
    aCircle->SetArcStartEnd(300.0, 60.0);
    aCircle->ResetVertices();
    aCircle->Evaluate();
    aCircle->Render(GL_LINE_STRIP);
	
    aCircle->SetRadius(130.0);
    aCircle->SetArcStartEnd(300.0, 60.0);
    aCircle->ResetVertices();
    aCircle->Evaluate();
    aCircle->Render(GL_LINE_STRIP);
	
    ///////////////////////////////////////////////////////////////////////////
    // Draw Layer 3: Compass Markings
    ///////////////////////////////////////////////////////////////////////////
	
    // Compass markings

    glColor3ub(255, 255, 255);
    glLineWidth(1.5);
    float heading_offset = fmod(aircraftHeading, compass_interval);

    static float vertices1[2*10];
    unsigned int vertexIdx = 0;
    for (int i = -30; i <= (30 + compass_interval); i += compass_interval)
      {
	float angle = (i - heading_offset) * DEG_TO_RAD;
	vertices1[2 * vertexIdx]       = CENTER_X + 120.0 * sinf(angle); 
	vertices1[2 * vertexIdx++ + 1] = CENTER_Y + 120.0 * cosf(angle);
	vertices1[2 * vertexIdx]       = CENTER_X + 130.0 * sinf(angle); 
	vertices1[2 * vertexIdx++ + 1] = CENTER_Y + 130.0 * cosf(angle);
      }
    glVertexPointer(2, GL_FLOAT, 0, &vertices1);
    glDrawArrays(GL_LINES, 0, 10);
	
    ///////////////////////////////////////////////////////////////////////////
    // Draw Layer 4: the Point of Interest marker (Navaids, Airports)
    ///////////////////////////////////////////////////////////////////////////

    // Rotate graphics context about the heading
    glPushMatrix();
    glTranslatef(CENTER_X, CENTER_Y, 0.0);
    glRotatef(aircraftHeading, 0, 0, 1);

    PlotCourse();
		
    // Naviads (blue)
    glColor3f(0.0, 0.0, 1.0);
    PlotGeoObjs(NavDatabase::getInstance()->GetNavaidHash()->GetListAtLatLon(aircraftLat, aircraftLon));
		
    // Airports (red)
    glColor3f(1.0, 0.0, 0.0);
    PlotGeoObjs(NavDatabase::getInstance()->GetAirportHash()->GetListAtLatLon(aircraftLat, aircraftLon));
		
    PlotWaypoints();
    glPopMatrix();
	
    ///////////////////////////////////////////////////////////////////////////
    // Draw Layer 5: Textual data, zoom buttons, aircraft icon, wind est.
    ///////////////////////////////////////////////////////////////////////////
	
    // Black background
    glColor4f(0.0, 0.0, 0.0, 0.8); // 80% alpha
    static const float vertices2[] = {
      // behind zoom buttons
      0.0, OVERLAY_Y,
      0.0, OVERLAY_Y + 20,
      10.5, OVERLAY_Y + 20,
      10.5, OVERLAY_Y,
      // behind bottom part
      0.0, 0.0,
      0.0, OVERLAY_Y,
      m_PhysicalSize.first, OVERLAY_Y,
      m_PhysicalSize.first, 0.0
    };
    glVertexPointer(2, GL_FLOAT, 0, &vertices2);
    glDrawArrays(GL_QUADS, 0, 8);

    // Lines dividing up the space in the gauge
    glColor3f(0.7, 0.7, 0.6);
    glLineWidth(1.0);
    static const float vertices3[] = {
      // lines around the zoom buttons
      0.0,  OVERLAY_Y + 10,
      10.5, OVERLAY_Y + 10,
      10.5, OVERLAY_Y,
      10.5, OVERLAY_Y + 20.1f,
      0.0,  OVERLAY_Y + 20.1f,
      10.5, OVERLAY_Y + 20.1f,
      10.5, OVERLAY_Y,
      10.5, OVERLAY_Y + 20,
      // line along top edge of overlay
      0.0, OVERLAY_Y,
      m_PhysicalSize.first, OVERLAY_Y
    };
    glVertexPointer(2, GL_FLOAT, 0, &vertices3);
    glDrawArrays(GL_LINES, 0, 12);

    // Zoom +/- buttons
    glLineWidth(2.0);
    glColor3f(1.0, 1.0, 1.0);
    static float vertices4[] = {
      // Plus symbol
      2.5, OVERLAY_Y+15.0f,
      7.5, OVERLAY_Y+15.0f,
      5.0, OVERLAY_Y+12.5f,
      5.0, OVERLAY_Y+17.5f,
      // Minus symbol
      2.5, OVERLAY_Y+5.0f,
      7.5, OVERLAY_Y+5.0f
    };
    glVertexPointer(2, GL_FLOAT, 0, &vertices4);
    glDrawArrays(GL_LINES, 0, 6);

    // Ground speed and track text
    char buffer[20];
    FontManager::getInstance()->SetSize(m_Font, 5.0, 5.0);
    sprintf(buffer, "TRACK %.0f", Globals::data_source->GetAirframe()->GetTrue_Heading() );
    FontManager::getInstance()->Print(2.0, 12.5, &buffer[0], m_Font);
    sprintf(buffer, "GS %.0f", Globals::data_source->GetAirframe()->GetGround_Speed_MS() );
    FontManager::getInstance()->Print(2.0, 2.5, &buffer[0], m_Font);

    // Scale text
    sprintf(buffer, "Scale: %.1f nm", m_SizeNM / (180.0 / 40.0));
    FontManager::getInstance()->SetSize(m_Font, 3.0, 3.0);
    FontManager::getInstance()->Print(5.0, OVERLAY_Y+175.0, &buffer[0], m_Font);

    // Wind speed/direction indicator
    PlotWindSpeedDirection();

    // Aircraft symbol
    glColor3ub(255,255,255);
    glLineWidth(2.0);
    const float width = 1.0;
    static float vertices5[] = {
      CENTER_X-width, CENTER_Y-6,
      CENTER_X-width, CENTER_Y+6,
      CENTER_X+width, CENTER_Y-6,
      CENTER_X+width, CENTER_Y+6,
      CENTER_X-4,     CENTER_Y-6,
      CENTER_X-width, CENTER_Y-6,
      CENTER_X-8,     CENTER_Y,
      CENTER_X-width, CENTER_Y,
      CENTER_X+4,     CENTER_Y-6,
      CENTER_X+width, CENTER_Y-6,
      CENTER_X+8,     CENTER_Y,
      CENTER_X+width, CENTER_Y
    };
    glVertexPointer(2, GL_FLOAT, 0, &vertices5);
    glDrawArrays(GL_LINES, 0, 12);
	
    // Divider between the PFD and the Nav Display
    glLineWidth(2.0);
    glColor3ub(0, 190, 190); // cyan
    static const float vertices6[] = {0.0,m_PhysicalSize.second,   0.0,0.0};
    glVertexPointer(2, GL_FLOAT, 0, &vertices6);
    glDrawArrays(GL_LINES, 0, 2);
  }

  /** Mouse event handler for zoom in/out buttons. */
  void NavDisplay::OnMouseDown(int button, float physicalX, float physicalY)
  {
    if ((physicalX <= 10.0)&&(physicalY>OVERLAY_Y)&&(physicalY<(OVERLAY_Y+10.0)))
      {
	m_SizeNM *= 2.0;
      }
    else if ((physicalX <= 10.0)&&(physicalY>(OVERLAY_Y+10.0))&&(physicalY<(OVERLAY_Y+20.0)))
      {
	m_SizeNM /= 2.0;
      }
  }

  void NavDisplay::PlotWindSpeedDirection()
  {
    // Get the data
    //	float windSpeed = Globals::data_source->GetAirframe()->GetWind_Speed();
    float windDirection = Globals::data_source->GetAirframe()->GetWind_Direction();
	
    glPushMatrix();
    glTranslatef(170.0, OVERLAY_Y+10.0, 0.0);
    // Draw the text
    // FIXME

    // Draw the Arrow
    glRotatef(windDirection, 0, 0, 1);

    glLineWidth(1.5);
    glColor3f(0.0, 1.0, 1.0); // sky blue
    static const float vertices[] = {0.0,4.0,   0.0,-4.0,   -2.0,2.0,   0.0,4.0,   2.0,2.0,   0.0,4.0};
    glVertexPointer(2, GL_FLOAT, 0, &vertices);
    glDrawArrays(GL_LINES, 0, 6);
    glPopMatrix();
  }

  void NavDisplay::PlotWaypoints()
  {
    // Get the waypoint list
    WaypointList *waypointList = NavDatabase::getInstance()->GetWaypointList();

    WaypointList::iterator iter;
    for (iter = waypointList->begin(); iter != waypointList->end(); ++iter)
      {
	// FIXME plot the waypoints and planned course
      }
  }

  void NavDisplay::PlotCourse()
  {
#if 0
    // Get the vector of CoursePoints
    FlightCourse *course = NavDatabase::getInstance()->GetFlightCourse();
    FlightCourse::iterator iter;	
    float xPos, yPos, lat, lon, northing, easting;

    glColor3f(0.5, 0.0, 0.0); // 50% red
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);

    for (iter = course->begin(); iter != course->end(); ++iter) {
      (*iter).GetCoords(lat, lon);
      GeographicObject::LatLonToMercator(lat, lon, northing, easting);
      PointToPixelCoord(northing, easting, xPos, yPos);
      glVertex2f(xPos, yPos);
    }
    
    glEnd();
#endif
  }

  void NavDisplay::PlotGeoObjs(std::list<GeographicObject*>& geoList)
  {
    std::list<GeographicObject*>::iterator iter;
    float objNorthing, objEasting;

    for (iter = geoList.begin(); iter != geoList.end(); ++iter)
      {
	// Get mercator coordinates in meters
	(*iter)->GetMercatorMeters(objNorthing, objEasting);

	// Compute position relative to gauge center
	float xPos, yPos;
	PointToPixelCoord(objNorthing, objEasting, xPos, yPos);

	// Only draw the navaid if it's visible within the rendering area
	if (PixelCoordIsVisible(xPos, yPos))
	  {
	    // We're going to be clever and "derotate" each label
	    // by the heading, so that everything appears upright despite
	    // the global rotation. This makes all of the labels appear at
	    // 0,0 in the local coordinate system
	    glPushMatrix();
	    glTranslatef(xPos, yPos, 0.0);
	    glRotatef(-1.0 * aircraftHeading, 0, 0, 1);

	    static const float vertices[] = {-1.0,0.0,   0.0,1.0,   1.0,0.0,   0.0,-1.0};
	    glVertexPointer(2, GL_FLOAT, 0, &vertices);
	    glDrawArrays(GL_POLYGON, 0, 4);

	    FontManager::getInstance()->SetSize(m_Font, 4.0, 4.0);
	    FontManager::getInstance()->Print(1.5, -2.0, (*iter)->GetIdentification().c_str(), m_Font);
	    glPopMatrix();
	  }
      }
  }

  // FIXME this whole function is a temporary hack/placeholder for testing RasterMapManager.
  void NavDisplay::PlotMap()
  {
    unsigned int x, y; float fx, fy;
    unsigned int z = 13;
	
    RasterMapManager::getInstance()->GetTileCoordsForLatLon(x, y, fx, fy, 
							    Globals::data_source->GetAirframe()->GetLatitude(),
							    Globals::data_source->GetAirframe()->GetLongitude(),
							    z);
	
    //----------------------------------
    // This is a Demo Mode hack...
    if (x < 6000) return;
    //----------------------------------

    static bool status[49];
    if (!m_TilesInitted)
      {
	int ident = 0;
	glGenTextures(49, &m_TileTextures[0]);
	for (int dx = -3; dx <= 3; dx++)
	  {
	    for (int dy = -3; dy <= 3; dy++)
	      {
		RasterMapTile *tile = RasterMapManager::getInstance()->GetTile(z, x+dx, y+dy);
		if (tile != NULL)
		  {
		    glBindTexture(GL_TEXTURE_2D, m_TileTextures[ident]);
					
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tile->Width(), tile->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, tile->Image());
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    delete tile;
					
		    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		    glEnableClientState(GL_VERTEX_ARRAY);
		    status[ident] = true;
		  }
		else
		  status[ident] = false;
		ident++;
	      }
	  }
	m_TilesInitted = true;
      }

    int ident = 0;
    for (int dx = -3; dx <= 3; dx++)
      {
	for (int dy = -3; dy <= 3; dy++)
	  {
	    if (status[ident])
	      {
		// Render tile
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(CENTER_X, CENTER_Y, 0);
		glRotatef(aircraftHeading, 0, 0, 1);
		glTranslatef((dx*256 + fx - 128)/3.2, (-dy*256 - fy - 128)/3.2, 0);
		glColor4ub(200, 200, 200, 255);
				
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_TileTextures[ident]);
					
		static const float texCoords[] = {0,1,   1,1,   0,0,   1,0};
		glTexCoordPointer(2, GL_FLOAT, 0, &texCoords);
				
		static const float vertices[] = {-40,-40,   40,-40,   -40,40,   40,40};
		glVertexPointer(2, GL_FLOAT, 0, &vertices);
				
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	      }
	    ident++;
	  }
      }
  }

  void NavDisplay::PointToPixelCoord(float objNorthing, float objEasting, float &xPos, float &yPos)
  {
    // Compute position relative to gauge center
    yPos = (objNorthing / METER_PER_NM - mercatorNorthing) * 180.0 / m_SizeNM;
    xPos = (objEasting / METER_PER_NM - mercatorEasting) * 180.0 / m_SizeNM;
  }

  bool NavDisplay::PixelCoordIsVisible(float xPos, float yPos)
  {
    return (
	    (fabs(xPos) < 90.0) && (yPos < (m_PhysicalSize.second - CENTER_Y)) 
	    && (yPos > (-1 * CENTER_Y)) && (sqrt(yPos*yPos + xPos*xPos) < 120)
	    // FIXME - doesn't work correctly
	    ) ? true : false;
  }

} // end namespace OpenGC

