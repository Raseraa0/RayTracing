#include "Material/material.h"
#include <cmath>

// par defaut on va dire qu'on renvoie just false
bool material::scatter(const ray& r, const hit_record& rec, color& attenuation,
                       ray& scattered) const {
  // problème de variable inutilisées
  (void)r;
  (void)rec;
  (void)attenuation;
  (void)scattered;
  return false;
}
