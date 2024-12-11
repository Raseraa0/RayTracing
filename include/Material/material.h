#ifndef MATERIAL_H
#define MATERIAL_H

#include "Hittable/hittable.h"
#include "color.h"
#include "ray.h"

class material {
public:
  int id = 0;

  virtual ~material() = default;

  virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation,
                       ray& scattered) const;
};

#endif // !MATERIAL_H
