#ifndef RAY_H
#define RAY_H

#include "Utilities/vec3.h"

class ray {
  // Attribut privées
private:
  point3 orig;
  vec3 dir;

public:
  // Constructeurs
  ray();
  ray(const point3& o, const vec3& d);

  // getteur
  const point3& origin() const; 
  const point3& direction() const; 

  // calcul d'un point sur le ray
  point3 at(double t) const; 
};

#endif // !RAY_H
