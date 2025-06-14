#include "NavDatabase.h"
#include "BinaryNavData.h"
#include "Debug.h"
#include "data_source_manager.h"
#include "preference_manager.h"
#include <stdio.h>
#include <sys/stat.h> 

namespace OpenGC {
  NavDatabase *NavDatabase::m_instance = nullptr;
  
  NavDatabase::NavDatabase()
  {
    m_NavaidList = 0, m_NavaidHash = 0;
    m_AirportList = 0, m_AirportHash = 0;
    m_WaypointList = 0;
    m_FlightCourse = new FlightCourse();
  }

  NavDatabase::~NavDatabase()
  {
    if(m_NavaidList != 0)
      delete m_NavaidList;

    if(m_NavaidHash != 0)
      delete m_NavaidHash;

    if(m_AirportList != 0)
      delete m_AirportList;
	
    if(m_AirportHash != 0)
      delete m_AirportHash;

    if(m_WaypointList != 0)
      delete m_WaypointList;

    if(m_FlightCourse != 0)
      delete m_FlightCourse;
  }

  NavDatabase *NavDatabase::getInstance(void) {
    if (nullptr == m_instance) {
      m_instance = new NavDatabase();
    }

    return m_instance;
  }
  
  bool fileExists(const std::string& filename)
  {
    struct stat stFileInfo;
    if(stat(filename.c_str(), &stFileInfo) == 0) 
      return true;
    else
      return false;
  }

  void NavDatabase::InitDatabase()
  {	
    const std::string& pathToNav = PreferenceManager::getInstance()->getString("PathToData") + "Navigation/";
    const std::string& pathToWritableNav = PreferenceManager::getInstance()->getString("PathToCaches") + "Navigation/";
	
    // Check for cached binary copies of nav data otherwise convert and cache
    if (!fileExists(pathToWritableNav + "nav_dat.bin"))
      {
	LogPrintf("Generating binary cache of navaid data...\n");
	BinaryNavData::ConvertNavaidData(pathToNav + "nav.dat", pathToWritableNav + "nav_dat.bin");
      }
    if (!fileExists(pathToWritableNav + "apt_dat.bin"))
      {
	LogPrintf("Generating binary cache of airport data...\n");
	BinaryNavData::ConvertAirportData(pathToNav + "apt.dat", pathToWritableNav + "apt_dat.bin");
      }
	
    printf("NavDatabase: Loading navigation database... "); fflush(stdout);

    // Load and hash NavAid (binary) database
    m_NavaidList = new NavaidList;
    m_NavaidList->InitializeList(pathToWritableNav + "nav_dat.bin");
    m_NavaidHash = new GeographicHash;
    m_NavaidHash->InsertGeographicList(m_NavaidList);

    // Load and hash Airport (binary) database
    m_AirportList = new AirportList;
    m_AirportList->InitializeList(pathToWritableNav + "apt_dat.bin");
    m_AirportHash = new GeographicHash;
    m_AirportHash->InsertGeographicList(m_AirportList);

    // Load Waypoint database
    m_WaypointList = new WaypointList;
    m_WaypointList->InitializeList(pathToNav + "waypoint.dat");

    // Load and hash Map database
    // FIXME actually load the map shapes database

    printf("Done\nNavDatabase: Navigation database contains:\n");
    printf("\t%i NavAids\n\t%i Airports\n\t%i Waypoints\n\t%i Map shapes\n",
	   (int)m_NavaidList->size(), (int)m_AirportList->size(), 
	   (int)m_WaypointList->size(), 0 /* m_MapShapeList->size() */);
  }

} // end namespace OpenGC

