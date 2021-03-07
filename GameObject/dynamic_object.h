#ifndef GAMEOBJECT_DYNAMIC_OBJECT_H_
#define GAMEOBJECT_DYNAMIC_OBJECT_H_

#include <cmath>

#include "object.h"

enum ViewDirection {
  kUp,
  kUpRight,
  kRight,
  kDownRight,
  kDown,
  kDownLeft,
  kLeft,
  kUpLeft,
};

class DynamicObject : public Object {
 public:
  explicit DynamicObject(Coordinates coords, const QPixmap& image);

  ViewDirection GetViewDirection() const;
  void SetViewDirection(ViewDirection view_direction);
  double GetSpeed() const;

  void Move();
  bool IsMoving() const;
  void SetMoving(bool flag);

 private:
  double speed_{ constants::kSpeed };
  ViewDirection view_direction_{kDown };
  bool is_moving_{ false };
};

#endif  // GAMEOBJECT_DYNAMIC_OBJECT_H_
