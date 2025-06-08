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

#include "RenderObject.h"
#include "Debug.h"

namespace OpenGC
{

  RenderObject::RenderObject()
  {
    // Initialize with safe default parameters

    m_UnitsPerPixel = 1.0;

    m_PhysicalPosition.first = 0;
    m_PhysicalPosition.second = 0;

    m_PhysicalSize.first = 0;
    m_PhysicalSize.second = 0;

    m_Scale.first = 1.0;
    m_Scale.second = 1.0;
  }

  RenderObject::~RenderObject()
  {

  }

  void RenderObject::SetScale(double xScale, double yScale)
  {
    // Set gauge scaling factors
    // Must be a double greater than 0

    if(xScale > 0)
      m_Scale.first = xScale;

    if(yScale > 0)
      m_Scale.second = yScale;
  }

  void RenderObject::SetPosition(double xPos, double yPos)
  {
    m_PhysicalPosition.first = xPos;
    m_PhysicalPosition.second = yPos;
  }

  void RenderObject::SetUnitsPerPixel(double unitsPerPixel)
  {
    m_UnitsPerPixel = unitsPerPixel;
  }

  // Called by framework when a mouse click occurs
  void RenderObject::HandleMouseButton(int button, int state, int x, int y)
  {
    if(this->ClickTest(button, state, x, y))
      {
	// Convert the click to an x/y position in render object physical coordinates
	double physX, physY;
	
	physX = (((double) x - (double) m_PixelPosition.first)/(double)m_PixelSize.first)*m_PhysicalSize.first;
	physY = (((double) y - (double) m_PixelPosition.second)/(double)m_PixelSize.second)*m_PhysicalSize.second;

	if(state==0)
	  this->OnMouseDown(button, physX, physY);
	else
	  this->OnMouseUp(button, physX, physY);
      }
  }

  // Called when a mouse "down" event occurs
  void RenderObject::OnMouseDown(int button, double physicalX, double physicalY)
  {
    // The default version of this doesn't do anything
    // Overload to provide specific functionality
  }

  // Called when a mouse "up" event occurs
  void RenderObject::OnMouseUp(int button, double physicalX, double physicalY)
  {
    // The default version of this doesn't do anything
    // Overload to provide specific functionality
  }

  // Called when keyboard event occurs
  void RenderObject::OnKeyboard(int keycode, int modifiers)
  {
    // The default version of this doesn't do anything
    // Overload to provide specific functionality
  }

} // end namespace OpenGC
