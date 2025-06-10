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
