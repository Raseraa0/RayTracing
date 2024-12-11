#ifndef VEC3_H
#define VEC3_H

#include "utils.h"
#include <cmath>
#include <iostream>
class vec3 {
public:
  // Le vecteur
  double vector[3];

  // Constructeurs
  vec3(double x, double y, double z);
  vec3();

  // Getteur
  double x() const;
  double y() const;
  double z() const;

  // Overload d'opérateur
  vec3 operator-() const;

  double operator[](int i) const; // Pour les cas mon_int = mon_vec[1]

  double& operator[](int i); // Pour les cas mon_vec[1] = mon_int

  vec3& operator+=(const vec3& other);

  vec3& operator-=(const vec3& other);

  vec3& operator*=(double val);

  vec3& operator/=(double val);

  // Calcul de la longueur du vecteur
  double length() const;

  double length_squarred() const;

  bool near_zero() const;

  // C'est surement + compliqué que ca mais on va dire je privilégie static
  // quand c'est utilisé dans la classe et inline quand c'est utilisé en dehors
  // de la classe
  static vec3 random();

  static vec3 random(double min, double max);
};

// C'est juste un alias, pour que le code soit plus claire à lire
using point3 = vec3;

// Définition d'équivalent de "méthode static" sauf que c'est directement
// remplacé à la compilation

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
  return out << "(" << v[0] << "," << v[1] << "," << v[2] << ")";
}

inline vec3 operator+(const vec3& v1, const vec3& v2) {
  return vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

inline vec3 operator-(const vec3& v1, const vec3& v2) {
  return v1 + -v2;
  // return vec3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

inline vec3 operator*(const vec3& v1, const vec3& v2) {
  return vec3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

inline vec3 operator*(const vec3& v1, double val) {
  return vec3(v1[0] * val, v1[1] * val, v1[2] * val);
}

inline vec3 operator*(double val, const vec3& v1) { return v1 * val; }

inline vec3 operator/(const vec3& v1, double val) { return v1 * (1 / val); }

// Produit scalaire
inline double dot(const vec3& v1, const vec3& v2) {
  return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

// Produit vectoriel
inline vec3 cross(const vec3& v1, const vec3& v2) {
  return vec3(v1.vector[1] * v2.vector[2] - v1.vector[2] * v2.vector[1],
              v1.vector[2] * v2.vector[0] - v1.vector[0] * v2.vector[2],
              v1.vector[0] * v2.vector[1] - v1.vector[1] * v2.vector[0]);
}

inline vec3 unit_vector(const vec3& v) { return v / v.length(); }

inline vec3 random_unit_vector() {
  while (true) {
    vec3 v = vec3::random(-1, 1);
    double length_squarred = v.length_squarred();
    if (1e-160 < length_squarred && length_squarred < 1) {
      return v / sqrt(length_squarred);
    }
    // sinon on recommence, methode par rejection
  }
}

inline vec3 random_on_hemisphere(const vec3& normal) {

  vec3 unit_v = random_unit_vector();
  if (dot(unit_v, normal) > 0) {
    return unit_v;
  } else {
    return -unit_v;
  }
}

inline vec3 random_on_unit_disk() {
  while (true) {
    vec3 v = vec3(random_double(-1, 1), random_double(-1, 1), 0);
    if (v.length_squarred() < 1) {
      return v;
    }
  }
}

inline vec3 reflect(const vec3& v, const vec3& normal) {
  return v - 2 * dot(v, normal) * normal;
}

inline vec3 refract(const vec3& v, const vec3& normal, double coef) {
  double cos_theta = std::fmin(dot(-v, normal), 1.0);
  vec3 perp_r_out = coef * (v + cos_theta * normal);
  vec3 parall_r_out =
      -std::sqrt(std::fabs(1.0 - perp_r_out.length_squarred())) * normal;
  return parall_r_out + perp_r_out;
}

#endif // !VEC3_H
