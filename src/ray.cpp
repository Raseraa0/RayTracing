#include "ray.h"


// Constructeurs
ray::ray() {}
ray::ray(const point3& o, const vec3& d) : orig(o), dir(d) {}

// getteur
const point3& ray::origin() const { return orig; }
const point3& ray::direction() const { return dir; }

// calcul d'un point sur le ray
point3 ray::at(double t) const { return orig + t * dir; }
