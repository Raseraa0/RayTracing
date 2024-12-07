#include "../include/color.h"
#include "../include/ray.h"
#include "../include/vec3.h"
#include <ostream>

// Fonction booleenne qui renvoie true sur le rayon touche
// la sphere dont on done le centre et le rayon
bool hit_sphere(const point3& center, double radius, const ray& r) {
  // calcul basé sur la résolution d'un système
  vec3 aux = center - r.origin();
  double a = dot(r.direction(), r.direction());
  double b = -2 * dot(r.direction(), aux);
  double c = dot(aux, aux) - radius * radius;
  double discr = b * b - 4 * a * c;
  return discr >= 0;
}

color ray_color(const ray& r) {

  color white = color(1, 1, 1);
  color blue = color(0, 0, 1);
  color red = color(1, 0, 0);

  if (hit_sphere(point3(0, 0, -1), 0.5, r)) {
    return red;
  }

  vec3 unit = unit_vector(r.direction());
  double a = 0.5 * (unit.y() + 1);
  return (1 - a) * white + a * blue;
}

int main() {

  // Définition de la largeur et de la hauteur de l'image
  double ratio = 16.0 / 9.0;
  int image_width = 400;

  int image_height = int(image_width / ratio);
  image_height = image_height < 1 ? 1 : image_height;

  // Définition de la largeur et de la hauteur du viewport
  int viewport_height = 2.0;
  int viewport_width = viewport_height * (double(image_width) / image_height);

  // Paramètres liés à la caméra
  // la longueur de focal est la distance entre l'oeil et l'écran
  // le camera center représente l'oeil
  double focal_length = 1.0;
  point3 camera_center = point3(0, 0, 0);

  // Vecteur qui parcours la largeur et la hauteur du viewport
  // On suppose le coin en haut a gauche le point de départ
  // l'axe x est la largeur
  // l'axe y est la hauteur
  // l'axe z est la profondeur
  vec3 viewport_u = vec3(viewport_width, 0, 0);
  vec3 viewport_v = vec3(0, -viewport_height, 0);

  // Vecteur qui représente la ditance entre le centre de chaque pixel
  vec3 pixel_delta_u = viewport_u / image_width;
  vec3 pixel_delta_v = viewport_v / image_height;

  // calcul du coin et du pixel tout en haut a gauche (donc le tout premier
  // pixel)
  point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) -
                               viewport_v / 2 - viewport_u / 2;
  point3 pixel00_loc =
      viewport_upper_left + pixel_delta_v / 2 + pixel_delta_u / 2;

  // Entete du fichier PPM
  std::cout << "P3" << std::endl
            << image_width << " " << image_height << std::endl
            << "255" << std::endl;

  std::clog << "Début de la génération de l'image" << std::flush;
  for (int j = 0; j < image_height; j++) {
    std::clog << "Génération de la ligne " << j << std::endl;
    for (int i = 0; i < image_width; i++) {

      point3 current_pixel_center =
          pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      vec3 ray_direction = current_pixel_center - camera_center;
      ray r = ray(camera_center, ray_direction);

      color pixel_color = ray_color(r);

      write_color(std::cout, pixel_color);
    }
  }
  std::clog << "Fin de la génération de l'image" << std::endl;
  return 0;
}
