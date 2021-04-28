#include "point.h"

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}
Point::Point(int x, int y, int z) : Point(static_cast<double>(x),
                                          static_cast<double>(y),
                                          static_cast<double>(z)) {}

Point Point::FromScreenPoint(const Point& screen_point) {
  Point new_coords{screen_point};
  new_coords.Rotate(-135);
  return new_coords;
}

double Point::GetIsometricX() const {
  return (y - x);
}

double Point::GetIsometricY() const {
  return (x + y) / 2 - z;
}

double Point::GetMagnitude() const {
  return std::sqrt(x * x + y * y + z * z);
}

void Point::Rotate(double angle) {
  double rad_angle = angle * M_PI / 180;
  double new_x = x * std::cos(rad_angle) + y * std::sin(rad_angle);
  double new_y = - x * std::sin(rad_angle) + y * std::cos(rad_angle);
  *this = Point{new_x, new_y, z};
}

void Point::ClampMagnitude(double new_magnitude) {
  if (IsNull()) {
    return;
  }
  double coefficient = std::sqrt(new_magnitude) / GetMagnitude();
  *this *= coefficient;
}

void Point::Normalize() {
  ClampMagnitude(1);
}

bool Point::IsNull() const {
  return (*this == Point{0, 0, 0});
}

Point& Point::operator+=(const Point& rhs) {
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}

Point operator+(Point lhs, const Point& rhs) {
  lhs += rhs;
  return lhs;
}

Point& Point::operator*=(double rhs) {
  x *= rhs;
  y *= rhs;
  z *= rhs;
  return *this;
}

Point operator*(Point lhs, double rhs) {
  lhs *= rhs;
  return lhs;
}

Point operator*(double lhs, Point rhs) {
  rhs *= lhs;
  return rhs;
}

Point& Point::operator-=(const Point& rhs) {
  *this = *this + (-rhs);
  return *this;
}

Point Point::operator+() const {
  return *this;
}

Point Point::operator-() const {
  return Point({-x, -y, -z});
}

Point& Point::operator/=(double rhs) {
  *this *= (1 / rhs);
  return *this;
}

Point operator-(Point lhs, const Point& rhs) {
  lhs -= rhs;
  return lhs;
}

Point operator/(Point lhs, double rhs) {
  lhs /= rhs;
  return lhs;
}

Point operator/(double lhs, Point rhs) {
  rhs /= lhs;
  return rhs;
}

bool Point::operator==(const Point& rhs) const {
  return (std::abs(x - rhs.x) < constants::kEps &&
          std::abs(y - rhs.y) < constants::kEps &&
          std::abs(z - rhs.z) < constants::kEps);
}

bool Point::operator!=(const Point& rhs) const {
  return !(*this == rhs);
}

double Point::SquaredDistanceFrom(const Point& other) const {
  return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
}
double Point::DistanceFrom(const Point& other) const {
  return std::sqrt(SquaredDistanceFrom(other));
}

Point Point::GetRounded() const {
  return {std::round(x), std::round(y), std::round(z)};
}
