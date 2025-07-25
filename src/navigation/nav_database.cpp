#include <sys/stat.h>
#include <iostream>
#include "nav_database.h"
#include "binary_nav_data.h"
#include "data_source_manager.h"
#include "preference_manager.h"
#include "debug.h"

OpenGC::NavDatabase *OpenGC::NavDatabase::m_instance = nullptr;
  
OpenGC::NavDatabase::NavDatabase() {
  m_NavaidList = 0, m_NavaidHash = 0;
  m_AirportList = 0, m_AirportHash = 0;
  m_WaypointList = 0;
  m_FlightCourse = new FlightCourse();
}

OpenGC::NavDatabase::~NavDatabase() {
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

OpenGC::NavDatabase *OpenGC::NavDatabase::getInstance(void) {
  if (nullptr == m_instance) {
    m_instance = new NavDatabase();
  }

  return m_instance;
}
  
bool fileExists(const std::string &filename) {
  struct stat stFileInfo;
  return stat(filename.c_str(), &stFileInfo) == 0;
}

void OpenGC::NavDatabase::InitDatabase() {
  std::string pathToNav;
  std::string pathToWritableNav;

  PreferenceManager::getInstance()->get("PathToData", pathToNav);
  PreferenceManager::getInstance()->get("PathToCaches", pathToWritableNav);

  pathToNav.append("Navigation/");
  pathToWritableNav.append("Navigation/");

  // Check for cached binary copies of nav data otherwise convert and cache
  if (!fileExists(pathToWritableNav + "nav_dat.bin")) {
    LogPrintf("Generating binary cache of navaid data...\n");
    BinaryNavData::ConvertNavaidData(pathToNav + "nav.dat", pathToWritableNav + "nav_dat.bin");
  }
  
  if (!fileExists(pathToWritableNav + "apt_dat.bin")) {
    LogPrintf("Generating binary cache of airport data...\n");
    BinaryNavData::ConvertAirportData(pathToNav + "apt.dat", pathToWritableNav + "apt_dat.bin");
  }
	
  std::cout << "NavDatabase: Loading navigation database..." << std::endl;

  // Load and hash NavAid (binary) database
  m_NavaidList = new NavaidList();
  m_NavaidList->initialize(pathToWritableNav + "nav_dat.bin");

  m_NavaidHash = new GeographicHash();
  m_NavaidHash->InsertGeographicList(m_NavaidList);

  // Load and hash Airport (binary) database
  m_AirportList = new AirportList();
  m_AirportList->initialize(pathToWritableNav + "apt_dat.bin");
  
  m_AirportHash = new GeographicHash();
  m_AirportHash->InsertGeographicList(m_AirportList);

  // Load Waypoint database
  m_WaypointList = new WaypointList();
  m_WaypointList->initialize(pathToNav + "waypoint.dat");

  // Load and hash Map database
  // FIXME actually load the map shapes database

  std::cout << "Done" << std::endl << "NavDatabase: Navigation database contains:" << std::endl;
  std::cout << m_NavaidList->size() << ", " << m_AirportList->size() << ", " <<	m_WaypointList->size() << std::endl;

  return;
}
