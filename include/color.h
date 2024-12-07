#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3;

// Fonction qui permet d'écrire un pixel de couleur sur un sortie
// On suppose ici que le pixel de couleur contient des valeur entre 0 et 1
void write_color(std::ostream &out, const color &pixel_color);

#endif // !COLOR_H
