#include "../include/color.h"

int main() {

  int width = 128;
  int height = 128;

  // P3 est pour l'encodage des couleur
  std::cout << "P3" << std::endl;

  // On doit indiquer les dimension de l'image au début
  std::cout << width << " " << height << std::endl;

  // Ensuite on indique la valeur max
  std::cout << "255" << std::endl;

  double R;
  double G;
  double B;

  std::clog << "Début de la génération de l'image" << std::endl;
  for (int j = 0; j < height; j++) {
    std::clog << "Génération de la ligne " << j << std::endl;
    for (int i = 0; i < width; i++) {

      R = double(i) / width;
      G = 0;
      B = double(j) / height;

      color pixel_color = color(R, G, B);
      write_color(std::cout, pixel_color);
    }
  }
  std::clog << "Fin de la génération de l'image" << std::endl;
}
