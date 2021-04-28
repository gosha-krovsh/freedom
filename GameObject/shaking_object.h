#ifndef GAMEOBJECT_SHAKING_OBJECT_H_
#define GAMEOBJECT_SHAKING_OBJECT_H_

#include "point.h"

class ShakingObject {
 public:
  void Tick(int current_tick);
  void Shake(const Point& direction_of_shake);

  Point GetOffset() const;

 private:
  Point offset_{0, 0};
  int tick_begin_of_shake_{-1};
  bool is_shaking_{false};
  Point direction_of_shake_{0, 0};
};

#endif  // GAMEOBJECT_SHAKING_OBJECT_H_
