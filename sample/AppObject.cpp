/*=========================================================================

  OpenGC - The Open Source Glass Cockpit Project
  Please see our web site at http://www.opengc.org

  Albatross UAV Project - http://www.albatross-uav.org

  Copyright (c) 2001-2003 Damion Shelton
  All rights reserved. Contributions by Hugo Vincent.
  See Copyright.txt or http://www.opengc.org/Copyright.htm for details.

  This software is distributed WITHOUT ANY WARRANTY; without even 
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
  PURPOSE.  See the above copyright notice for more information.

  =========================================================================*/

#include <iostream>

//--------Base-----------------
#include "GLHeaders.h"
#include <FL/Fl.H>
#include "AppObject.h"
#include "RenderObject.h"
#include "PrefManager.h"
#include "NavDatabase.h"
#include "Debug.h"

//--------Data Sources---------
#include "data_source_manager.h"
#include "albatross_data_source.h"
#include "test_data_source.h"
#include "fg_data_source.h"

//--------Gauges---------------
#include "PFD.h"
#include "NavDisplay.h"
#include "EngineInstruments.h"

namespace OpenGC {
  AppObject::AppObject() {
    // Make sure all the pointers are nulled out
    m_pRenderWindow = 0;
  }

  AppObject::~AppObject() {
    if(m_pRenderWindow != 0) {
      delete m_pRenderWindow;
      m_pRenderWindow = 0;
    }
  }

  bool AppObject::Go(XMLNode rootNode)
  {	
    // Navigation Database (global)
    NavDatabase::getInstance()->InitDatabase();

    // Create the data source
    XMLNode dsNode = rootNode.GetChild("DataSource");
    Assert(dsNode.HasProperty("type"), "DataSource node has no type property");
    string dsName = dsNode.GetProperty("type");
    char *titleSuffix;
    
    if (dsName == "FlightGear") {
      // Get host/port settings
      if (dsNode.HasChild("Host")) {
	PrefManager::getInstance()->SetPrefS("FlightGearHost", 
					     dsNode.GetChild("Host").GetText());
      }
      
      if (dsNode.HasChild("Port")) {
	PrefManager::getInstance()->SetPrefI("FlightGearPort", 
					     dsNode.GetChild("Port").GetTextAsInt());
      }

      DataSourceManager::getInstance()->allocate(DATA_SOURCE_FG);
	
      if (!DataSourceManager::getInstance()->getDataSource()->Open()) {
	return false;
      }
	
      titleSuffix = (char *)" (FlightGear)";
    }
    else if (dsName == "Albatross") {
      DataSourceManager::getInstance()->allocate(DATA_SOURCE_ALBATROSS);
      titleSuffix = (char *)" (Flight Mode)";
    }
    else if (dsName == "Test") {
      DataSourceManager::getInstance()->allocate(DATA_SOURCE_TEST);
      titleSuffix = (char *)" (Test)";
    }
    else {
      printf("Invalid data source \"%s\".\n", dsName.c_str());
      return false;
    }

    // Set up the window title
    XMLNode windowNode = rootNode.GetChild("Window");
    string windowTitle = "Glass Cockpit";

    if (windowNode.HasChild("Title")) {
      windowTitle = windowNode.GetChild("Title").GetText();
    }
    
    windowTitle += titleSuffix;
	
    // Calculate window size
    double xSize = 1127.0, ySize = 785.0; // default size
    
    if (windowNode.HasChild("Geometry"))
      {
	XMLNode geoNode = windowNode.GetChild("Geometry");
	if (geoNode.HasChild("Size"))
	  {
	    geoNode.GetChild("Size").GetTextAsCoord(xSize, ySize);
	  }
      }
    double zoom = PrefManager::getInstance()->GetPrefD("Zoom");
    int windowX = (int)(xSize * zoom), windowY = (int)(ySize * zoom);
    LogPrintf("Application: Window Size = %ix%ipx\n", windowX, windowY);

    // Create the render window
    m_pRenderWindow = new FLTKRenderWindow(4, 0, windowX, windowY, 
					   windowTitle.c_str());
    m_pRenderWindow->mode(FL_RGB | FL_DOUBLE);
    PrefManager::getInstance()->SetPrefD("UnitsPerPixel", 
					 m_pRenderWindow->GetUnitsPerPixel());	

    // We need to go ahead and show the window so that an OpenGL device
    // context exists once we start loading fonts
    m_pRenderWindow->show();

    // Force the render window to update to obtain a valid device context
    m_pRenderWindow->redraw();
    Fl::flush();

    // Create Gauges as described by the XML file
    XMLNode::NodeList nodeList = windowNode.GetChildList("Gauge");
    XMLNode::NodeList::iterator iter;
    for (iter = nodeList.begin(); iter != nodeList.end(); ++iter)
      {
	Gauge *pGauge;
	string name = (*iter).GetProperty("type");

	if(name == "PFD")
	  {
	    pGauge = new PFD();
	  }
	else if(name == "NavDisplay")
	  {
	    pGauge = new NavDisplay();
	  }
	else if(name == "EngineInstruments")
	  {
	    pGauge = new EngineInstruments();
	  }
	else
	  {
	    printf("Error: unsupported gauge type \"%s\"\n", name.c_str());
	    return false;
	  }

	pGauge->InitFromXMLNode(*iter);
	m_pRenderWindow->AddGauge(pGauge);
      }

    // Now it's time to enter the event loop
    Fl::run();

    return true; // sucess
  }

  void AppObject::IdleFunction()
  {
    // Every time we loop we grab some new data...
    bool changed1 = DataSourceManager::getInstance()->getDataSource()->OnIdle();

    // ...calculate extra data from the incoming data...
    AirframeDataContainer* data = DataSourceManager::getInstance()->getDataSource()->GetAirframe();
    // FIXME this isn't really the right place for this...
    double lat = data->GetLatitude();
    double lon = data->GetLongitude();
    CoursePoint p = CoursePoint(lat, lon);

    NavDatabase::getInstance()->GetFlightCourse()->push_back(p);

    // and re-render the window if there is new data.
    if(changed1) {
      m_pRenderWindow->redraw();
      Fl::flush();
    }

    return;
  }
} // end namespace OpenGC

