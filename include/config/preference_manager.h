#pragma once

#include <map>
#include "xml_parser.h"

namespace OpenGC {
  class PreferenceManager {
  public:
    /// function that gets single instance of the class
    /// @return static single instance
    static PreferenceManager *getInstance(void);
    /// destructor
    virtual ~PreferenceManager();    
    /// function that initializes the preferences map from an XML file
    /// @param [in] path - XML file path
    void initialize(const char *path);
    /// function that gets floating value of field matching key
    /// @param [in] key - key field
    /// @param [out] value - value field
    /// @return true if key is found into the list, otherwise false
    bool get(const std::string &key, double &value);
    /// function that gets decimal value of field matching key
    /// @param [in] key - key field
    /// @param [out] value - value field
    /// @return true if key is found into the list, otherwise false
    bool get(const std::string &key, int &value);
    /// function that gets string value of field matching key
    /// @param [in] key - key field
    /// @param [out] value - value field
    /// @return true if key is found into the list, otherwise false
    bool get(const std::string &key, std::string &value);
    /// function that gets boolean value of field matching key
    /// @param [in] key - key field
    /// @param [out] value - value field
    /// @return true if key is found into the list, otherwise false
    bool get(const std::string &key, bool &value);
    
  private:
    /// single instance of the class
    static PreferenceManager *m_instance;
    /// floating preference lists
    std::map<std::string, double> m_floating_preferences;
    /// decimal preference lists
    std::map<std::string, int> m_decimal_preferences;
    /// string preference lists
    std::map<std::string, std::string> m_string_preferences;
    /// boolean preference lists
    std::map<std::string, bool> m_boolean_preferences;

    /// default constructor
    PreferenceManager(void);
  };
}
