#include "coordinates.h"

Coordinates::Coordinates(double x, double y, double z) : x(x), y(y), z(z) {}

double Coordinates::GetIsometricX() const {
  return (y - x);
}

double Coordinates::GetIsometricY() const {
  return (x + y)/2. - z;
}
