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
 * Boeing 777 vertical speed indicator
 */

#ifndef VSI_h
#define VSI_h

#include "GaugeComponent.h"

namespace OpenGC
{

  class VSI : public GaugeComponent  
  {
  public:

    VSI();
    virtual ~VSI();

    /** Overloaded render function */
    void Render();

  protected:

    /** Routine to convert an altitude to needle position */
    float VSpeedToNeedle(float vspd);

    /** The font number provided to us by the font manager */
    int m_Font;

    /** Centered position of needle in physical coordinates */
    float m_NeedleCenter;

    /** Max positive or negative deflection of needle in physical coordinates */
    float m_MaxNeedleDeflection;

  };

} // end namespace OpenGC

#endif
