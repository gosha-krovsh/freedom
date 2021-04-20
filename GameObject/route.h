#ifndef GAMEOBJECT_ROUTE_H_
#define GAMEOBJECT_ROUTE_H_

#include <cmath>

#include "dynamic_object.h"
#include "point.h"

class Route {
 public:
  Route(const Point& start, const Point& finish);
  Point GetNext();
  bool HasFinished() const;

 private:
  const Point start_;
  const Point finish_;

  Point current_;
};

#endif  // GAMEOBJECT_ROUTE_H_
