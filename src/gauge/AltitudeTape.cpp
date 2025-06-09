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
#include <math.h>

#include "Globals.h"
#include "GaugeComponent.h"
#include "AltitudeTape.h"

namespace OpenGC
{

  AltitudeTape::AltitudeTape()
  {
    m_Font = Globals::font_manager->LoadDefaultFont();

    m_PhysicalPosition.first = 0;
    m_PhysicalPosition.second = 0;

    m_PhysicalSize.first = 24;
    m_PhysicalSize.second = 136;

    m_Scale.first = 1.0;
    m_Scale.second = 1.0;
  }

  AltitudeTape::~AltitudeTape()
  {

  }

  void AltitudeTape::Render()
  {
    // Call base class to setup viewport and projection
    GaugeComponent::Render();

    // Get the altitude
    long int alt = (long int) Globals::data_source->GetAirframe()->GetAltitude_MSL_Feet();

    // Save matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // Draw in gray-blue
    glColor3ub(51,51,76);

    // Draw the background rectangle
    const float vertices[] = {
      0.0, 0.0,
      0.0, m_PhysicalSize.second,
      m_PhysicalSize.first, m_PhysicalSize.second,
      m_PhysicalSize.first, 0.0,
      0.0, 0.0
    };

    glVertexPointer(2, GL_FLOAT, 0, &vertices);
    glDrawArrays(GL_POLYGON, 0, 5);	
	
    // Tick marks are spaced every 100 ft. vertically
    // The tick spacing represents how far apart they are in physical
    // units
    const float tickSpacing = 17.0, tickWidth = 3.7, fontHeight = 4, fontWidth = 3.5, fontIndent = 4.5;
    const int numTicks = m_PhysicalSize.second / tickSpacing;

    Globals::font_manager->SetSize(m_Font, fontHeight, fontWidth);

    int nextHighestAlt = (alt/100)*100;

    if (nextHighestAlt < alt)
      nextHighestAlt += 100;

    // The vertical offset is how high in physical units the next highest 100's
    // altitude is above the arrow
    float vertOffset = ((float) nextHighestAlt - (float) alt) / 100 * tickSpacing;

    glColor3ub(255,255,255);
    glLineWidth(2.0);

    // Draw ticks up from the center
    for (int i = -numTicks/2; i <= numTicks/2; i++)
      {
	int tickAlt = nextHighestAlt + i * 100;
	float tickLocation = (m_PhysicalSize.second/2) + i * tickSpacing + vertOffset;
	float texty = tickLocation - fontHeight / 2;
		
	if (tickAlt >= 0)
	  {
	    const float vertices[] = {0, tickLocation, tickWidth, tickLocation};
	    glVertexPointer(2, GL_FLOAT, 0, &vertices);
	    glDrawArrays(GL_LINES, 0, 2);
			
	    if ((tickAlt % 200) == 0)
	      {
		Globals::font_manager->SetRightAligned(m_Font, true);
		static char buffer[16];
		sprintf( buffer, "%d", tickAlt);
		Globals::font_manager->Print(fontIndent + fontWidth * 5, texty, &buffer[0], m_Font);
		Globals::font_manager->SetRightAligned(m_Font, false);
	      }
	  }
      }

    glPopMatrix();
  }

} // end namespace OpenGC
