#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

class sphere : public hittable {
private:
  point3 center;
  double radius;

public:
  sphere(const point3& c, double r);

  bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};
#endif // !SPHERE_H
