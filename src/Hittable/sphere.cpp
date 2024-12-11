#include "Hittable/sphere.h"

sphere::sphere(const point3& c, double r, shared_ptr<material> m)
    : center(c), radius(std::fmax(0, r)) {
  // TODO initialiser mat
  mat = m;
}

bool sphere::hit(const ray& r, interval ray_t, hit_record& rec) const {

  // résolu par un système
  vec3 aux = center - r.origin();
  double a = r.direction().length_squarred();
  double h = geometry::dot(r.direction(), aux);
  double c = aux.length_squarred() - radius * radius;
  double discr = h * h - a * c;

  if (discr < 0) {
    return false;
  }

  double discr_squarred = std::sqrt(discr);

  double root = (h - discr_squarred) / a;

  // la première racine est la plus proche, si elle est dans l'intervall:
  // super sinon on regarde si la deuxième, un peu plus loin est dans
  // l'intervalle
  if (!ray_t.surrounds(root)) {

    root = (h + discr_squarred) / a;
    if (!ray_t.surrounds(root)) {
      return false;
    }
  }

  rec.t = root;
  rec.p = r.at(root);
  vec3 outward_normal = (rec.p -center) / radius;
  rec.set_face_normal(r, outward_normal);
  rec.mat = mat;

  return true;
}
