#include "../include/hittable_list.h"
#include "../include/sphere.h"
#include "../include/vec3.h"
#include "../include/camera.h"

#include <cmath>
#include <memory>

using std::make_shared;

// Main
int main() {

  // Description des objets
  hittable_list world;
  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  camera cam;
  cam.ratio = 16.0/9.0;
  cam.image_width = 400;

  cam.render(world);
  return 0;
}