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

/**
 * RenderObjects are the base class for any class which draws in
 * RenderWindow and defines a client rendering space. Currently
 * this includes Gauges and GaugeComponents.
 */

#pragma once

#include <utility>
#include "GLHeaders.h"

namespace OpenGC {
  class RenderObject {
  public:
    RenderObject();
    virtual ~RenderObject();		
    virtual void SetUnitsPerPixel(const float unitsPerPixel);
    virtual void SetScale(const float xScale, const float yScale);
    void SetPosition(const float xPos, const float yPos);
    void SetParentRenderObject(RenderObject* pObject);
    std::pair<float, float> GetPhysicalPosition(void);
    
    /** Called by framework when a mouse click occurs (x/y in pixel coordinates) */
    void HandleMouseButton(const int button, const int state, const int x, const int y);
    /** Called when a mouse "down" event occurs (x/y in physical coordinates) */
    virtual void OnMouseDown(const int button, const float physicalX, const float physicalY);
    /** Called when a mouse "up" event occurs (x/y in physical coordinates) */
    virtual void OnMouseUp(const int button, const float physicalX, const float physicalY);	
    /** Called when a key is pressed on the keyboard and OpenGC has focus */
    virtual void OnKeyboard(const int keycode, const int modifiers);

    /** Return true if the click is inside the gauge
	If true, tests gauge components prior to returning */
    virtual bool ClickTest(const int button, const int state, const int x, const int y) = 0;
    virtual void Render(void) = 0;

  protected:
    /** Set by the render window to describe pixel-realspace conversions */
    float m_UnitsPerPixel;
    /** Parent object, for cascading position information */
    RenderObject *m_pParentRenderObject;
    /** 1.0=normal scale, 0.5=half, 2=float, etc. */
    std::pair<float, float> m_Scale;
    /** Position in mm in the render window */
    std::pair<float, float> m_PhysicalPosition;
    /** Placement in render window in pixel units */
    std::pair<unsigned int, unsigned int> m_PixelPosition;
    /** Size in mm, defined by derived classes, NOT initialized */
    std::pair<float, float> m_PhysicalSize;
    /** Size in render window in pixel units */
    std::pair<unsigned int, unsigned int> m_PixelSize;
  };
}
