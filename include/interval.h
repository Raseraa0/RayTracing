#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
public:
  double min, max;

  interval();

  interval(double m1, double m2);

  bool containt(double x) const;

  bool surrounds(double x) const;

  double clamp(double x) const;

  double size() const;

  static const interval empty, universe;
};

#endif // !INTERVAL_H
