#include <iostream>
#include "preference_manager.h"
#include "debug.h"

OpenGC::PreferenceManager *OpenGC::PreferenceManager::m_instance = nullptr;

OpenGC::PreferenceManager::PreferenceManager() {
  
}

OpenGC::PreferenceManager::~PreferenceManager() {
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
    Check(node.hasChild("Name") && node.hasChild("Type") && node.hasChild("Value"));
		
    Preference preference;
    std::string type = node.getChild("Type").getText();

    if (type == "double") {
      preference.type = 'D';
      preference.asDouble = node.getChild("Value").getTextAsDouble();
    }
    else if (type == "string") {
      preference.type = 'S';
      preference.asString = node.getChild("Value").getText();
    }
    else if (type == "integer") {
      preference.type = 'I';
      preference.asInt = node.getChild("Value").getTextAsInt();
    }
    else if (type == "boolean") {
      preference.type = 'B';
      preference.asBool = node.getChild("Value").getTextAsBool();
    }
    
    preference.isSet = true;
    m_preferences[node.getChild("Name").getText()] = preference;
  }

  return;
}

bool OpenGC::PreferenceManager::getBoolean(const std::string &key) {
  auto it = m_preferences.find(key);
  return it->second.asBool;
}

int OpenGC::PreferenceManager::getInteger(const std::string &key) {
  auto it = m_preferences.find(key);
  return it->second.asInt;
}

double OpenGC::PreferenceManager::getDouble(const std::string &key) {
  auto it = m_preferences.find(key);
  return it->second.asDouble;
}

std::string OpenGC::PreferenceManager::getString(const std::string &key) {
  auto it = m_preferences.find(key);
  return it->second.asString;
}

void OpenGC::PreferenceManager::print(void) const {
  std::cout << "PreferenceManager: database contains " << m_preferences.size() << " entries:" << std::endl;

  for (auto it = m_preferences.begin(); it != m_preferences.end(); ++it) {
    switch (it->second.type) {
    case 'D':
      std::cout << "\t" << it->first.c_str() << " = [double] " << it->second.asDouble << std::endl;
      break;
    case 'S':
      std::cout << "\t" << it->first.c_str() << " = [string] " << it->second.asString << std::endl;
      break;
    case 'B':
      std::cout << "\t" << it->first.c_str() << " = [bool] " << it->second.asBool << std::endl;
      break;
    case 'I':
      std::cout << "\t" << it->first.c_str() << " = [integer] " << it->second.asInt << std::endl;
      break;
    }
  }
  
  return;
}
