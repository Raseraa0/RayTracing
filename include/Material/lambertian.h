#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material/material.h"
#include "Texture/texture.h"

class lambertian : public material {
private:
  shared_ptr<texture> tex;

public:
  lambertian(const color& a);
  lambertian(shared_ptr<texture> t);

  bool scatter(const ray& r, const hit_record& rec, color& attenuation,
               ray& scattered) const override;
};

#endif // !LAMBERTIAN_H
