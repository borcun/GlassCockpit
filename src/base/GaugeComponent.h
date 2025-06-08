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
 * GaugeComponents are the most "primitive" building block in the
 * OpenGC design scheme. Gauges are composed of a number of
 * GaugeComponents, each of which is capable of positioning and
 * drawing itself.
 *
 * By breaking a gauge into multiple GaugeComponents, recycling
 * of code is encouraged between different gauge designs.
 */

#ifndef GaugeComponent_h
#define GaugeComponent_h

#include "FontManager.h"
#include "data_source.h"
#include "OrderedPair.h"
#include "RenderObject.h"

namespace OpenGC
{

  class GaugeComponent: public RenderObject
  {
  public:
    GaugeComponent();
    virtual ~GaugeComponent();

    /** Render the gauge component */
    virtual void Render();

    /** Return true if the click is inside the gauge component */
    bool ClickTest(int button, int state, int x, int y);

    /** Set to true to have an opaque background */
    void SetOpaque(bool opaque) { m_Opaque = opaque; }

  private:
    bool m_Opaque;
  };

} // end namespace OpenGC

#endif

