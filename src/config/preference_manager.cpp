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

  std::list<XMLNode> node_list = rootNode.getChildList();
  
  for (auto it = node_list.begin(); it != node_list.end(); ++it) {
    Check(it->getName() == "Preference");
    Check(it->hasChild("Name") && it->hasChild("Type") && it->hasChild("Value"));
		
    std::string type = it->getChild("Type").getText();
    std::string key = it->getChild("Name").getText();
    
    if (type == "double") {
      m_floating_preferences[key] = it->getChild("Value").getTextAsDouble();
    }
    else if (type == "integer") {
      m_decimal_preferences[key] = it->getChild("Value").getTextAsInt();
    }
    else if (type == "string") {
      m_string_preferences[key] = it->getChild("Value").getText();
    }
    else if (type == "boolean") {
      m_boolean_preferences[key] = it->getChild("Value").getTextAsBool();
    }
    else {
      std::cerr << "invalid field type in XML: " << type << std::endl;
    }
  }

  return;
}

bool OpenGC::PreferenceManager::get(const std::string &key, double &value) {
  auto it = m_floating_preferences.find(key);

  if (m_floating_preferences.end() == it) {
    return false;
  }

  value = it->second;
  return true;
}

bool OpenGC::PreferenceManager::get(const std::string &key, int &value) {
  auto it = m_decimal_preferences.find(key);

  if (m_decimal_preferences.end() == it) {
    return false;
  }

  value = it->second;
  return true;
}

bool OpenGC::PreferenceManager::get(const std::string &key, std::string &value) {
  auto it = m_string_preferences.find(key);

  if (m_string_preferences.end() == it) {
    return false;
  }

  value = it->second;
  return true;
}

bool OpenGC::PreferenceManager::get(const std::string &key, bool &value) {
  auto it = m_boolean_preferences.find(key);

  if (m_boolean_preferences.end() == it) {
    return false;
  }

  value = it->second;
  return true;
}
