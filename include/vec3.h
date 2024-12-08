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
  vec3(double x, double y, double z) : vector{x, y, z} {}
  vec3() : vector{0, 0, 0} {}

  // Getteur
  double x() const { return vector[0]; }
  double y() const { return vector[1]; }
  double z() const { return vector[2]; }

  // Overload d'opérateur
  vec3 operator-() const { return vec3(-vector[0], -vector[1], -vector[2]); }

  double operator[](int i) const {
    return vector[i];
  } // Pour les cas mon_int = mon_vec[1]

  double& operator[](int i) {
    return vector[i];
  } // Pour les cas mon_vec[1] = mon_int

  vec3& operator+=(const vec3& other) {
    vector[0] += other.vector[0];
    vector[1] += other.vector[1];
    vector[2] += other.vector[2];
    return *this;
  }

  vec3& operator-=(const vec3& other) { return *this += (-other); }

  vec3& operator*=(double val) {
    vector[0] *= val;
    vector[1] *= val;
    vector[2] *= val;
    return *this;
  }

  vec3& operator/=(double val) { return *this *= 1 / val; }

  // Calcul de la longueur du vecteur
  double length() const { return std::sqrt(length_squarred()); }

  double length_squarred() const {
    return vector[0] * vector[0] + vector[1] * vector[1] +
           vector[2] * vector[2];
  }

  static vec3 random() {
    return vec3(random_double(), random_double(), random_double());
  }

  static vec3 random(double min, double max) {
    return vec3(random_double(min, max), random_double(min, max),
                random_double(min, max));
  }
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

#endif // !VEC3_H
