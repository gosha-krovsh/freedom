#ifndef GAMEOBJECT_COORDINATES_H_
#define GAMEOBJECT_COORDINATES_H_

struct Coordinates {
  Coordinates(double x, double y, double z = 0);

  double GetIsometricX() const;
  double GetIsometricY() const;

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

  double x;
  double y;
  double z;
};

#endif  // GAMEOBJECT_COORDINATES_H_
