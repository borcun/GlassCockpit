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

/**
 * Responsible for creating a global AppObject (the application), processing
 * the command line arguments, setting some run-time configuration options
 * from the XML file, and starting the application.
 */

#include <iostream>
#include <FL/Fl.H>
#include <unistd.h>
#include <string.h>
#include "debug.h"
#include "AppObject.h"
#include "preference_manager.h"
#include "raster_map_manager.h"
#include "xml_parser.h"

using namespace OpenGC;

/// Construct the one and only App Object
AppObject application;

void GlobalIdle(void *) {
  double update_rate = 0.0;
  application.IdleFunction();
  
  if (PreferenceManager::getInstance()->get("AppUpdateRate", update_rate)) {
    Fl::repeat_timeout(update_rate, GlobalIdle);
  }

  return;
}

int main(int argc, char **argv) {	
  if (3 != argc) {
    std::cout << "usage: ./opengc-sample default.xml preference.xml - " << argc << std::endl;
    return -1;
  }

  PreferenceManager *pref_man = PreferenceManager::getInstance();
  char *xmlFileName = argv[1];	
  XMLParser parser;
    
  pref_man->initialize(argv[2]);

  Assert(parser.read(xmlFileName), "unable to read XML file");
  Check(parser.hasNode("/"));
  Assert(parser.hasNode("/Window"), "invalid XML, no Window node");
  Assert(parser.hasNode("/DataSource"), "invalid XML, no DataSource node");

  std::string path_to_data;
  
  if (!pref_man->get("PathToData", path_to_data)) {
    std::cerr << "could not path to data" << std::endl;
    return -1;
  }
  
  RasterMapManager::getInstance()->SetCachePath(RasterMapManager::RMM_CACHE_MGMAPS, path_to_data + "MGMapsCache", "GoogleTer");

  double update_rate = 0.0;

  if (!pref_man->get("AppUpdateRate", update_rate)) {
    std::cerr << "could not get application update rate" << std::endl;
    return -1;
  }
  
  Fl::add_timeout(update_rate, GlobalIdle);

  int retval;
  XMLNode rootNode = parser.getNode("/");

  if (application.Go(rootNode)) {
    LogPrintf("Done, exiting cleanly.\n");
    retval = 0;
  }
  else {
    LogPrintf("Error, exiting.\n");
    retval = 1;
  }

  return retval;
}

