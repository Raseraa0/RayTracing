#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material/material.h"

class lambertian : public material {
private:
  color albedo;

public:
  lambertian(const color& a);

  bool scatter(const ray& r, const hit_record& rec, color& attenuation,
               ray& scattered) const;
};

#endif // !LAMBERTIAN_H
