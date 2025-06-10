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
#include "PrefManager.h"
#include "data_source.h"
#include "Gauge.h"
#include "Debug.h"

namespace OpenGC
{
  Gauge::Gauge() {
    m_NumGaugeComponents = 0;
    m_DrawGaugeOutline = false;

    m_Scale.second = 1.0;
    m_Scale.first = 1.0;

    m_PhysicalPosition.first = 0;
    m_PhysicalPosition.second = 0;

    m_PixelPosition.first = 0;
    m_PixelPosition.second = 0;

    m_PixelSize.first = 0;
    m_PixelSize.second = 0;
  }

  Gauge::~Gauge() {
    // If there are gauge components, delete them
    if( m_NumGaugeComponents!=0 ) {
      std::list<GaugeComponent*>::iterator it;
	
      for (it = m_GaugeComponentList.begin(); it != m_GaugeComponentList.end(); ++it) {
	delete *it;
      }
    }
  }

  void Gauge::InitFromXMLNode(XMLNode gaugeNode) {
    Check(gaugeNode.IsValid() && gaugeNode.GetName() == "Gauge");

    double scale = PrefManager::getInstance()->GetPrefD("DefaultGaugeScale");
    double zoom = PrefManager::getInstance()->GetPrefD("Zoom");
    double x, y; // temp variables
	
    // Set the units per pixel
    if (gaugeNode.HasChild("UnitsPerPixel"))
      {
	SetUnitsPerPixel(gaugeNode.GetChild("UnitsPerPixel").GetTextAsDouble());
      }
    else
      {
	SetUnitsPerPixel(PrefManager::getInstance()->GetPrefD("UnitsPerPixel"));
      }

    // Set the position
    if (gaugeNode.HasChild("Position"))
      {
	gaugeNode.GetChild("Position").GetTextAsCoord(x, y);
	SetPosition(x * zoom, y * zoom);
      }
    else
      {
	SetPosition(0.0, 0.0);
      }

    // Set the scale
    if (gaugeNode.HasChild("Scale")) {
      gaugeNode.GetChild("Scale").GetTextAsCoord(x, y);
      SetScale(x * zoom * scale, y * zoom * scale);
    }
    else
      {
	SetScale(zoom * scale, zoom * scale);
      }

    // Set the gauge outline
    if (gaugeNode.HasChild("Outline"))
      {
	SetGaugeOutline(gaugeNode.GetChild("Outline").GetTextAsBool());
      }
	
    CustomXMLInit(gaugeNode);
  }

  void Gauge::AddGaugeComponent(GaugeComponent *pComponent) {
    m_GaugeComponentList.push_back(pComponent);
    m_NumGaugeComponents++;
  }

  void Gauge::Render(void) {
    // Overload this function in derived classes to render
    // parts of the guage not defined by gauge components

    // BUT!!! you should always call the base class render function
    // as well in order to render the gauge components

    this->ResetGaugeCoordinateSystem();

    if (m_NumGaugeComponents > 0) {
      std::list<GaugeComponent*>::iterator it;
      
      for (it = m_GaugeComponentList.begin(); it != m_GaugeComponentList.end(); ++it) {
	(*it)->Render();
      }
    }

    this->ResetGaugeCoordinateSystem();

    if(m_DrawGaugeOutline) {
      this->DrawGaugeOutline();
    }

    return;
  }

  // Resets the gauge coordinate system before and after rendering components
  void Gauge::ResetGaugeCoordinateSystem() {
    this->RecalcWindowPlacement();

    // The viewport is established in order to clip things
    // outside the bounds of the gauge
    glViewport(m_PixelPosition.first, m_PixelPosition.second, m_PixelSize.first, m_PixelSize.second);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Define the projection so that we're drawing in "real" space
    glOrtho(0,m_PhysicalSize.first,0, m_PhysicalSize.second, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }

  void Gauge::RecalcWindowPlacement() {
    // Figure out where we're drawing in the window
    m_PixelPosition.first = (int) (m_PhysicalPosition.first / m_UnitsPerPixel);
    m_PixelPosition.second = (int) (m_PhysicalPosition.second / m_UnitsPerPixel);

    m_PixelSize.first = (int) (m_PhysicalSize.first / m_UnitsPerPixel * m_Scale.first);
    m_PixelSize.second = (int) (m_PhysicalSize.second / m_UnitsPerPixel * m_Scale.second);
  }

  void Gauge::SetUnitsPerPixel(const float unitsPerPixel) {
    m_UnitsPerPixel = unitsPerPixel;

    if (m_NumGaugeComponents > 0) {
      std::list<GaugeComponent*>::iterator it;
      
      for (it = m_GaugeComponentList.begin(); it != m_GaugeComponentList.end(); ++it) {
	(*it)->SetUnitsPerPixel(m_UnitsPerPixel);
      }
    }

    return;
  }

  void Gauge::SetScale(const float xScale, const float yScale) {
    // Set gauge scaling factors, must be greater than 0
    if ((xScale > 0) && (yScale > 0)) {
      m_Scale.first = xScale;
      m_Scale.second = yScale;

      if (m_NumGaugeComponents > 0) {
	std::list<GaugeComponent*>::iterator it;
	  
	for (it = m_GaugeComponentList.begin(); it != m_GaugeComponentList.end(); ++it) {
	  (*it)->SetScale(xScale, yScale);
	}
      }
    }

    return;
  }

  bool Gauge::ClickTest(const int button, const int state, const int x, const int y) {
    if( (x >= (int)m_PixelPosition.first)&&(x <= (int)(m_PixelPosition.first + m_PixelSize.first))
	&&(y >= (int)m_PixelPosition.second)&&(y <= (int)(m_PixelPosition.second + m_PixelSize.second)))
      {
	if(m_NumGaugeComponents > 0) {
	  std::list<GaugeComponent*>::iterator it;
	  for (it = m_GaugeComponentList.begin(); it != m_GaugeComponentList.end(); ++it) {
	    (*it)->HandleMouseButton(button, state, x, y);
	  }
	}
	return true;
      }
    else {
      return false;
    }
  }

  void Gauge::DrawGaugeOutline()
  {
    const float vertices[] = {
      0.0f, 0.0f,
      0.0f, (float) m_PhysicalSize.second,
      (float) m_PhysicalSize.first, (float) m_PhysicalSize.second,
      (float) m_PhysicalSize.first, 0.0f
    };

    glLineWidth(2.0);
    glColor3ub(0, 190, 190);
    glVertexPointer(2, GL_FLOAT, 0, &vertices);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
  }
}
