#ifndef TEXTURE_H
#define TEXTURE_H

#include "color.h"

class texture {
public:
  virtual ~texture() = default;

  virtual color value(double u, double v, const point3& p) const = 0;
};

#endif // !TEXTURE_H
