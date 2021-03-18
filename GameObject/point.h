#ifndef GAMEOBJECT_POINT_H_
#define GAMEOBJECT_POINT_H_

#include <cmath>

// Representation of 3D point in Cartesian coordinate system.
// It also can be used as a vector with the beginning at the origin.
class Point {
 public:
  Point(double x, double y, double z = 0);

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

  bool operator==(const Point& rhs) const;
  bool operator!=(const Point& rhs) const;

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

 public:
  double x{0};
  double y{0};
  double z{0};
};

#endif  // GAMEOBJECT_POINT_H_
