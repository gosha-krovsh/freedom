#ifndef GAMEOBJECT_DYNAMIC_OBJECT_H_
#define GAMEOBJECT_DYNAMIC_OBJECT_H_

#include <cmath>

#include "object.h"

class DynamicObject : public Object {
 public:
  enum class ViewDirection {
    kUp,
    kUpRight,
    kRight,
    kDownRight,
    kDown,
    kDownLeft,
    kLeft,
    kUpLeft,
  };

 public:
  DynamicObject(const Coordinates& coords, const QPixmap& image);

  void Tick(int current_tick) override;

  ViewDirection GetViewDirection() const;
  void SetMovingDirection(bool left, bool up, bool right, bool down);


 private:
  bool IsMoving() const;
  void SetMoving(bool flag);
  void SetViewDirection(ViewDirection view_direction);
  void SetViewDirection(int h, int v);
  Coordinates GetSpeedVector() const;
  void Move();

 private:
  bool is_moving_{false};
  ViewDirection view_direction_{ViewDirection::kDown};
  double speed_{constants::kSpeed};
};

#endif  // GAMEOBJECT_DYNAMIC_OBJECT_H_
