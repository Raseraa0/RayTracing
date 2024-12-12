#ifndef UTILS_H
#define UTILS_H

// Ici je définirai des constante utile

#include <cstdlib>
#include <limits>

namespace utils {

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) { return degrees * pi / 180; }

inline double random_double() { return std::rand() / (RAND_MAX + 1.0); }

inline double random_double(double min, double max) {
  return min + (max - min) * random_double();
}

inline int random_int(int min, int max) {
  return int(random_double(min, max + 1));
}

} // namespace utils

#endif // !UTILS_H
