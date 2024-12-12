#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "Utilities/interval.h"
#include "ray.h"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
private:
  std::vector<shared_ptr<hittable>> array;

public:
  hittable_list();

  hittable_list(shared_ptr<hittable> elem);

  // Fonction qui ajoute un élément à la liste
  void add(shared_ptr<hittable> elem);

  // Fonction qui supprime tout ce qu'il y a dans la liste
  void clear();

  bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};
#endif // !HITTABLE_LIST_H
