#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "hittable.h"
#include "ray.h"

// Classe abstraite des materiaux
class material {
public:
  int id = 0;

  virtual ~material() = default;

  virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation,
                       ray& scattered) const;
};

// Classe des matériaux lambertian
class lambertian : public material {
private:
  color albedo;

public:
  lambertian(const color& a);

  bool scatter(const ray& r, const hit_record& rec, color& attenuation,
               ray& scattered) const;
};

// Classe pour le métal
class metal : public material {
private:
  color albedo;
  double fuzz;

public:
  metal(const color& a, double f);

  bool scatter(const ray& r, const hit_record& rec, color& attenuation,
               ray& scattered) const;
};

// Classe pour le verre
class dielectric : public material {
private:
  double reflexion_index;

  static double reflectance(double cos_theta, double refraction_index);

public:
  int id = 1;

  dielectric(double r);

  bool scatter(const ray& r, const hit_record& rec, color& attenuation,
               ray& scattered) const;
};

#endif // !MATERIAL_H
