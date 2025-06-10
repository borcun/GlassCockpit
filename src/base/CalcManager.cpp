#include "CalcManager.h"
#include "NavDatabase.h"
#include "data_source_manager.h"

namespace OpenGC {
  CalcManager::CalcManager()
  {
  }

  CalcManager::~CalcManager()
  {
  }

  void CalcManager::InitFromXMLNode(XMLNode calcNode)
  {
  }
	
  bool CalcManager::Calculate()
  {
    AirframeDataContainer* data = DataSourceManager::getInstance()->getDataSource()->GetAirframe();
	
    // FIXME this isn't really the right place for this...
    double lat = data->GetLatitude();
    double lon = data->GetLongitude();
    CoursePoint p = CoursePoint(lat, lon);

    NavDatabase::getInstance()->GetFlightCourse()->push_back(p);
	
    return false;
  }	
} // end namespace OpenGC
