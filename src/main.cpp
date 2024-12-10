#include "../include/camera.h"
#include "../include/hittable_list.h"
#include "../include/sphere.h"
#include "../include/vec3.h"

#include <cmath>
#include <memory>

using std::make_shared;
using std::shared_ptr;

// Main
int main() {

  // Description des objets
  hittable_list world;

  shared_ptr<material> material_ground =
      make_shared<lambertian>(color(0.8, 0.8, 0.0));
  shared_ptr<material> material_center =
      make_shared<lambertian>(color(0.1, 0.2, 0.5));
  shared_ptr<material> material_left =
      make_shared<metal>(color(0.8, 0.8, 0.8), 0);
  shared_ptr<material> material_right =
      make_shared<metal>(color(0.8, 0.6, 0.2), 0.05);

  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
  world.add(make_shared<sphere>(point3(0, -0, -1.2), 0.5, material_center));
  world.add(make_shared<sphere>(point3(-1, 0, -1), 0.5, material_left));
  world.add(make_shared<sphere>(point3(1, -0, -1), 0.5, material_right));

  camera cam;
  cam.ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.sample_per_pixel = 500;
  cam.max_depth = 50;

  cam.render(world);
  return 0;
}
