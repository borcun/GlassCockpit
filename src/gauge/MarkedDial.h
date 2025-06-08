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

#ifndef MarkedDial_H
#define MarkedDial_H

#include "GaugeComponent.h"

namespace OpenGC
{

  typedef float (AirframeDataContainer::*AirframeMemFn)();

  class MarkedDial : public GaugeComponent  
  {
  public:

    MarkedDial();
    virtual ~MarkedDial();

    void Render();
    void SetDataSource(AirframeMemFn fn) {m_DataFn = fn; }
    void SetMinMax(double min, double max) {m_Min = min; m_Max = max; }
    void SetTickSpacing(double spacing) {m_TickSpacing = spacing; }
    void SetTickDivisor(double divisor) {m_TickDivisor = divisor; }

  protected:

    int m_Font;
    AirframeMemFn m_DataFn;
    double m_Min, m_Max, m_TickSpacing, m_TickDivisor;
  };

}

#endif
