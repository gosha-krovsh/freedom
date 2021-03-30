#ifndef ROUTE_H_
#define ROUTE_H_

#include "coordinates.h"

class Route {
 public:
  Route(const Coordinates& start, const Coordinates& finish);
  Route(const Route& route) = default;

  Coordinates GetNext();
  bool HasFinished() const;

 private:
  const Coordinates start_point_;
  const Coordinates finish_point_;

  Coordinates current_point_;
};

#endif  // ROUTE_H_
