
#include "Hittable/bvh.h"
#include "Hittable/hittable.h"
#include "Hittable/hittable_list.h"
#include "Utilities/utils.h"
#include "aabb.h"
#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>

//TODO peut etre un jour rajouter un consctructeur avec left et right, car c'est pas mal si l'utilisateur peut lui meme definir les bound

bvh_node::bvh_node(hittable_list l) : bvh_node(l.array, 0, l.array.size()) {}

bvh_node::bvh_node(std::vector<shared_ptr<hittable>> array, size_t start,
                   size_t end) {


  // askip mieux de faire sans random... mais pas pour moi :p
  int choosed_axis = utils::random_int(0, 2);

  // comparator est de type fonction ici
  auto comparator = (choosed_axis == 0)   ? box_compare_x
                    : (choosed_axis == 1) ? box_compare_y
                                          : box_compare_z;

  size_t size = end - start;

  // si un seul élement, on le duplique afin de ne pas avoir de truc vide
  if (size == 1) {
    left = array[start];
    right = array[start];
  }
  // si deux élement, on en met un dans chaqun
  else if (size == 2) {
    left = array[start];
    right = array[start + 1];
  }
  // sinon, on sort puis on met la moitié dans chaque côté
  else {

    // Ces deux ligne sont infame mais pas le choix our pas avoir de warning du
    // au changement de type
    auto start_sort =
        std::begin(array) +
        static_cast<std::vector<std::shared_ptr<hittable>>::difference_type>(
            start);
    auto end_sort =
        std::begin(array) +
        static_cast<std::vector<std::shared_ptr<hittable>>::difference_type>(
            end);

    std::sort(start_sort, end_sort, comparator);
    size_t mid = start + size / 2;
    left = make_shared<bvh_node>(array, start, mid);
    right = make_shared<bvh_node>(array, mid, end);
  }

  bbox = aabb(left->bounding_box(), right->bounding_box());
}

bool bvh_node::hit(const ray& r, interval ray_t, hit_record& rec) const {

  // Si je ne touche pas la box de toute facon c'est mort
  if (!bbox.hit(r, ray_t)) {
    return false;
  }

  // Sinon je procède par récurtion sur mes deux enfant
  bool hit_left = left->hit(r, ray_t, rec);
  interval new_interval(ray_t.min, hit_left ? rec.t : ray_t.max);
  bool hit_right = right->hit(r, new_interval, rec);

  return hit_left || hit_right;
}

aabb bvh_node::bounding_box() const { return bbox; }

bool bvh_node::box_compare(const shared_ptr<hittable> h1,
                           const shared_ptr<hittable> h2, int axis) {
  interval i1 = h1->bounding_box().get_interval(axis);
  interval i2 = h2->bounding_box().get_interval(axis);
  return i1.min < i2.min;
}

bool bvh_node::box_compare_x(const shared_ptr<hittable> h1,
                             const shared_ptr<hittable> h2) {
  return box_compare(h1, h2, 0);
}

bool bvh_node::box_compare_y(const shared_ptr<hittable> h1,
                             const shared_ptr<hittable> h2) {
  return box_compare(h1, h2, 1);
}

bool bvh_node::box_compare_z(const shared_ptr<hittable> h1,
                             const shared_ptr<hittable> h2) {
  return box_compare(h1, h2, 2);
}
