#pragma once

#include "data_source.h"

namespace OpenGC {
  enum DataSourceType {
    DATA_SOURCE_NONE,
    DATA_SOURCE_FG,
    DATA_SOURCE_ALBATROSS,
    DATA_SOURCE_TEST
  };
  
  class DataSourceManager {
  public:
    static DataSourceManager *getInstance(void);
    virtual ~DataSourceManager();
    bool allocate(DataSourceType type);
    DataSource *getDataSource(void) const;
    
  private:
    /// single class instance
    static DataSourceManager *m_instance;
    /// data source reference
    DataSource *m_data_source = nullptr;

    // singleton class
    DataSourceManager();
  };
}
