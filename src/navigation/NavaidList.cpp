#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "NavaidList.h"
#include "NavaidGeoObj.h"
#include "Constants.h"
#include "BinaryNavData.h"
#include "Debug.h"

namespace OpenGC
{

  using namespace std;

  NavaidList::NavaidList()
  {

  }

  NavaidList::~NavaidList()
  {

  }

  bool NavaidList::LoadData(const std::string& fileName)
  {
    ifstream file(fileName.c_str(), ios::binary);
    Assert(file.is_open(), "can't read navaid database");

    // The struct that is read in for each navaid
    BinaryNavData::NavaidData *nav = new BinaryNavData::NavaidData;

    // Now iterate over the structs in the file
    while (file.eof() != 1)
      {
	file.read((char*)nav, sizeof(BinaryNavData::NavaidData));

	// Ensure ID std::string is null terminated
	if (nav->id_length >= MAX_NAV_ID_LENGTH)
	  {
	    nav->id[MAX_NAV_ID_LENGTH] = 0;
	  }
	else
	  {
	    nav->id[nav->id_length] = 0;
	  }
		
	// Create the NavaidGeoObj and fill out it's fields
	NavaidGeoObj* pNavaid = new NavaidGeoObj();
	pNavaid->SetAltitudeMeters(nav->elev);
	pNavaid->SetIdentification(nav->id);
	pNavaid->SetDegreeLat(nav->lat);
	pNavaid->SetDegreeLon(nav->lon);
	// FIXME other info

	// Now add the navaid to the list
	this->push_back(pNavaid);
      }
    delete nav;
    return true;
  }

} // end namespace OpenGC

