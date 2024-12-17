#include "Texture/solid_color.h"

solid_color::solid_color(color a) : albedo(a) {}

solid_color::solid_color(double r, double g, double b)
    : albedo(color(r, g, b)) {}

color solid_color::value(double u, double v, const point3& p) const {
  (void) u;
  (void) v;
  (void) p;
  return albedo;
}
