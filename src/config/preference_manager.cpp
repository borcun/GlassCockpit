#include <iostream>
#include "preference_manager.h"
#include "debug.h"

OpenGC::PreferenceManager *OpenGC::PreferenceManager::m_instance = nullptr;

OpenGC::PreferenceManager::PreferenceManager() {
  
}

OpenGC::PreferenceManager::~PreferenceManager() {
  for (auto it = m_preferences.begin(); it != m_preferences.end(); ++it) {
    delete it->second;
  }
}

OpenGC::PreferenceManager *OpenGC::PreferenceManager::getInstance(void) {
  if (nullptr == m_instance) {
    m_instance = new PreferenceManager();
  }

  return m_instance;
}

void OpenGC::PreferenceManager::initialize(const char *xmlFileName) {
  XMLParser parser;
  Assert(parser.read(xmlFileName), "unable to read XML file");
  Check(parser.hasNode("/"));

  XMLNode rootNode = parser.getNode("/");
  Check(rootNode.isValid() && rootNode.getName() == "Preferences");

  // Iterate over the preference definitions
  std::list<XMLNode> nodeList = rootNode.getChildList();
  
  for (std::list<XMLNode>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
    XMLNode node = *it;
      
    Check(node.getName() == "Preference");
    Check(node.hasChild("Name") && node.hasChild("Type") && node.hasChild("DefaultValue"));
		
    // Now create each Preference struct
    Preference *preference = new Preference();
    std::string type = node.getChild("Type").getText();

    if (type == "double") {
      preference->type = 'D';
      preference->asDouble = node.getChild("DefaultValue").getTextAsDouble();
    }
    else if (type == "string") {
      preference->type = 'S';
      preference->asString = node.getChild("DefaultValue").getText();
    }
    else if (type == "integer") {
      preference->type = 'I';
      preference->asInt = node.getChild("DefaultValue").getTextAsInt();
    }
    else if (type == "boolean") {
      preference->type = 'B';
      preference->asBool = node.getChild("DefaultValue").getTextAsBool();
    }
    
    preference->isSet = true;
    m_preferences[node.getChild("Name").getText()] = preference;
  }

  return;
}

void OpenGC::PreferenceManager::populate(XMLNode prefNode) {
  // Load in XML values for the preferences
  Check(prefNode.isValid() && prefNode.getName() == "Preferences");
  
  std::list<XMLNode> nodeList = prefNode.getChildList();
  std::list<XMLNode>::iterator it;
    
  for (it = nodeList.begin(); it != nodeList.end(); ++it) {
    std::string key = it->getName();
	
    LogPrintf("PreferenceManager: setting %s = %s\n", key.c_str(), it->getText().c_str());

    // set the preference
    Preference *toSet = m_preferences[key];

    if (toSet->type == 'D') {
      setDouble(key, it->getTextAsDouble());
    }
    else if (toSet->type == 'S') {
      setString(key, it->getText());
    }
    else if (toSet->type == 'I') {
      setInteger(key, it->getTextAsInt());
    }
    else if (toSet->type == 'B') {
      setBoolean(key, it->getTextAsBool());
    }
  }

  return;
}

bool OpenGC::PreferenceManager::getBoolean(const std::string &key) {
  const Preference * const preference = m_preferences[key];
  
  Assert(preference != NULL, "no such preference");
  Assert(preference->isSet && preference->type == 'B', "getting un-set Preference");

  return preference->asBool;
}

int OpenGC::PreferenceManager::getInteger(const std::string &key) {
  const Preference * const preference = m_preferences[key];
  
  Assert(preference != NULL, "no such preference");
  Assert(preference->isSet && preference->type == 'I', "getting un-set Preference");

  return preference->asInt;
}

double OpenGC::PreferenceManager::getDouble(const std::string &key) {
  const Preference * const preference = m_preferences[key];
  
  Assert(preference != NULL, "no such preference");
  Assert(preference->isSet && preference->type == 'D', "getting un-set Preference");

  return preference->asDouble;
}

std::string OpenGC::PreferenceManager::getString(const std::string &key) {
  const Preference * const preference = m_preferences[key];
  
  Assert(preference != NULL, "no such preference");
  Assert(preference->isSet && preference->type == 'S', "getting un-set Preference");

  return preference->asString;
}

void OpenGC::PreferenceManager::setBoolean(const std::string &key, const bool value) {
  Preference * const preference = m_preferences[key];
  
  if (preference->isSet) {
    Assert(preference->type == 'B', "setting preference with wrong type");
    preference->asBool = value;
  }
  else {
    preference->isSet = true;
    preference->type = 'B';
    preference->asBool = value;
  }

  return;
}

void OpenGC::PreferenceManager::setDouble(const std::string &key, const double value) {
  Preference * const preference = m_preferences[key];

  if (preference->isSet) {
    Assert(preference->type == 'D', "setting preference with wrong type");
    preference->asDouble = value;
  }
  else {
    preference->isSet = true;
    preference->type = 'D';
    preference->asDouble = value;
  }

  return;
}

void OpenGC::PreferenceManager::setString(const std::string &key, const std::string &value) {
  Preference * const preference = m_preferences[key];
  
  if (preference->isSet) {
    Assert(preference->type == 'S', "setting preference with wrong type");
    preference->asString = value;
  }
  else {
    preference->isSet = true;
    preference->type = 'S';
    preference->asString = value;
  }

  return;
}

void OpenGC::PreferenceManager::setInteger(const std::string &key, const int value) {
  Preference * const preference = m_preferences[key];
  
  if (preference->isSet) {
    Assert(preference->type == 'S', "setting preference with wrong type");
    preference->asInt = value;
  }
  else {
    preference->isSet = true;
    preference->type = 'S';
    preference->asInt = value;
  }

  return;
}

void OpenGC::PreferenceManager::display(void) const {
  std::cout << "PreferenceManager: database contains " << m_preferences.size() << " entries:" << std::endl;

  for (auto it = m_preferences.begin(); it != m_preferences.end(); ++it) {
    switch (it->second->type) {
    case 'D':
      std::cout << "\t" << it->first.c_str() << " = [double] " << it->second->asDouble << std::endl;
      break;
    case 'S':
      std::cout << "\t" << it->first.c_str() << " = [string] " << it->second->asString << std::endl;
      break;
    case 'B':
      std::cout << "\t" << it->first.c_str() << " = [bool] " << it->second->asBool << std::endl;
      break;
    case 'I':
      std::cout << "\t" << it->first.c_str() << " = [integer] " << it->second->asInt << std::endl;
      break;
    }
  }
  
  return;
}
