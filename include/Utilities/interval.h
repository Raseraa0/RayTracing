#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
public:
  double min, max;

  interval();

  interval(double m1, double m2);

  interval(interval i1, interval i2);

  bool containt(double x) const;

  bool surrounds(double x) const;

  double clamp(double x) const;

  interval expand(double delta) const;

  double size() const;

  static const interval empty, universe;
};


#endif // !INTERVAL_H
