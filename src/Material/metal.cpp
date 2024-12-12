#include "Material/metal.h"


metal::metal(const color& a, double f) : albedo(a), fuzz(f) {};



bool metal::scatter(const ray& r, const hit_record& rec, color& attenuation,
                    ray& scattered) const {
  vec3 scattered_direction = geometry::reflect(r.direction(), rec.normal);
  scattered_direction =
      geometry::unit_vector(scattered_direction) + fuzz * geometry::random_unit_vector();

  scattered = ray(rec.p, scattered_direction, r.time());
  attenuation = albedo;
  return geometry::dot(scattered_direction, rec.normal) > 0;
}

