#include "Utilities/vec3.h"
#include "Utilities/utils.h"

vec3::vec3(double x, double y, double z) : vector{x, y, z} {}
vec3::vec3() : vector{0, 0, 0} {}

// Getteur
double vec3::x() const { return vector[0]; }
double vec3::y() const { return vector[1]; }
double vec3::z() const { return vector[2]; }

// Overload d'opérateur
vec3 vec3::operator-() const {
  return vec3(-vector[0], -vector[1], -vector[2]);
}

double vec3::operator[](int i) const {
  return vector[i];
} // Pour les cas mon_int = mon_vec[1]

double& vec3::operator[](int i) {
  return vector[i];
} // Pour les cas mon_vec[1] = mon_int

vec3& vec3::operator+=(const vec3& other) {
  vector[0] += other.vector[0];
  vector[1] += other.vector[1];
  vector[2] += other.vector[2];
  return *this;
}

vec3& vec3::operator-=(const vec3& other) { return *this += (-other); }

vec3& vec3::operator*=(double val) {
  vector[0] *= val;
  vector[1] *= val;
  vector[2] *= val;
  return *this;
}

vec3& vec3::operator/=(double val) { return *this *= 1 / val; }

// Calcul de la longueur du vecteur
double vec3::length() const { return std::sqrt(length_squarred()); }

double vec3::length_squarred() const {
  return vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2];
}

bool vec3::near_zero() const {
  double s = 1e-8;
  return (std::fabs(vector[0]) < s && std::fabs(vector[1]) < s &&
          std::fabs(vector[2]) < s);
}

// C'est surement + compliqué que ca mais on va dire je privilégie static
// quand c'est utilisé dans la classe et inline quand c'est utilisé en dehors
// de la classe
vec3 vec3::random() {
  return vec3(utils::random_double(), utils::random_double(), utils::random_double());
}

vec3 vec3::random(double min, double max) {
  return vec3(utils::random_double(min, max), utils::random_double(min, max),
              utils::random_double(min, max));
}
