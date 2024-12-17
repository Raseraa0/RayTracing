#include "Material/lambertian.h"
#include "Texture/solid_color.h"

lambertian::lambertian(const color& a)
    : tex(std::make_shared<solid_color>(a)) {};

lambertian::lambertian(shared_ptr<texture> t) : tex(t) {}

bool lambertian::scatter(const ray& r, const hit_record& rec,
                         color& attenuation, ray& scattered) const {

  (void)r;

  vec3 scattered_direction = rec.normal + geometry::random_unit_vector();

  if (scattered_direction.near_zero()) {
    scattered_direction = rec.normal;
  }

  scattered = ray(rec.p, scattered_direction, r.time());
  attenuation = tex->value(rec.u, rec.v, rec.p);
  return true;
}
