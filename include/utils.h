#ifndef UTILS_H
#define UTILS_H

// Ici je définirai des constante utile

#include <limits>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) { return degrees * pi / 180; }

#endif // !UTILS_H
