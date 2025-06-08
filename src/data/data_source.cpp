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

#include "data_source.h"

OpenGC::DataSource::DataSource(void) {
    m_airframe = new AirframeDataContainer();
}

OpenGC::DataSource::~DataSource() {
    if (nullptr != m_airframe) {
	delete m_airframe;
    }
}

OpenGC::AirframeDataContainer* OpenGC::DataSource::GetAirframe(void) const {
    return m_airframe;
}

bool OpenGC::DataSource::OnIdle(void) {
    // The default version does nothing
    return false;
}

bool OpenGC::DataSource::Open(void) {
    // The default version returns false, which doesn't necessarily mean anything
    return false;
}
