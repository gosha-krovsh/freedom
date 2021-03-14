#include "coordinates.h"

Coordinates::Coordinates(double x, double y, double z) : x(x), y(y), z(z) {}

double Coordinates::GetIsometricX() const {
  return (y - x);
}

double Coordinates::GetIsometricY() const {
  return (x + y) / 2. - z;
}

Coordinates& Coordinates::operator+=(const Coordinates& rhs) {
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}

Coordinates operator+(Coordinates lhs, const Coordinates& rhs) {
  lhs += rhs;
  return lhs;
}

Coordinates& Coordinates::operator*=(double rhs) {
  x *= rhs;
  y *= rhs;
  z *= rhs;
  return *this;
}

Coordinates operator*(Coordinates lhs, double rhs) {
  lhs *= rhs;
  return lhs;
}

Coordinates operator*(double lhs, Coordinates rhs) {
  rhs *= lhs;
  return rhs;
}

Coordinates& Coordinates::operator-=(const Coordinates& rhs) {
  *this = -(*this);
  return *this;
}

Coordinates Coordinates::operator+() const {
  return *this;
}

Coordinates Coordinates::operator-() const {
  return Coordinates({-x, -y, -z});
}

Coordinates& Coordinates::operator/=(double rhs) {
  *this *= (1 / rhs);
  return *this;
}

Coordinates operator-(Coordinates lhs, const Coordinates& rhs) {
  lhs -= rhs;
  return lhs;
}

Coordinates operator/(Coordinates lhs, double rhs) {
  lhs /= rhs;
  return lhs;
}

Coordinates operator/(double lhs, Coordinates rhs) {
  rhs /= lhs;
  return rhs;
}
