#ifndef SPHERE_H
#define SPHERE_H

#include "aabb.h"
#include "hittable.h"
#include "ray.h"
#include <memory>

using std::shared_ptr;

class sphere : public hittable {
private:
  ray center;
  double radius;
  shared_ptr<material> mat;
  aabb bbox;

public:
  sphere(const point3& c, double r, shared_ptr<material> m);

  sphere(const point3& c1, const point3& c2, double r, shared_ptr<material> m);

  bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

  virtual aabb bounding_box() const override;
};
#endif // !SPHERE_H
