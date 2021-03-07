#ifndef GAMEOBJECT_COORDINATES_H_
#define GAMEOBJECT_COORDINATES_H_

struct Coordinates {
  Coordinates(double x, double y, double z);

  double x;
  double y;
  double z;

  double GetIsoX() const;
  double GetIsoY() const;
};

#endif  // GAMEOBJECT_COORDINATES_H_
