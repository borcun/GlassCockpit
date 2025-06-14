#include <iostream>
#include <sstream>
#include <fstream>
#include "AirportList.h"
#include "Constants.h"
#include "BinaryNavData.h"
#include "Debug.h"

namespace OpenGC
{

  using namespace std;

  AirportList::AirportList()
  {

  }

  AirportList::~AirportList()
  {

  }

  bool AirportList::LoadData(const std::string& fileName)
  {
    ifstream file(fileName.c_str(), ios::binary);
    Assert(file.is_open(), "can't read airport database");

    // The struct that is read in for each airport
    BinaryNavData::AirportData *apt = new BinaryNavData::AirportData;

    // Now iterate over the structs in the file
    while (file.eof() != 1)
      {
	file.read((char*)apt, sizeof(BinaryNavData::AirportData));

	// Ensure ID std::string is null terminated
	if (apt->id_length >= MAX_APT_ID_LENGTH)
	  {
	    apt->id[MAX_APT_ID_LENGTH] = 0;
	  }
	else
	  {
	    apt->id[apt->id_length] = 0;
	  }
		
	// Create the AirportGeoObj and fill out it's fields
	GeographicObject *airport = new GeographicObject();
	
	airport->SetAltitudeMeters(apt->elev);
	airport->SetIdentification(apt->id);
	airport->SetDegreeLat(apt->lat);
	airport->SetDegreeLon(apt->lon);

	// Now add the airport to the list
	this->push_back(airport);
      }
    delete apt;
    return true;
  }

} // end namespace OpenGC

