#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class sphere : public hittable {
private:
  point3 center;
  double radius;

public:
  sphere(const point3& center, double radius)
      : center(center), radius(std::fmax(0, radius)) {}

  bool hit(const ray& r, double ray_tmin, double ray_tmax,
           hit_record& rec) const override {

    // résolu par un système
    vec3 aux = center - r.origin();
    double a = r.direction().length_squarred();
    double h = dot(r.direction(), aux);
    double c = aux.length_squarred() - radius * radius;
    double discr = h * h - a * c;

    if (discr < 0) {
      return false;
    }

    double discr_squarred = std::sqrt(discr);

    double root = (h - discr_squarred) / a;

    // Si la première racine n'est pas dans l'interval accepté
    if (root <= ray_tmin || root >= ray_tmax) {

      root = (h + discr_squarred) / a;
      // Si la deuxième racine n'est pas dans l'interval accepté
      if (root <= ray_tmin || root >= ray_tmax) {
        return false;
      }
    }

    rec.t = root;
    rec.p = r.at(root);
    rec.normal = (rec.p - center) / radius;

    return true;
  }
};
#endif // !SPHERE_H
