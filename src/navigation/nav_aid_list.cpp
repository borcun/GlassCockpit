#include <fstream>
#include "nav_aid_list.h"
#include "nav_aid_geo_obj.h"
#include "binary_nav_data.h"
#include "constants.h"
#include "debug.h"

OpenGC::NavaidList::NavaidList() {

}

OpenGC::NavaidList::~NavaidList() {

}

bool OpenGC::NavaidList::LoadData(const std::string &fileName) {
  std::ifstream file(fileName.c_str(), std::ios::binary);
  Assert(file.is_open(), "can't read navaid database");

  BinaryNavData::NavaidData *nav = new BinaryNavData::NavaidData();

  while (file.eof() != 1) {
    file.read((char *) nav, sizeof(BinaryNavData::NavaidData));
    
    if (nav->id_length >= MAX_NAV_ID_LENGTH) {
      nav->id[MAX_NAV_ID_LENGTH] = 0;
    }
    else {
      nav->id[nav->id_length] = 0;
    }
		
    NavaidGeoObj *pNavaid = new NavaidGeoObj();

    pNavaid->SetAltitudeMeters(nav->elev);
    pNavaid->SetIdentification(nav->id);
    pNavaid->SetDegreeLat(nav->lat);
    pNavaid->SetDegreeLon(nav->lon);
    // FIXME other info

    // Now add the navaid to the list
    push_back(pNavaid);
  }
  
  delete nav;

  return true;
}
