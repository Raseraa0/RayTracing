#ifndef METAL_H
#define METAL_H

#include "Material/material.h"

class metal : public material {
private:
  color albedo;
  double fuzz;

public:
  metal(const color& a, double f);

  bool scatter(const ray& r, const hit_record& rec, color& attenuation,
               ray& scattered) const override;
};

#endif // !METAL_H
