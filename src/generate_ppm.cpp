#include <iostream>

int main() {

  int width = 1000;
  int height = 2000;

  // P3 est pour l'encodage des couleur
  std::cout << "P3" << std::endl;

  // On doit indiquer les dimension de l'image au début
  std::cout << width << " " << height << std::endl;

  // Ensuite on indique la valeur max
  std::cout << "255" << std::endl;

  int R;
  int G;
  int B;

  std::clog << "Début de la génération de l'image" << std::endl;
  for (int j = 0; j < height; j++) {
    std::clog << "Génération de la ligne " << j << std::endl;
    for (int i = 0; i < width; i++) {

      R = int(double(i) / width * 255);
      G = 0;
      B = int(double(j) / height * 255);

      std::cout << R << " " << G << " " << B << std ::endl;
    }
  }
  std::clog << "Fin de la génération de l'image" << std::endl;
}
