#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable.h"
#include "vec3.h"

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

private:
  int image_height;
  point3 camera_center;
  point3 pixel00_loc;
  vec3 pixel_delta_v;
  vec3 pixel_delta_u;
  double pixel_sample_scale;
  vec3 u, v, w; // Ce sont les vecteur qui constitue la base de la camera

  // Renvoie la couleur touché par ce rayon
  color ray_color(const ray& r, int depth, const hittable& world);

  // Permet de mettre a jour tout les parametres de la camera
  void initialize();

  ray get_ray(int i, int j) const;

  // return une position random sur un carré de 1 sur 1 centré en 0
  vec3 sample_square() const;

public:
  void render(const hittable& world);
};

#endif // !CAMERA_H
