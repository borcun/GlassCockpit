/**
 * The base class for all gauges in the OpenGC object model.
 * Gauge's define a client rendering space and an associated
 * orthographic projection. Use of a client rendering space, in
 * the form of a glRenderWindow(), allows for greatly simplified
 * clipping, since objects drawn outside of the render window
 * are not displayed. The client window calculations are for the
 * most part used to manage the placement of GaugeComponents (i.e.
 * the intent is to use GaugeComponents for drawing, rather than
 * drawing within a Gauge, in order to promote reusability of
 * code.
 *
 * Gauge's contain one or more GaugeComponents, which also define
 * client rendering space and a viewport transform.
 */

#pragma once

#include <list>
#include "GaugeComponent.h"
#include "XMLNode.h"

namespace OpenGC {
  class Gauge: public RenderObject {
  public:
    Gauge(void);
    virtual ~Gauge();
    /** Recalculates placement of the gauge in the window */
    void RecalcWindowPlacement();
    /** Resets the gauge coordinate system before and after rendering components */
    void ResetGaugeCoordinateSystem();
    /** Determine whether or not to draw the gauge outline */
    void SetGaugeOutline(bool outline) { m_DrawGaugeOutline = outline; }
    /** Set up using XML options. Pass it the <Gauge> node. */
    void InitFromXMLNode(XMLNode gaugeNode);	
    /** Add a gauge component */
    void AddGaugeComponent(GaugeComponent* pComponent);
    /** Overloaded method for setting the monitor calibration */
    void SetUnitsPerPixel(const float unitsPerPixel) override;
    /** Set the x and y scale of the gauge (and member components) */
    void SetScale(const float xScale, const float yScale) override;

    /** Return true if the click is inside the gauge
	If true, tests gauge components prior to returning */
    virtual bool ClickTest(const int button, const int state, const int x, const int y) override;
    /** Overloaded render method */
    virtual void Render(void) override;

  protected:
    /** All of the guage components */
    std::list<GaugeComponent *> m_GaugeComponentList;
    /** The number of gauge components in this gauge */
    int m_NumGaugeComponents;
    /** Whether or not to draw a blue line around the gauge */
    bool m_DrawGaugeOutline;

    /** Overload to set Gauge-specific options */
    virtual void CustomXMLInit(XMLNode node) {}
    /** Draw the gauge outline */
    void DrawGaugeOutline();
  };
}
