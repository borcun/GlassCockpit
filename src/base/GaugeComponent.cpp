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
#include "GLHeaders.h"

#include "GaugeComponent.h"

namespace OpenGC
{

  GaugeComponent::GaugeComponent()
    :m_Opaque(true)
  {

  }

  GaugeComponent::~GaugeComponent()
  {

  }

  void GaugeComponent::Render()
  {
    // Overload this function in derived classes to render
    // the guage component
    std::pair<double, double> parentPhysicalPosition = m_pParentRenderObject->GetPhysicalPosition();

    // The location in pixels is calculated based on the size of the
    // gauge component and the offset of the parent guage
    m_PixelPosition.first = (int) ( (m_PhysicalPosition.first * m_Scale.first + parentPhysicalPosition.first ) / m_UnitsPerPixel);
    m_PixelPosition.second = (int) ( (m_PhysicalPosition.second * m_Scale.second + parentPhysicalPosition.second ) / m_UnitsPerPixel);

    // The size in pixels of the gauge is the physical size / mm per pixel
    m_PixelSize.first = (int) ( m_PhysicalSize.first / m_UnitsPerPixel * m_Scale.first);
    m_PixelSize.second = (int) ( m_PhysicalSize.second / m_UnitsPerPixel * m_Scale.second);

    // The viewport is established in order to clip things
    // outside the bounds of the GaugeComponent
    glViewport(m_PixelPosition.first, m_PixelPosition.second, m_PixelSize.first, m_PixelSize.second);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Define the projection so that we're drawing in "real" space
    glOrtho(0, m_Scale.first * m_PhysicalSize.first, 0, m_Scale.second * m_PhysicalSize.second, -1, 1);

    // Prepare the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(m_Scale.first, m_Scale.second, 1.0f);
  }

  bool GaugeComponent::ClickTest(int button, int state, int x, int y)
  {
    if( (x >= (int)m_PixelPosition.first)&&(x <= (int)(m_PixelPosition.first + m_PixelSize.first))
	&&(y >= (int)m_PixelPosition.second)&&(y <= (int)(m_PixelPosition.second + m_PixelSize.second)) )
      {
	// Click is inside the GaugeComponent
	return true;
      }
    else
      {
	// Click is NOT inside the GaugeComponent
	return false;
      }
  }

} // end namespace OpenGC
