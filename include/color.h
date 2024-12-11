#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <cmath>
#include <iostream>

using color = vec3;

namespace coloration {

// Fonction qui permet d'écrire un pixel de couleur sur un sortie
// On suppose ici que le pixel de couleur contient des valeur entre 0 et 1
void write_color(std::ostream& out, const color& pixel_color);

inline double linear_to_gamma(double x) {
  if (x > 0) {
    return std::sqrt(x);
  }
  return 0;
}
} // namespace color

#endif // !COLOR_H
