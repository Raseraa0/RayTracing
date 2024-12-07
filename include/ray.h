#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
  // Attribut privées
private:
  point3 orig;
  vec3 dir;

public:
  // Constructeurs
  ray() {}
  ray(const point3& orig, const vec3& dir) : orig(orig), dir(dir) {}

  // getteur
  const point3& origin() const { return orig; }
  const point3& direction() const { return dir; }

  // calcul d'un point sur le ray
  point3 at(double t) const { return orig + t * dir; }
};

#endif // !RAY_H
