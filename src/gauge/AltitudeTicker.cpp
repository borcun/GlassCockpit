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
#include "AltitudeTicker.h"

namespace OpenGC
{

  AltitudeTicker::AltitudeTicker()
  {
    m_Font = FontManager::getInstance()->LoadDefaultFont();

    m_PhysicalPosition.first = 0;
    m_PhysicalPosition.second = 0;

    m_PhysicalSize.first = 28;
    m_PhysicalSize.second = 18;

    m_Scale.first = 1.0;
    m_Scale.second = 1.0;
  }

  AltitudeTicker::~AltitudeTicker()
  {

  }

  void AltitudeTicker::Render()
  {
    // Call base class to setup viewport and projection
    GaugeComponent::Render();

    // Draw black background
    glColor3ub(0,0,0);
    // Rectangular part
    static const float vertices[] = {3.5,0.0,   28.0,0.0,   28.0,18.0,   3.5,18.0};
    glVertexPointer(2, GL_FLOAT, 0, &vertices);
    glDrawArrays(GL_QUADS, 0, 4);
    // Triangular part
    static const float vertices1[] = {0.0,9.0,   3.5,6.0,   3.5,12.0};
    glVertexPointer(2, GL_FLOAT, 0, &vertices1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
	
    // White border around background
    glColor3ub(255,255,255);
    glLineWidth(2);
    static const float vertices2[] = {3.5,18.0,   28.0,18.0,   28.0,0.0,  3.5,0.0};
    glVertexPointer(2, GL_FLOAT, 0, &vertices2);
    glDrawArrays(GL_LINE_STRIP, 0, 4);
    glLineWidth(1.5);
    static const float vertices3[] = {3.5,0.0,   3.5,6.0,   0.0,9.0,   3.5,12.0,   3.5,18.0};
    glVertexPointer(2, GL_FLOAT, 0, &vertices3);
    glDrawArrays(GL_LINE_STRIP, 0, 5);

    // y position of the text (for easy changes)
    const double bigFontHeight = 8.0;
    const double littleFontHeight = 6.5;
    double texty = m_PhysicalSize.second / 2 - bigFontHeight / 2;

    FontManager::getInstance()->SetSize(m_Font, 6.0, bigFontHeight);

    // Get the data
    float alt_f = DataSourceManager::getInstance()->getDataSource()->GetAirframe()->GetAltitude_MSL_Feet();
    long int alt = (long int)alt_f;

    // Draw text in white
    glColor3ub(255,255,255);

    // 10000's
    char buffer[4];
    if(alt >= 10000)
      {
	sprintf(buffer, "%li", alt/10000);
	FontManager::getInstance()->Print(5.0, texty, buffer, m_Font);
	alt_f = alt_f - 10000*(int)(alt/10000);
	alt = alt-10000*(int)(alt/10000);
      }
    else
      {
	// Draw a cross-hatched box
	glColor3ub(0,179,0); // green
	glLineWidth(2.0);
	static const float vertices[] = {5.0,7.6666, 6.0,5.0, 5.0,10.3333, 7.0,5.0,
					 5.0,13.0, 8.0,5.0, 6.0,13.0, 8.0,7.6666, 7.0,13.0, 8.0,10.3333};
	glVertexPointer(2, GL_FLOAT, 0, &vertices);
	glDrawArrays(GL_LINES, 0, 10);
	glColor3ub(255,255,255);
      }

    // 1000's
    sprintf(buffer, "%li", alt/1000);
    FontManager::getInstance()->Print(9.5, texty, &buffer[0], m_Font);
    alt_f = alt_f - 1000*(int)(alt/1000);
    alt = alt-1000*(int)(alt/1000);

    // The 100's, 10's, and 1's are drawn in a smaller size
    FontManager::getInstance()->SetSize(m_Font, 5.0, littleFontHeight);
    texty = m_PhysicalSize.second / 2 - littleFontHeight / 2;

    // 100's
    sprintf(buffer, "%li", alt/100);
    FontManager::getInstance()->Print(15.0, texty, &buffer[0], m_Font);
    alt_f = alt_f - 100*(int)(alt/100);
    alt = alt-100*(int)(alt/100);

    // The 10's and 1's position (which is always 0) scroll based on altitude
    // We use three digits for the tens position, high, middle, and low
    // Note that the tens digit is always a multiple of 2
    int middle_ten = alt / 10;

    bool roundupnine = false;

    switch(middle_ten)
      {
      case 1:
      case 3:
      case 5:
      case 7:
	middle_ten += 1;
	break;
      case 9:
	middle_ten = 0;
	roundupnine = true;
	break;
      }

    // Figure out the translation for the tens and ones position
    double vertTranslation;

    if (middle_ten != 0)
      vertTranslation = (middle_ten * 10 - alt_f) / 20 * littleFontHeight;
    else {
      if (roundupnine)
	vertTranslation = (100 - alt_f) / 20 * littleFontHeight;
      else
	vertTranslation = (0 - alt_f) / 20 * littleFontHeight;
    }
    glTranslated(0, vertTranslation, 0);

    // Now figure out the digits above and below
    int top2_ten = (middle_ten + 4) % 10;
    int top_ten = (middle_ten + 2) % 10;
    int bottom_ten = (middle_ten - 2 + 10) % 10;
    int bottom2_ten = (middle_ten - 4 + 10) % 10;

    // Display all of the digits
    sprintf(buffer, "%i", top2_ten);
    FontManager::getInstance()->Print(19.0, texty + 2 * (littleFontHeight + littleFontHeight/10), &buffer[0], m_Font);
    FontManager::getInstance()->Print(23.0, texty + 2 * (littleFontHeight + littleFontHeight/10), "0", m_Font);
	
    sprintf(buffer, "%i", top_ten);
    FontManager::getInstance()->Print(19.0, texty + littleFontHeight + littleFontHeight/10, &buffer[0], m_Font);
    FontManager::getInstance()->Print(23.0, texty + littleFontHeight + littleFontHeight/10, "0", m_Font);

    sprintf(buffer, "%i", middle_ten);
    FontManager::getInstance()->Print(19.0, texty, &buffer[0], m_Font);
    FontManager::getInstance()->Print(23.0, texty, "0", m_Font);

    sprintf(buffer, "%i", bottom_ten);
    FontManager::getInstance()->Print(19.0, texty - littleFontHeight - littleFontHeight/10, &buffer[0], m_Font);
    FontManager::getInstance()->Print(23.0, texty - littleFontHeight - littleFontHeight/10, "0", m_Font);
	
    sprintf(buffer, "%i", bottom2_ten);
    FontManager::getInstance()->Print(19.0, texty - 2 * (littleFontHeight + littleFontHeight/10), &buffer[0], m_Font);
    FontManager::getInstance()->Print(23.0, texty - 2 * (littleFontHeight + littleFontHeight/10), "0", m_Font);
  }

} // end namespace OpenGC
