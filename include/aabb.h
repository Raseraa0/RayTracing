#ifndef AABB_H
#define AABB_H

#include "Utilities/interval.h"
#include "ray.h"

class aabb {
public:
  interval x, y, z;

  aabb();

  aabb(const interval& xx, const interval& yy, const interval& zz);

  aabb(const point3& p1, const point3& p2);

  aabb(const aabb& a1, const aabb& a2);


  const interval& get_interval(int n) const;
  
  bool hit(const ray& r, interval ray_t) const;

  int longest_axis() const;

  static const aabb empty, universe;
};

#endif // !AABB_H
