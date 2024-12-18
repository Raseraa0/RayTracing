#ifndef CAMERA_H
#define CAMERA_H

#include "Hittable/hittable.h"
#include "color.h"
#include "Utilities/vec3.h"

class camera {
public:
  int image_width = 100;
  double ratio = 1.0;
  int sample_per_pixel = 10;
  int max_depth = 10;

  double vfov = 90;
  point3 lookfrom = point3(0, 0, 0);
  point3 lookat = point3(0, 0, -1);
  vec3 vup = vec3(0, 1, 0);

  double defocus_angle = 0;
  double focus_distance = 10;

private:
  int image_height;
  point3 camera_center;
  point3 pixel00_loc;
  vec3 pixel_delta_v;
  vec3 pixel_delta_u;
  double pixel_sample_scale;
  vec3 u, v, w; // Ce sont les vecteur qui constitue la base de la camera
  vec3 defocus_disk_u;
  vec3 defocus_disk_v;

  // Renvoie la couleur touché par ce rayon
  color ray_color(const ray& r, int depth, const hittable& world);

  // Permet de mettre a jour tout les parametres de la camera
  void initialize();

  ray get_ray(int i, int j) const;

  // return une position random sur un carré de 1 sur 1 centré en 0
  vec3 sample_square() const;

  // return le point de départ situé dans le disque autour de la camera
  point3 defocus_disk_sample() const;

public:
  void render(const hittable& world);
};

#endif // !CAMERA_H
