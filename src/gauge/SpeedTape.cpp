/*=========================================================================

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

  =========================================================================*/

#include <stdio.h>

#include "data_source_manager.h"
#include "GaugeComponent.h"
#include "SpeedTape.h"

namespace OpenGC
{

  SpeedTape::SpeedTape()
  {
    m_Font = FontManager::getInstance()->LoadDefaultFont();

    m_PhysicalPosition.first = 0;
    m_PhysicalPosition.second = 0;

    m_PhysicalSize.first = 34; // make the clip region larger to handle speed bug
    m_PhysicalSize.second = 136;
    indent_x = m_PhysicalSize.first - 11;

    m_Scale.first = 1.0;
    m_Scale.second = 1.0;
  }

  SpeedTape::~SpeedTape()
  {

  }

  void SpeedTape::Render()
  {
    // Call base class to setup viewport and projection
    GaugeComponent::Render();

    // Speed for floating point calculations
    float airspeed = DataSourceManager::getInstance()->getDataSource()->GetAirframe()->GetAirspeed_KT();

    // The speed tape doesn't show speeds greater than 1999 knots
    if(airspeed > 1999.0)
      airspeed = 1999.0;

    // Save matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // Draw in gray-blue
    glColor3ub(51,51,76);

    // Draw the background rectangle
    static const float vertices[] = {
      0.0, 0.0,
      0.0, m_PhysicalSize.second,
      indent_x, m_PhysicalSize.second,
      indent_x, 0.0,
      0.0, 0.0
    };
    glVertexPointer(2, GL_FLOAT, 0, &vertices);
    glDrawArrays(GL_POLYGON, 0, 5);

    // Tick marks are space every 10 kph vertically
    // The tick spacing represents how far apart they are in physical
    // units
    const float tickSpacing = 11.3, tickWidth = 3.7, fontHeight = 5, fontWidth = 4.1, fontIndent = 5;
    const int numTicks = m_PhysicalSize.second / tickSpacing;

    FontManager::getInstance()->SetSize(m_Font, fontHeight, fontWidth);

    float nextHighestAirspeed = (((int)airspeed) / 10) * 10;
    if (nextHighestAirspeed < airspeed)
      nextHighestAirspeed += 10;

    // The vertical offset is how high in physical units the next highest 10's
    // airspeed is above the arrow. For airspeeds divisible by 10, this is 0. I.e. 120, 130
    // etc. are all aligned with the arrow
    float vertOffset = (nextHighestAirspeed - airspeed) * tickSpacing / 10.f;

    glColor3ub(255,255,255);
    glLineWidth(2.0);
	
    // Draw ticks up from the center
    for (int i = -numTicks/2; i <= numTicks/2; i++)
      {
	int tickSpeed = nextHighestAirspeed + i * 10;
	float tickLocation = (m_PhysicalSize.second/2) + i * tickSpacing + vertOffset;
	float texty = tickLocation - fontHeight / 2;
		
	if (tickSpeed >= 0)
	  {
	    const float vertices[] = {indent_x - tickWidth, tickLocation, indent_x, tickLocation};
	    glVertexPointer(2, GL_FLOAT, 0, &vertices);
	    glDrawArrays(GL_LINES, 0, 2);
			
	    if ((tickSpeed % 20) == 0)
	      {
		FontManager::getInstance()->SetRightAligned(m_Font, true);
		static char buffer[16];
		sprintf( buffer, "%d", tickSpeed);
		FontManager::getInstance()->Print(fontIndent + fontWidth*3, texty, &buffer[0], m_Font);
		FontManager::getInstance()->SetRightAligned(m_Font, false);
	      }
	  }
      }
    glPopMatrix();
  }

} // end namespace OpenGC
