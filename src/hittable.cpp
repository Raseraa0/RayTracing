
#include "../include/hittable.h"

// Pour des raison pratique, le vecteur normal doit toujours
// aller à l'encontre du rayo
void hit_record::set_face_normal(const ray& r, const vec3& outward_normal) {
  front_face = dot(r.direction(), outward_normal) < 0;
  normal = front_face ? outward_normal : -outward_normal;
}
