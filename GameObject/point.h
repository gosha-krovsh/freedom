#ifndef GAMEOBJECT_POINT_H_
#define GAMEOBJECT_POINT_H_

#include <QString>

#include <cmath>
#include <string>

#include "Model/constants.h"

// Representation of 3D point in Cartesian coordinate system.
// It also can be used as a vector with the beginning at the origin.
class Point {
 public:
  class HashFunc {
   public:
    long double operator()(const Point& point) const {
      return 29 * point.x + 31 * point.y + 37 * point.z;
    }
  };

 public:
  Point() = default;
  Point(double x, double y, double z = 0);
  Point(int x, int y, int z = 0);

  Point GetRounded() const;

  // Transform point from users screen to Cartesian point.
  static Point FromScreenPoint(const Point& screen_point);

  double GetIsometricX() const;
  double GetIsometricY() const;

  // Returns |true| if the point has (0, 0, 0) coordinates.
  bool IsNull() const;

  // Returns the length of the vector.
  double GetMagnitude() const;

  // Makes vector have a magnitude of |new_magnitude|.
  void ClampMagnitude(double new_magnitude);

  // Makes vector have a magnitude of 1.
  void Normalize();

  // Rotates the coordinates in the XY-plane through an |angle| in degrees
  // about the origin of a 2-dimensional Cartesian coordinate system.
  void Rotate(double angle);

  double SquaredDistanceFrom(const Point& other) const;
  double DistanceFrom(const Point& other) const;

  bool operator==(const Point& rhs) const;
  bool operator!=(const Point& rhs) const;

  bool operator<(const Point& rhs) const;
  bool operator<=(const Point& rhs) const;
  bool operator>(const Point& rhs) const;
  bool operator>=(const Point& rhs) const;

  Point operator+() const;
  Point operator-() const;
  Point& operator+=(const Point& rhs);
  Point& operator-=(const Point& rhs);
  Point& operator*=(double rhs);
  Point& operator/=(double rhs);
  friend Point operator+(Point lhs, const Point& rhs);
  friend Point operator-(Point lhs, const Point& rhs);
  friend Point operator*(Point lhs, double rhs);
  friend Point operator*(double lhs, Point rhs);
  friend Point operator/(Point lhs, double rhs);
  friend Point operator/(double lhs, Point rhs);

  QString ToString() const;

 public:
  double x{0};
  double y{0};
  double z{0};
};

#endif  // GAMEOBJECT_POINT_H_
