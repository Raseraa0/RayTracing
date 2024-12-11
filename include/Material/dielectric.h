#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material/material.h"

class dielectric : public material {
private:
  double reflexion_index;

  static double reflectance(double cos_theta, double refraction_index);

public:
  int id = 1;

  dielectric(double r);

  bool scatter(const ray& r, const hit_record& rec, color& attenuation,
               ray& scattered) const;
};

#endif // !DIELECTRIC_H
