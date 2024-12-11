#include "material.h"
#include <cmath>

// par defaut on va dire qu'on renvoie just false
bool material::scatter(const ray& r, const hit_record& rec, color& attenuation,
                       ray& scattered) const {
  // problème de variable inutilisées
  (void)r;
  (void)rec;
  (void)attenuation;
  (void)scattered;
  return false;
}

lambertian::lambertian(const color& a) : albedo(a) {};

metal::metal(const color& a, double f) : albedo(a), fuzz(f) {};

dielectric::dielectric(double r) : reflexion_index(r) {};

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

bool metal::scatter(const ray& r, const hit_record& rec, color& attenuation,
                    ray& scattered) const {
  vec3 scattered_direction = geometry::reflect(r.direction(), rec.normal);
  scattered_direction =
      geometry::unit_vector(scattered_direction) + fuzz * geometry::random_unit_vector();

  scattered = ray(rec.p, scattered_direction);
  attenuation = albedo;
  return geometry::dot(scattered_direction, rec.normal) > 0;
}

bool dielectric::scatter(const ray& r, const hit_record& rec,
                         color& attenuation, ray& scattered) const {
  attenuation = color(1.0, 1.0, 1.0);

  // cela nous permet de savoir si on est dans l'air et arrive dans la matière
  // ou si on est dans la matière et que l'on sort dans l'air
  double ri = rec.front_face ? (1.0 / reflexion_index) : reflexion_index;

  vec3 direction_unit = geometry::unit_vector(r.direction());
  double cos_theta = std::fmin(geometry::dot(-direction_unit, rec.normal), 1.0);
  double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

  // Cette condition est du au loi de snell descarts
  bool cant_refract = ri * sin_theta > 1.0;

  vec3 direction;

  if (cant_refract) {
    direction = geometry::reflect(direction_unit, rec.normal);
  } else {
    direction = geometry::refract(direction_unit, rec.normal, ri);
  }

  scattered = ray(rec.p, direction);

  return true;
}

// Juste une formule qui utilise une approximation polynomiale
double dielectric::reflectance(double cos_theta, double refraction_index) {
  double r0 = (1 - refraction_index) / (1 + refraction_index);
  r0 = r0 * r0;
  return r0 + (1 - r0) * std::pow((1 - cos_theta), 5);
}
