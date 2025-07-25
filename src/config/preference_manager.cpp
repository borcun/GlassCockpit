#include <iostream>
#include "xml_parser.h"
#include "preference_manager.h"

OpenGC::PreferenceManager *OpenGC::PreferenceManager::m_instance = nullptr;

OpenGC::PreferenceManager::PreferenceManager(void) {
  
}

OpenGC::PreferenceManager::~PreferenceManager() {
}

OpenGC::PreferenceManager *OpenGC::PreferenceManager::getInstance(void) {
  if (nullptr == m_instance) {
    m_instance = new PreferenceManager();
  }

  return m_instance;
}

bool OpenGC::PreferenceManager::load(const char *xml_file) {
  if (nullptr == xml_file) {
    std::cerr << "invalid xml file name" << std::endl;
    return false;
  }

  XMLParser parser;

  if (!parser.read(xml_file)) {
    std::cerr << "could not read XML file: " << xml_file << std::endl;
    return false;
  }
  
  if (!parser.hasNode("/")) {
    std::cerr << "could not read XML file, there is root node" << std::endl;
    return false;
  }

  XMLNode rootNode = parser.getNode("/");

  if (!rootNode.isValid() || 0 != rootNode.getName().compare("Preferences")) {
    std::cerr << "invalid root node, it is not equal to \'Preferences\'" << std::endl;
    return false;
  }

  std::list<XMLNode> node_list = rootNode.getChildList();
  bool is_succeed = true;
  
  for (auto it = node_list.begin(); is_succeed && it != node_list.end(); ++it) {
    if (0 != it->getName().compare("Preference")) {
      is_succeed = false;
    }
    else if (!it->hasChild("Name") || !it->hasChild("Type") || !it->hasChild("Value")) {
      is_succeed = false;
    }
    else {	
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
  }

  // if parsing failed, clear data cached s
  if (!is_succeed) {
    m_floating_preferences.clear();
    m_decimal_preferences.clear();
    m_string_preferences.clear();
    m_boolean_preferences.clear();
  }
  
  return is_succeed;
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
