#include "color.h"
#include "Utilities/interval.h"
#include <iostream>

// Fonction qui permet d'écrire un pixel de couleur sur un sortie
// On suppose ici que le pixel de couleur contient des valeur entre 0 et 1
void coloration::write_color(std::ostream& out, const color& pixel_color) {

  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();

  r = coloration::linear_to_gamma(r);
  g = coloration::linear_to_gamma(g);
  b = coloration::linear_to_gamma(b);

  // On veux assurer que les valeur sont bien comprise
  // entre 0 inclue et 256 exclu

  static const interval intensity = interval(0, 0.999);
  int rbyte = int(256 * intensity.clamp(r));
  int gbyte = int(256 * intensity.clamp(g));
  int bbyte = int(256 * intensity.clamp(b));

  out << rbyte << " " << gbyte << " " << bbyte << std::endl;
}
