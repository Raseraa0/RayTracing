#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

#include "Texture/texture.h"

class solid_color : public texture {
public:

  solid_color(color a);
  solid_color(double r, double g, double b);

  color value(double u, double v, const point3& p) const override;

private:
  color albedo;
};

#endif // !SOLID_COLOR_H
