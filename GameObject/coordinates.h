#ifndef GAMEOBJECT_COORDINATES_H_
#define GAMEOBJECT_COORDINATES_H_

struct Coordinates {
  Coordinates(double x, double y, double z);

  double GetIsometricX() const;
  double GetIsometricY() const;

  double x;
  double y;
  double z;
};

#endif  // GAMEOBJECT_COORDINATES_H_
