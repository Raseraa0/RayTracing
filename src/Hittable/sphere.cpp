#include "Hittable/sphere.h"

// Constructeur pour une sphere static
sphere::sphere(const point3& c, double r, shared_ptr<material> m)
    : center(c, vec3(0, 0, 0)), radius(std::fmax(0, r)), mat(m) {

  vec3 half_diagonal = vec3(radius, radius, radius);
  bbox = aabb(c + half_diagonal, c - half_diagonal);
}

// Constructeur pour une sphere dynammic
sphere::sphere(const point3& c1, const point3& c2, double r,
               shared_ptr<material> m)
    : center(c1, c2 - c1), radius(std::fmax(0, r)), mat(m) {

  vec3 half_diagonal = vec3(radius, radius, radius);

  aabb bbox1 = aabb(c1 + half_diagonal, c1 - half_diagonal);
  aabb bbox2 = aabb(c2 + half_diagonal, c2 - half_diagonal);

  bbox = aabb(bbox1, bbox2);
}

bool sphere::hit(const ray& r, interval ray_t, hit_record& rec) const {

  // résolu par un système
  point3 current_center = center.at(r.time());
  vec3 aux = current_center - r.origin();
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
  vec3 outward_normal = (rec.p - current_center) / radius;
  rec.set_face_normal(r, outward_normal);
  rec.mat = mat;

  return true;
}

aabb sphere::bounding_box() const { return bbox; }
