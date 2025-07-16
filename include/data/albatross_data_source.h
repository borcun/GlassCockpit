#pragma once

#include "data_source.h"

namespace OpenGC {
  class AlbatrossDataSource : public DataSource {
  public:
    AlbatrossDataSource(void);
    virtual ~AlbatrossDataSource();

    bool open(void) override;
    bool onIdle(void) override;
  };
}
