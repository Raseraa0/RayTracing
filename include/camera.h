#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable.h"
#include "utils.h"
#include "vec3.h"

class camera {
public:
  int image_width = 100;
  double ratio = 1.0;
  int sample_per_pixel = 10;
  int max_depth = 10;

private:
  int image_height;
  point3 camera_center;
  point3 pixel00_loc;
  vec3 pixel_delta_v;
  vec3 pixel_delta_u;
  double pixel_sample_scale;

  // Renvoie la couleur touché par ce rayon
  color ray_color(const ray& r, int depth, const hittable& world) {

    // just une limite pour pas que la fonction récursive explose
    if (depth <= 0) {
      return color(0, 0, 0);
    }

    color white = color(1, 1, 1);
    color blue = color(0.2, 0.4, 1);

    hit_record rec;
    if (world.hit(r, interval(0.001, infinity), rec)) {
      // Le rayon qui touche une surface est alors réfléchie, et donc il renvoie
      // ce qui est touché par le rayon réfléchie
      vec3 reflexion_direction = random_on_hemisphere(rec.normal);
      return 0.5 * ray_color(ray(rec.p, reflexion_direction), depth - 1, world);
    }

    vec3 unit = unit_vector(r.direction());
    double a = 0.5 * (unit.y() + 1);
    return (1 - a) * white + a * blue;
  }

  // Permet de mettre a jour tout les parametres de la camera
  void initialize() {

    pixel_sample_scale = 1.0 / sample_per_pixel;

    // Définition de la largeur et de la hauteur de l'image
    image_height = int(image_width / ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Définition de la largeur et de la hauteur du viewport
    double viewport_height = 2.0;
    double viewport_width =
        viewport_height * (double(image_width) / image_height);

    // Paramètres liés à la caméra
    // la longueur de focal est la distance entre l'oeil et l'écran
    // le camera center représente l'oeil
    double focal_length = 1;
    camera_center = point3(0, 0, 0);

    // Vecteur qui parcours la largeur et la hauteur du viewport
    // On suppose le coin en haut a gauche le point de départ
    // l'axe x est la largeur
    // l'axe y est la hauteur
    // l'axe z est la profondeur
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Vecteur qui représente la ditance entre le centre de chaque pixel
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // calcul du coin et du pixel tout en haut a gauche (donc le tout premier
    // pixel)
    point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) -
                                 viewport_v / 2 - viewport_u / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_v + pixel_delta_u);
  }

  ray get_ray(int i, int j) const {
    vec3 offset = sample_square();

    point3 pixel_sample_loc = pixel00_loc + ((i + offset.x()) * pixel_delta_u) +
                              ((j + offset.y()) * pixel_delta_v);

    vec3 ray_direction = pixel_sample_loc - camera_center;

    return ray(camera_center, ray_direction);
  }

  // return une position random sur un carré de 1 sur 1 centré en 0
  vec3 sample_square() const {
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
  }

public:
  void render(const hittable& world) {

    initialize();

    // Entete du fichier PPM
    std::cout << "P3" << std::endl
              << image_width << " " << image_height << std::endl
              << "255" << std::endl;

    std::clog << "Début du Render..." << std::endl;
    int step = image_height / 10;
    for (int j = 0; j < image_height; j++) {
      if (j % step == 0) {
        std::clog << "Lignes génerées : " << j / step * 10 << "%" << std::endl;
      }
      for (int i = 0; i < image_width; i++) {

        color pixel_color(0, 0, 0);
        for (int sample = 0; sample < sample_per_pixel; sample++) {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, max_depth, world);
        }

        write_color(std::cout, pixel_color * pixel_sample_scale);
      }
    }
    std::clog << "Fin du Render !!!" << std::endl;
  }
};

#endif // !CAMERA_H
