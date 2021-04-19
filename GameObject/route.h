#ifndef GAMEOBJECT_ROUTE_H_
#define GAMEOBJECT_ROUTE_H_

#include <cmath>

#include "dynamic_object.h"
#include "point.h"

class Route {
 public:
  Route(const Point& start, const Point& finish);
  Route(const Route& route) = default;

  Point GetNext();
  bool HasFinished() const;

 private:
  const Point start_point_;
  const Point finish_point_;

  Point current_point_;
};

#endif  // GAMEOBJECT_ROUTE_H_
