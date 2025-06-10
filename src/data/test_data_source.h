#pragma once

#include "data_source.h"

namespace OpenGC {
  enum TestState {
    STATE_WAITING,
    STATE_CONNECTING,
    STATE_FD,
    STATE_RUNNING
  }; 

  class TestDataSource : public DataSource {
  public:
    TestDataSource(void);
    virtual ~TestDataSource();

    bool open(void) override;
    bool onIdle(void) override;

  private:
    TestState m_state;
  };
}
