
#include "Hittable/bvh.h"
#include "Hittable/hittable_list.h"
#include "Hittable/sphere.h"
#include "Material/dielectric.h"
#include "Material/lambertian.h"
#include "Material/metal.h"
#include "Texture/checker_texture.h"
#include "Utilities/utils.h"
#include "Utilities/vec3.h"
#include "camera.h"
#include "Scenes/scene.h"
#include <cmath>
#include <memory>

using std::make_shared;
// using std::shared_ptr;

void scene::boucing_sphere() {
  hittable_list world;

  // srand((unsigned)time(0));

  auto checked_ground = make_shared<checker_texture>(0.3, color(0.1, 0.1, 0.1),
                                                     color(1, 0.2, 0.1));
  auto ground_material = make_shared<lambertian>(checked_ground);
  world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = utils::random_double();
      point3 center(a + 0.9 * utils::random_double(), 0.2,
                    b + 0.9 * utils::random_double());

      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        shared_ptr<material> sphere_material;

        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = color::random() * color::random();
          sphere_material = make_shared<lambertian>(albedo);
          point3 center2 = center + vec3(0, utils::random_double(0, 0.5), 0);
          world.add(make_shared<sphere>(center, center2, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = color::random(0.5, 1);
          auto fuzz = utils::random_double(0, 0.5);
          sphere_material = make_shared<metal>(albedo, fuzz);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = make_shared<dielectric>(1.5);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = make_shared<dielectric>(1.5);
  world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

  auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
  world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

  auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
  world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

  camera cam;

  cam.ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.sample_per_pixel = 50;
  cam.max_depth = 50;

  cam.vfov = 20;
  cam.lookfrom = point3(13, 2, 3);
  cam.lookat = point3(0, 0, 0);
  cam.vup = vec3(0, 1, 0);

  cam.defocus_angle = 0.6;
  cam.focus_distance = 10.0;

  world = hittable_list(make_shared<bvh_node>(world));

  cam.render(world);
}
