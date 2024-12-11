#include "../include/camera.h"
#include "../include/hittable_list.h"
#include "../include/sphere.h"
#include "../include/vec3.h"

#include <cmath>
#include <memory>

using std::make_shared;
// using std::shared_ptr;

// Main
int main() {

  // Description des objets
  hittable_list world;

  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_solid = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_metal = make_shared<metal>(color(0.8, 0.8, 0.8), 0);
  auto material_dielectric_outer = make_shared<dielectric>(1.50);
  auto material_dielectric_inner = make_shared<dielectric>(1.00 / 1.50);

  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
  world.add(make_shared<sphere>(point3(0, -0, -1.2), 0.5, material_solid));
  world.add(make_shared<sphere>(point3(1, 0, -1), 0.5, material_metal));
  world.add(
      make_shared<sphere>(point3(-1, -0, -1), 0.5, material_dielectric_outer));
  world.add(
      make_shared<sphere>(point3(-1, -0, -1), 0.4, material_dielectric_inner));

  camera cam;
  cam.ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.sample_per_pixel = 100;
  cam.max_depth = 50;

  cam.vfov = 50;
  cam.lookfrom = point3(0, 0, 1);
  cam.lookat = point3(0, 0, -1);
  cam.vup = vec3(0, 1, 0);

  cam.defocus_angle = 10;
  cam.focus_distance = 2;

  cam.render(world);
  return 0;
}
