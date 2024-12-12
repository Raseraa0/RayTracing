#include "ray.h"


// Constructeurs
ray::ray() {}
ray::ray(const point3& o, const vec3& d) : orig(o), dir(d), tm(0) {}
ray::ray(const point3& o, const vec3& d, double t) : orig(o), dir(d), tm(t) {}

// getteur
const point3& ray::origin() const { return orig; }
const point3& ray::direction() const { return dir; }
double ray::time() const { return tm; }

// calcul d'un point sur le ray
point3 ray::at(double t) const { return orig + t * dir; }
