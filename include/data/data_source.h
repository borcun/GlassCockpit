#pragma once

#include "airframe_data_container.h"

namespace OpenGC {
  class DataSource {
  public:		
    DataSource(void);
    virtual ~DataSource();

    /** Get access to airframe data */
    AirframeDataContainer *GetAirframe(void) const;

    /**
     * Called by the base AppObject after all the init parameters
     * have been complete. This should open the connection to the sim
     */
    virtual bool open() = 0;

    /**
     * Called by the render window during idle processing
     * This function is the one and only place where OpenGC
     * should acquire data from the sim
     */
    virtual bool onIdle() = 0;

  protected:
    // Data that describes the airframe (alt, heading, control surfaces, etc.) 
    AirframeDataContainer *m_airframe = nullptr;
  };
}
