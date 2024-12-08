#ifndef HITTABLE_H
#define HITTABLE_H

#include "interval.h"
#include "ray.h"
#include "vec3.h"

// Classe qui va servir a enregistré des données
class hit_record {
public:
  point3 p;
  double t;
  vec3 normal;
  bool front_face; 

  // Pour des raison pratique, le vecteur normal doit toujours
  // aller à l'encontre du rayo
  void set_face_normal(const ray& r, const vec3& outward_normal){
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : - outward_normal;
  }
};

class hittable {
public:
  // Destructeur: comportement par defaut donné par le programme
  virtual ~hittable() = default;

  // Methode virtuel qui doit raccourci vima ller au debtu du paragrapheforcément être overide (du au =0)
  virtual bool hit(const ray& r, interval ray_t,
                   hit_record& rec) const = 0;
};

#endif // !HITTABLE_H
