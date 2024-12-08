#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "vec3.h"

// Classe qui va servir a enregistré des données
class hit_record {
public:
  point3 p;
  double t;
  vec3 normal;
};

class hittable {
public:
  // Destructeur: comportement par defaut donné par le programme
  virtual ~hittable() = default;

  // Methode virtuel qui doit forcément être overide (du au =0)
  virtual bool hit(const ray& r, double ray_tmin, double ray_tmax,
                   hit_record& rec) const = 0;
};

#endif // !HITTABLE_H
