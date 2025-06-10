#include "data_source_manager.h"
#include "fg_data_source.h"
#include "albatross_data_source.h"
#include "test_data_source.h"

OpenGC::DataSourceManager *OpenGC::DataSourceManager::m_instance = nullptr;

OpenGC::DataSourceManager::DataSourceManager(void) {
  m_data_source = nullptr;
}

OpenGC::DataSourceManager::~DataSourceManager() {
  if (nullptr != m_data_source) {
    delete m_data_source;
    m_data_source = nullptr;
  }
}

OpenGC::DataSourceManager *OpenGC::DataSourceManager::getInstance(void) {
  if (nullptr == m_instance) {
    m_instance = new DataSourceManager();
  }

  return m_instance;
}

bool OpenGC::DataSourceManager::allocate(DataSourceType type) {
  if (nullptr != m_data_source) {
    return false;
  }
  
  switch (type) {
  case DATA_SOURCE_FG:
    m_data_source = new FGDataSource();
    break;
  case DATA_SOURCE_ALBATROSS:
    m_data_source = new AlbatrossDataSource();
    break;
  case DATA_SOURCE_TEST:
    m_data_source = new TestDataSource();
    break;
  }

  return nullptr != m_data_source;
}

OpenGC::DataSource *OpenGC::DataSourceManager::getDataSource(void) const {
  return m_data_source;
}
