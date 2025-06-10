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

#include "data_source_manager.h"
#include "GLHeaders.h"
#include <stdio.h>
#include <math.h>
#include "GaugeComponent.h"
#include "CircleEvaluator.h"
#include "HeadingIndicator.h"

namespace OpenGC
{

  HeadingIndicator::HeadingIndicator()
  {
    m_Font = FontManager::getInstance()->LoadDefaultFont();

    m_PhysicalPosition.first = 0;
    m_PhysicalPosition.second = 0;

    m_PhysicalSize.first = 130;
    m_PhysicalSize.second = 45;

    m_Scale.first = 1.0;
    m_Scale.second = 1.0;
  }

  HeadingIndicator::~HeadingIndicator()
  {

  }

  void HeadingIndicator::Render()
  {
    // Call base class to setup viewport and projection
    GaugeComponent::Render();

    /**
     * A few general notes:
     *
     * This is a hard gauge to get sized correctly, so we set up a bunch
     * of symbolic constants for reference rather than hard coding everything.
     * 
     * Also, the implementation of the 777 heading indicator is a little curious
     * because although the gauge is circular in the real world, a given number
     * of degrees on the displayed circle do not represent an equivalent
     * difference in heading. indicatorDegreesPerTrueDegrees is the conversion
     * factor between "gauge" degrees and "display" degrees.
     */

    const float centerX = 60;
    const float centerY = -35;
    const float radius = 70.0;
    const float indicatorDegreesPerTrueDegrees = 1.5;

    const float bigFontSize = 5.0;
    const float littleFontSize = 3.5;

    char buffer[32];

    glTranslated(centerX, centerY, 0);

    // Draw in gray
    glColor3ub(51,51,76);
    glLineWidth( 1.5 );

    // Set up the circle
    CircleEvaluator *aCircle = CircleEvaluator::getInstance();
    aCircle->SetRadius(radius);
    aCircle->SetArcStartEnd(300,60);
    aCircle->SetDegreesPerPoint(2.5);
    aCircle->SetOrigin(0.0, 0.0);

    // Draw the circle
    aCircle->ResetVertices();
    aCircle->AddVertex(0,0);
    aCircle->Evaluate();
    aCircle->Render(GL_TRIANGLE_FAN);
    glLineWidth(1.0);
    aCircle->Render(GL_LINE_STRIP); // and again for antialiasing

    // Draw the center detent
    glColor3ub(255,255,255);
    const float vertices[] = {0.0f,radius, -2.8f,radius+3.25, 2.8f,radius+3.25};
    glVertexPointer(2, GL_FLOAT, 0, &vertices);
    glDrawArrays(GL_LINE_LOOP, 0, 3);

    float heading = DataSourceManager::getInstance()->getDataSource()->GetAirframe()->GetTrue_Heading();

    // -----------Draw the detents around the circle-----------------------------
    // Figure out the nearest heading that's a multiple of 10
    float nearestTen = (float)( (int)heading - (int)heading % 10);

    // Derotate by this offset
    glRotated((heading - nearestTen) * indicatorDegreesPerTrueDegrees,0,0,1);

    // Now derotate by 40 "virtual" degrees
    glRotated(40*indicatorDegreesPerTrueDegrees,0,0,1);


    // Now draw lines 5 virtual degrees apart around the perimeter of the circle
    for(int i = (int)nearestTen - 40; i<=nearestTen+40; i+=5)
      {
	// The length of the tickmarks on the compass rose
	float tickLength;

	// Make sure the display heading is between 0 and 360
	int displayHeading = (i+720)%360;

	// If the heading is a multiple of ten, it gets a long tick
	if(displayHeading%10==0)
	  {
	    tickLength = 4;

	    // The x-position of the font (depends on the number of characters in the heading)
	    float fontx;

	    // Convert the display heading to a string
	    //_itoa( displayHeading/10, buffer, 10);
	    sprintf( buffer, "%d", displayHeading/10 );
	    if(displayHeading%30==0)
	      {
		if(displayHeading>=100)
		  fontx = -bigFontSize;
		else
		  fontx = -bigFontSize/2;

		FontManager::getInstance()->SetSize(m_Font, bigFontSize, bigFontSize);
		FontManager::getInstance()->Print(fontx, radius-tickLength-bigFontSize, &buffer[0], m_Font );
	      }
	    else
	      {
		if(displayHeading>=100)
		  fontx = -littleFontSize;
		else
		  fontx = -littleFontSize/2;

		FontManager::getInstance()->SetSize(m_Font, littleFontSize, littleFontSize);
		FontManager::getInstance()->Print(fontx, radius-tickLength-littleFontSize, &buffer[0], m_Font );
	      }

	  }
	else // Otherwise it gets a short tick
	  tickLength = 2.5;

	const float vertices[] = {0,radius,  0,radius-tickLength};
	glVertexPointer(2, GL_FLOAT, 0, &vertices);
	glDrawArrays(GL_LINES, 0, 2);

	glRotated(5.0 * indicatorDegreesPerTrueDegrees,0,0,-1);
      }
  }

} // end namespace OpenGC

