#pragma once

#include "XMLNode.h"

namespace OpenGC {
  class CalcManager {
  public:
    CalcManager();
    ~CalcManager();
	
    void InitFromXMLNode(XMLNode calcNode);
    bool Calculate();
  };
}
