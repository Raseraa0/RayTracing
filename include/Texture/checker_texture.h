#ifndef CHECKER_TEXTURE_H
#define CHECKER_TEXTURE_H

#include "Texture/texture.h"
#include <memory>

using std::shared_ptr;
using std::make_shared;

class checker_texture : public texture {
public:
  checker_texture(double scale, shared_ptr<texture> o, shared_ptr<texture> e);
  checker_texture(double scale, const color& o, const color& e);

  color value(double u, double v, const point3& p) const override;

private:
  double inv_scale;
  shared_ptr<texture> odd;
  shared_ptr<texture> even;
};

#endif // !CHECKER_TEXTURE_H
