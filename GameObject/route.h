#ifndef ROUTE_H_
#define ROUTE_H_

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

#endif  // ROUTE_H_
