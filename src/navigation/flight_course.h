#pragma once

#include <vector>
#include <utility>

namespace OpenGC {
  /// course point pair
  class FlightCourse : public std::vector<std::pair<double, double>> {
  public:
    FlightCourse() {}
    virtual ~FlightCourse() {}
  };
}

