#ifndef GAMEOBJECT_DYNAMIC_OBJECT_H_
#define GAMEOBJECT_DYNAMIC_OBJECT_H_

#include <cmath>

#include "object.h"

class DynamicObject : public Object {
 public:
  DynamicObject(Coordinates coords, const QPixmap& image);

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

  ViewDirection GetViewDirection() const;
  void SetViewDirection(ViewDirection view_direction);
  void SetMovingDirection(bool left, bool up, bool right, bool down);
  Coordinates GetSpeedMultipliers() const;
  double GetSpeed() const;


  ViewDirection ConvertVectorToViewDirection(int h, int v);

  void Move();
  bool IsMoving() const;
  void SetMoving(bool flag);

  void Tick(int current_tick) override;

 private:
  double speed_{ constants::kSpeed };
  ViewDirection view_direction_{ ViewDirection::kDown };
  bool is_moving_{ false };
};

#endif  // GAMEOBJECT_DYNAMIC_OBJECT_H_
