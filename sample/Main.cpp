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

#include <FL/Fl.H>
#include <unistd.h>
#include <string.h>

#include "debug.h"
#include "AppObject.h"
#include "preference_manager.h"
#include "raster_map_manager.h"
#include "xml_parser.h"

#define DEFAULT_XML_FILE	(char*) "../resource/Default.xml"
#define PREFERENCES_XML_FILE	(char*) "../resource/Preferences.xml"

using namespace OpenGC;

/// Construct the one and only App Object
AppObject *theApp;

/** Print usage information */
void usage()
{
  LogPrintf("usage: OpenGC [config.xml]\nIf no XML configuration file"
	    "is provided Data/Default.xml is used.\n");
}

/** Global idle function to handle app updates */
void GlobalIdle(void *)
{
  theApp->IdleFunction();
  Fl::repeat_timeout(PreferenceManager::getInstance()->getDouble("AppUpdateRate"), GlobalIdle);
}

/** Main entry point for the application */
int main(int argc, char* argv[])
{	
  // Check the command line arguments
  char *xmlFileName = DEFAULT_XML_FILE;

  if (argc > 2) {
    usage();
    return 1;
  }
  else if (argc == 2) {
    // Check the file exists
    FILE *f = fopen(argv[1], "r");
    
    if (f == NULL) {
      usage();
      return 1;
    }
    else {
      xmlFileName = argv[1];
    }
  }
	
  theApp = new AppObject();
  PreferenceManager::getInstance()->initialize(PREFERENCES_XML_FILE);
  // Read the XML file and do some basic checks about its contents
  XMLParser parser;

  Assert(parser.read(xmlFileName), "unable to read XML file");
  Check(parser.hasNode("/"));
  Assert(parser.hasNode("/Window"), "invalid XML, no Window node");
  Assert(parser.hasNode("/DataSource"), "invalid XML, no DataSource node");
	
  // Set the user-defined (in XML file) application preferences
  if (parser.hasNode("/Preferences")) {
    PreferenceManager::getInstance()->populate(parser.getNode("/Preferences"));
  }

  // Set RasterMaps path
  RasterMapManager::getInstance()->SetCachePath(
      RasterMapManager::RMM_CACHE_MGMAPS, 
      PreferenceManager::getInstance()->getString("PathToData") + "MGMapsCache", "GoogleTer");

  // FIXME debug:
  PreferenceManager::getInstance()->display();

  // Set the update rate in nominal seconds per frame
  Fl::add_timeout(PreferenceManager::getInstance()->getDouble("AppUpdateRate"), GlobalIdle);

  // Run up the application
  int retval;
  XMLNode rootNode = parser.getNode("/");

  if (theApp->Go(rootNode)) {
    LogPrintf("Done, exiting cleanly.\n");
    retval = 0;
  }
  else {
    LogPrintf("Error, exiting.\n");
    retval = 1;
  }

  // Clean up
  delete theApp;

  return retval;
}

