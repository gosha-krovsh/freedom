#include "coordinates.h"

Coordinates::Coordinates(double x, double y, double z) : x(x), y(y), z(z) {}

double Coordinates::GetIsoX() const {
  return (y - x);
}

double Coordinates::GetIsoY() const {
  return (x + y)/2. - z;
}
