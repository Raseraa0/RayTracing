#include "../include/material.h"

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


lambertian::lambertian(const color& a) : albedo(a){};

metal::metal(const color& a, double f) : albedo(a), fuzz(f){};


bool lambertian::scatter(const ray& r, const hit_record& rec,
                         color& attenuation, ray& scattered) const {

  (void)r;

  vec3 scattered_direction = rec.normal + random_unit_vector();

  if (scattered_direction.near_zero()) {
    scattered_direction = rec.normal;
  }

  scattered = ray(rec.p, scattered_direction);
  attenuation = albedo;
  return true;
}

bool metal::scatter(const ray& r, const hit_record& rec, color& attenuation,
                    ray& scattered) const {
  vec3 scattered_direction = reflect(r.direction(), rec.normal);
  scattered_direction = unit_vector(scattered_direction) + fuzz * random_unit_vector();

  scattered = ray(rec.p, scattered_direction);
  attenuation = albedo;
  return dot(scattered_direction,rec.normal) > 0;
}
