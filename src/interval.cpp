#include "interval.h"
#include "utils.h"

interval::interval() : min(utils::infinity), max(-utils::infinity) {}

interval::interval(double m1, double m2) : min(m1), max(m2) {}

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

double interval::size() const { return max - min; }

const interval interval::empty = interval(utils::infinity, -utils::infinity);
const interval interval::universe = interval(-utils::infinity, utils::infinity);
