#include "../include/color.h"
#include <iostream>

// Fonction qui permet d'écrire un pixel de couleur sur un sortie
// On suppose ici que le pixel de couleur contient des valeur entre 0 et 1
void write_color(std::ostream &out, const color &pixel_color) {

  int r = int(255.999 * pixel_color.x());
  int g = int(255.999 * pixel_color.y());
  int b = int(255.999 * pixel_color.z());

  out << r << " " << g << " " << b << std::endl;
}

