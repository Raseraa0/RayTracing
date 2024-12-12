#include "Utilities/interval.h"
#include "Utilities/utils.h"
#include <cmath>

interval::interval() : min(utils::infinity), max(-utils::infinity) {}

interval::interval(double m1, double m2) : min(m1), max(m2) {}

interval::interval(interval i1, interval i2) {
  min = std::fmin(i1.min, i2.min);
  max = std::fmax(i1.max, i2.max);
}

bool interval::containt(double x) const { return min <= x && x <= max; }

bool interval::surrounds(double x) const { return min < x && x < max; }

double interval::clamp(double x) const {
  if (x < min) {
    return min;
  }
  if (x > max) {
    return max;
  }

  return x;
}

interval interval::expand(double delta) const {
  double padding = delta / 2;
  return interval(min - padding, max + padding);
}

double interval::size() const { return max - min; }

const interval interval::empty = interval(utils::infinity, -utils::infinity);
const interval interval::universe = interval(-utils::infinity, utils::infinity);
