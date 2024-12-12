#include "aabb.h"

aabb::aabb() {}

aabb::aabb(const interval& xx, const interval& yy, const interval& zz)
    : x(xx), y(yy), z(zz) {}

aabb::aabb(const point3& p1, const point3& p2) {
  x = p1.x() < p2.x() ? interval(p1.x(), p2.x()) : interval(p2.x(), p1.x());
  y = p1.y() < p2.y() ? interval(p1.y(), p2.y()) : interval(p2.y(), p1.y());
  z = p1.z() < p2.z() ? interval(p1.z(), p2.z()) : interval(p2.z(), p1.z());
}

aabb::aabb(const aabb& a1, const aabb& a2) {
  x = interval(a1.x, a2.x);
  y = interval(a1.y, a2.y);
  z = interval(a1.z, a2.z);
}

const interval& aabb::get_interval(int n) const {
  if (n == 0) {
    return x;
  }
  if (n == 1) {
    return y;
  }
  if (n == 2) {
    return z;
  }
  return interval::empty;
}

bool aabb::hit(const ray& r, interval ray_t) const {
  const point3& ray_origine = r.origin();
  const vec3& ray_direction = r.direction();

  for (int index_axis = 0; index_axis < 3; index_axis++) {
    const interval ax = get_interval(index_axis);
    const double adinv = 1.0 / ray_direction[index_axis];

    double t0 = (ax.min - ray_origine[index_axis]) * adinv;
    double t1 = (ax.max - ray_origine[index_axis]) * adinv;

    if (t0 < t1) {
      if (t0 > ray_t.min) {
        ray_t.min = t0;
      }
      if (t1 < ray_t.max) {
        ray_t.max = t1;
      }
    } else {
      if (t1 > ray_t.min) {
        ray_t.min = t1;
      }
      if (t0 < ray_t.max) {
        ray_t.max = t0;
      }
    }

    if (ray_t.max <= ray_t.min) {
      return false;
    }
  }

  return true;
}

int aabb::longest_axis() const {
  if (x.size() > y.size()) {
    return x.size() > z.size() ? 0 : 2;
  } else {
    return y.size() > z.size() ? 1 : 2;
  }
}

const aabb aabb::empty = aabb(interval::empty,interval::empty,interval::empty);
const aabb aabb::universe = aabb(interval::universe,interval::universe,interval::universe);
