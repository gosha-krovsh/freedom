#ifndef GAMEOBJECT_SHAKING_OBJECT_H_
#define GAMEOBJECT_SHAKING_OBJECT_H_

#include "point.h"

class ShakingObject {
 public:
  void Tick(int current_tick);
  void Shake(const Point& direction_of_shake);

  void SetOffset(const Point& offset);
  Point GetOffset() const;

 private:
  Point offset_{0, 0};
  int remaining_shaking_ticks{0};
  Point direction_of_shake_{0, 0};
};

#endif  // GAMEOBJECT_SHAKING_OBJECT_H_
