/*=========================================================================

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
#include "gl_headers.h"
#include "PFDOverlay.h"

namespace OpenGC
{

  PFDOverlay::PFDOverlay()
  {
    m_Font = FontManager::getInstance()->LoadDefaultFont();
    this->SetOpaque(false); // this is overlaid so we don't want an opaque background
	
    m_PhysicalSize.first = 200;
    m_PhysicalSize.second = 190;

    m_Scale.first = 1.0;
    m_Scale.second = 1.0;
  }

  PFDOverlay::~PFDOverlay()
  {

  }
	
  void PFDOverlay::Render()
  {
    GaugeComponent::Render();
		
    AirframeDataContainer *data = DataSourceManager::getInstance()->getDataSource()->GetAirframe();
	
    char buffer[16];

    // Draw heading indicator track as text
    glColor3d(255, 255, 255); // white
    sprintf(buffer, "%3d", (int) data->GetTrue_Heading());
    FontManager::getInstance()->SetSize(m_Font, 4.0, 4.0 );
    FontManager::getInstance()->Print(75, 7, "GPS", m_Font); 
    FontManager::getInstance()->SetRightAligned(m_Font, true);
    FontManager::getInstance()->Print(100, 7, &buffer[0], m_Font); 
    FontManager::getInstance()->SetRightAligned(m_Font, false);
  }

} // end namespace OpenGC
