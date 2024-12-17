#include "Texture/checker_texture.h"
#include "Texture/solid_color.h"

checker_texture::checker_texture(double scale, shared_ptr<texture> o,
                                 shared_ptr<texture> e)
    : inv_scale(1.0 / scale), odd(o), even(e) {}

checker_texture::checker_texture(double scale, const color& o, const color& e)
    : checker_texture(scale, make_shared<solid_color>(o),
                      make_shared<solid_color>(e)) {}

color checker_texture::value(double u, double v, const point3& p) const {

  int valX = int(std::floor(inv_scale * p.x()));
  int valY = int(std::floor(inv_scale * p.y()));
  int valZ = int(std::floor(inv_scale * p.z()));

  bool isEven = (valX + valY + valZ) % 2 == 0;

  return isEven ? even->value(u, v, p) : odd->value(u, v, p);
}
