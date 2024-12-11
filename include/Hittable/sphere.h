#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"
#include "vec3.h"
#include <memory>

using std::shared_ptr;

class sphere : public hittable {
private:
  point3 center;
  double radius;
  shared_ptr<material> mat;

public:
  sphere(const point3& c, double r, shared_ptr<material> m);

  bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};
#endif // !SPHERE_H
