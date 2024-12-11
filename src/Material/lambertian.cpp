#include "Material/lambertian.h"

lambertian::lambertian(const color& a) : albedo(a) {};
bool lambertian::scatter(const ray& r, const hit_record& rec,
                         color& attenuation, ray& scattered) const {

  (void)r;

  vec3 scattered_direction = rec.normal + geometry::random_unit_vector();

  if (scattered_direction.near_zero()) {
    scattered_direction = rec.normal;
  }

  scattered = ray(rec.p, scattered_direction);
  attenuation = albedo;
  return true;
}
