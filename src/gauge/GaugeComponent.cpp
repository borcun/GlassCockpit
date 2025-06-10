#include "GaugeComponent.h"

OpenGC::GaugeComponent::GaugeComponent() : m_Opaque(true)
{
  
}

OpenGC::GaugeComponent::~GaugeComponent() {

}

void OpenGC::GaugeComponent::SetOpaque(bool opaque) {
  m_Opaque = opaque;
  return;
}

bool OpenGC::GaugeComponent::ClickTest(const int button, const int state, const int x, const int y) {
  if( (x >= (int)m_PixelPosition.first)&&(x <= (int)(m_PixelPosition.first + m_PixelSize.first))
      &&(y >= (int)m_PixelPosition.second)&&(y <= (int)(m_PixelPosition.second + m_PixelSize.second)) )
    {
      // Click is inside the GaugeComponent
      return true;
    }

  return false;
}

void OpenGC::GaugeComponent::Render(void) {
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

  return;
}
