#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "interval.h"
#include "hittable.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
private:
  std::vector<shared_ptr<hittable>> array;

public:
  hittable_list() {}

  hittable_list(shared_ptr<hittable> elem) { add(elem); }

  // Fonction qui ajoute un élément à la liste
  void add(shared_ptr<hittable> elem) { array.push_back(elem); }

  // Fonction qui supprime tout ce qu'il y a dans la liste
  void clear() { array.clear(); }

  bool hit(const ray& r,interval ray_t,
           hit_record& rec) const override {
    hit_record temp_rec;
    bool hit_anything = false;
    double ray_tmax_aux = ray_t.max;

    for (const shared_ptr<hittable> elem : array) {

      // On cherche entre le min et le max
      // Puis on cherche entre le min et la distance de l'object le plus proche
      // déjà trouvé
      if (elem->hit(r, interval(ray_t.min, ray_tmax_aux), temp_rec)) {
        rec = temp_rec;
        ray_tmax_aux = rec.t;
        hit_anything = true;
      }
    }
    return hit_anything;
  }
};
#endif // !HITTABLE_LIST_H
