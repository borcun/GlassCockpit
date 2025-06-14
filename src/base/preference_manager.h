#pragma once

#include <map>
#include "XMLParser.h"

namespace OpenGC {
  // The structure that configuration options are stored in
  struct Preference {
    std::string asString;
    double asDouble;
    bool asBool;
    int	asInt;
    bool isSet; // set to true when initialised
    char type;  // 'I'=int, 'B'=bool, 'D'=double, 'S'=string
  };
  
  using PreferenceMap = std::map<std::string, Preference *>;

  /** Global manager for preferences in the application. Preferences are stored
   * in an STL map, where the XML node name for each preference (i.e. a string)
   * is the key. See preferences.xml to see or change the default preferences,
   * or default.xml (or your setup XML file) to change your specific preference
   * values. */
  class PreferenceManager {
  public:
    /// function that gets single instance of the class
    /// @return static single instance
    static PreferenceManager *getInstance(void);

    /// destructor
    virtual ~PreferenceManager();
    
    ///function that initializes the preferences map from an XML file
    /// @param [in] path - XML file path
    void initialize(const char *path);
    
    ///function that populates preferences from XML preference node
    /// @param [in] prefNode - preference node
    void populate(XMLNode prefNode);			

    void setString(const std::string &key, const std::string &value);
    void setBoolean(const std::string &key, const bool value);
    void setDouble(const std::string &key, const double value);
    void setInteger(const std::string &key, const int value);
    std::string getString(const std::string &key);
    bool getBoolean(const std::string &key);
    double getDouble(const std::string &key);
    int getInteger(const std::string &key);
    
    /** Print all preferences for debugging */
    void display(void) const;

  private:
    /// single instance of the class
    static PreferenceManager *m_instance;
    /// preference list
    PreferenceMap m_preferences;

    /// default constructor
    PreferenceManager();
  };
}
