#include "../include/camera.h"
#include "../include/material.h"
#include "../include/utils.h"
#include <ostream>

// Renvoie la couleur touché par ce rayon
color camera::ray_color(const ray& r, int depth, const hittable& world) {

  // juste une limite pour pas que la fonction récursive explose
  if (depth <= 0) {
    return color(0, 0, 0);
  }

  color white(1, 1, 1);
  color blue(0.2, 0.4, 1);

  hit_record rec;
  if (world.hit(r, interval(0.001, infinity), rec)) {

    ray scattered;
    color attenuation;
    if (rec.mat->scatter(r, rec, attenuation, scattered)) {

      // if (rec.mat->id == 1){
      //    std::clog << "" << std::endl;
      //  }
      return attenuation * ray_color(scattered, depth - 1, world);
    }

    return color(0, 0, 0);
  }

  vec3 unit = unit_vector(r.direction());
  double a = 0.5 * (unit.y() + 1);
  return (1 - a) * white + a * blue;
}

// Permet de mettre a jour tout les parametres de la camera
void camera::initialize() {

  pixel_sample_scale = 1.0 / sample_per_pixel;

  // Définition de la largeur et de la hauteur de l'image
  image_height = int(image_width / ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // Paramètres liés à la caméra
  // la longueur de focal est la distance entre l'oeil et l'écran
  // le camera center représente l'oeil
  camera_center = lookfrom;

  // Définition de la largeur et de la hauteur du viewport
  double theta = degrees_to_radians(vfov);
  double h = std::tan(theta / 2);
  double viewport_height = 2 * h * focus_distance;
  double viewport_width =
      viewport_height * (double(image_width) / image_height);

  w = unit_vector(lookfrom - lookat);
  u = unit_vector(cross(vup, w));
  v = cross(w, u);

  // Vecteur qui parcours la largeur et la hauteur du viewport
  // On suppose le coin en haut a gauche le point de départ
  // l'axe x est la largeur (u)
  // l'axe y est la hauteur (v)
  // l'axe z est la profondeur (w)
  vec3 viewport_u = viewport_width * u;
  vec3 viewport_v = viewport_height * -v;

  // Vecteur qui représente la ditance entre le centre de chaque pixel
  pixel_delta_u = viewport_u / image_width;
  pixel_delta_v = viewport_v / image_height;

  // calcul du coin et du pixel tout en haut a gauche (donc le tout premier
  // pixel)
  point3 viewport_upper_left =
      camera_center - focus_distance * w - viewport_v / 2 - viewport_u / 2;
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_v + pixel_delta_u);

  double defocus_ratio =
      focus_distance * std::tan(degrees_to_radians(defocus_angle / 2));

  defocus_disk_u = defocus_ratio * u;
  defocus_disk_v = defocus_ratio * v;
}

ray camera::get_ray(int i, int j) const {
  vec3 offset = sample_square();

  point3 pixel_sample_loc = pixel00_loc + ((i + offset.x()) * pixel_delta_u) +
                            ((j + offset.y()) * pixel_delta_v);

  point3 ray_origin =
      defocus_angle <= 0 ? camera_center : defocus_disk_sample();

  vec3 ray_direction = pixel_sample_loc - ray_origin;

  return ray(ray_origin, ray_direction);
}

// return une position random sur un carré de 1 sur 1 centré en 0
vec3 camera::sample_square() const {
  return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

void camera::render(const hittable& world) {

  initialize();

  // Entete du fichier PPM
  std::cout << "P3" << std::endl
            << image_width << " " << image_height << std::endl
            << "255" << std::endl;

  std::clog << "Début du Render..." << std::endl;
  for (int j = 0; j < image_height; j++) {

    int percentage = static_cast<int>((j + 1) * 100.0 / image_height);
    std::clog << "\rProgression : " << percentage << "%" << std::flush;

    for (int i = 0; i < image_width; i++) {

      color pixel_color(0, 0, 0);
      for (int sample = 0; sample < sample_per_pixel; sample++) {
        ray r = get_ray(i, j);
        pixel_color += ray_color(r, max_depth, world);
      }

      write_color(std::cout, pixel_color * pixel_sample_scale);
    }
  }
  std::clog << "\nFin du Render !!!" << std::endl;
}

point3 camera::defocus_disk_sample() const {
  vec3 p = random_on_unit_disk();
  return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}
