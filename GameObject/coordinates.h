#ifndef GAMEOBJECT_COORDINATES_H_
#define GAMEOBJECT_COORDINATES_H_

#include <cmath>

struct Coordinates {
  Coordinates(double x, double y, double z = 0);

  double GetIsometricX() const;
  double GetIsometricY() const;

  double GetLength() const;

  bool operator==(const Coordinates& rhs) const;
  bool operator!=(const Coordinates& rhs) const;

  Coordinates operator+() const;
  Coordinates operator-() const;
  Coordinates& operator+=(const Coordinates& rhs);
  Coordinates& operator-=(const Coordinates& rhs);
  Coordinates& operator*=(double rhs);
  Coordinates& operator/=(double rhs);
  friend Coordinates operator+(Coordinates lhs, const Coordinates& rhs);
  friend Coordinates operator-(Coordinates lhs, const Coordinates& rhs);
  friend Coordinates operator*(Coordinates lhs, double rhs);
  friend Coordinates operator*(double lhs, Coordinates rhs);
  friend Coordinates operator/(Coordinates lhs, double rhs);
  friend Coordinates operator/(double lhs, Coordinates rhs);

  double x{0};
  double y{0};
  double z{0};
};

#endif  // GAMEOBJECT_COORDINATES_H_
