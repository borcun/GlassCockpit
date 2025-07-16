/**
 * GaugeComponents are the most "primitive" building block in the
 * OpenGC design scheme. Gauges are composed of a number of
 * GaugeComponents, each of which is capable of positioning and
 * drawing itself.
 *
 * By breaking a gauge into multiple GaugeComponents, recycling
 * of code is encouraged between different gauge designs.
 */

#pragma once

#include "RenderObject.h"
#include "FontManager.h"

namespace OpenGC {
  class GaugeComponent: public RenderObject {
  public:
    GaugeComponent();
    virtual ~GaugeComponent();
    void SetOpaque(bool opaque);
    virtual bool ClickTest(const int button, const int state, const int x, const int y) override;
    virtual void Render(void) override;

  private:
    bool m_Opaque;
  };
}
