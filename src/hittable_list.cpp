#include "hittable_list.h"

hittable_list::hittable_list() {}

hittable_list::hittable_list(shared_ptr<hittable> elem) { add(elem); }

// Fonction qui ajoute un élément à la liste
void hittable_list::add(shared_ptr<hittable> elem) { array.push_back(elem); }

// Fonction qui supprime tout ce qu'il y a dans la liste
void hittable_list::clear() { array.clear(); }

bool hittable_list::hit(const ray& r, interval ray_t, hit_record& rec) const {
  hit_record temp_rec;
  bool hit_anything = false;
  double ray_tmax_aux = ray_t.max;

  for (const shared_ptr<hittable>& elem : array) {

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
