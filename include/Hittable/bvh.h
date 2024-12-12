#ifndef BVH_H
#define BVH_H

#include "Hittable/hittable.h"
#include "Hittable/hittable_list.h"
#include "aabb.h"
#include <cstddef>
#include <memory>
#include <vector>

using std::shared_ptr;

class bvh_node : public hittable {
public:
  bvh_node(hittable_list l);

  bvh_node(std::vector<shared_ptr<hittable>>, size_t start, size_t end);

  bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

  aabb bounding_box() const override;

private:
  aabb bbox;
  shared_ptr<hittable> left;
  shared_ptr<hittable> right;


  static bool box_compare(const shared_ptr<hittable> h1, const shared_ptr<hittable> h2, int axis);
  static bool box_compare_x(const shared_ptr<hittable> h1, const shared_ptr<hittable> h2);
  static bool box_compare_y(const shared_ptr<hittable> h1, const shared_ptr<hittable> h2);
  static bool box_compare_z(const shared_ptr<hittable> h1, const shared_ptr<hittable> h2);
};

#endif // !BVH_H
