#include "RenderObject.h"

OpenGC::RenderObject::RenderObject(void) {
  m_UnitsPerPixel = 1.0;
  m_PhysicalPosition.first = 0;
  m_PhysicalPosition.second = 0;
  m_PhysicalSize.first = 0;
  m_PhysicalSize.second = 0;
  m_Scale.first = 1.0;
  m_Scale.second = 1.0;
}

OpenGC::RenderObject::~RenderObject() {
  
}

void OpenGC::RenderObject::SetUnitsPerPixel(const float unitsPerPixel) {
  m_UnitsPerPixel = unitsPerPixel;
  return;
}

void OpenGC::RenderObject::SetScale(const float xScale, const float yScale) {
  if(xScale > 0.0) { m_Scale.first = xScale; }
  if(yScale > 0.0) { m_Scale.second = yScale; }

  return;
}

void OpenGC::RenderObject::SetPosition(const float xPos, const float yPos) {
  m_PhysicalPosition.first = xPos;
  m_PhysicalPosition.second = yPos;

  return;
}

void OpenGC::RenderObject::SetParentRenderObject(RenderObject* pObject) {
  m_pParentRenderObject = pObject;
  return;
}

std::pair<float, float> OpenGC::RenderObject::GetPhysicalPosition(void) {
  return m_PhysicalPosition;
}

// Called by framework when a mouse click occurs
void OpenGC::RenderObject::HandleMouseButton(const int button, const int state, const int x, const int y) {
  if (ClickTest(button, state, x, y)) {
    // Convert the click to an x/y position in render object physical coordinates
    float physX, physY;
	
    physX = ((x - m_PixelPosition.first) / m_PixelSize.first) * m_PhysicalSize.first;
    physY = ((y - m_PixelPosition.second) / m_PixelSize.second) * m_PhysicalSize.second;

    if(0 == state) {
      this->OnMouseDown(button, physX, physY);
    }
    else {
      this->OnMouseUp(button, physX, physY);
    }
  }

  return;
}

// Called when a mouse "down" event occurs
void OpenGC::RenderObject::OnMouseDown(const int button, const float physicalX, const float physicalY) {
  // The default version of this doesn't do anything
  // Overload to provide specific functionality
}

// Called when a mouse "up" event occurs
void OpenGC::RenderObject::OnMouseUp(const int button, const float physicalX, const float physicalY) {
  // The default version of this doesn't do anything
  // Overload to provide specific functionality
}

// Called when keyboard event occurs
void OpenGC::RenderObject::OnKeyboard(const int keycode, const int modifiers) {
  // The default version of this doesn't do anything
  // Overload to provide specific functionality
}
