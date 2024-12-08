#ifndef INTERVAL_H
#define INTERVAL_H

#include "utils.h"
class interval {
public:
  double min, max;

  interval() : min(infinity), max(-infinity) {}

  interval(double min, double max) : min(min), max(max) {}

  bool containt(double x) const { return min <= x && x <= max; }

  bool surrounds(double x) const { return min < x && x < max; }

  double clamp(double x) const {
    if (x < min) {
      return min;
    }
    if (x > max) {
      return max;
    }

    return x;
  }

  double size() const { return max - min; }

  static const interval empty, universe;
};


#endif // !INTERVAL_H
