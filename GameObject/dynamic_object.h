#ifndef GAMEOBJECT_DYNAMIC_OBJECT_H_
#define GAMEOBJECT_DYNAMIC_OBJECT_H_

#include <cmath>

#include "object.h"

class DynamicObject : public Object {
 public:
  enum class ViewDirection {
    kRight,
    kUpRight,
    kUp,
    kUpLeft,
    kLeft,
    kDownLeft,
    kDownRight,
    kDown,
  };

 public:
  DynamicObject(const Point& coords, const QPixmap& image);

  void Tick(int current_tick) override;

  ViewDirection GetViewDirection() const;
  void UpdateMovement(bool left, bool up, bool right, bool down);


 private:
  void UpdateSpeedVector(Point iso_vector);
  void UpdateViewDirection();
  void Move();

 private:
  double speed_value_{constants::kSpeed};
  Point speed_vector_{0, 0};
  ViewDirection view_direction_{ViewDirection::kDown};
};

#endif  // GAMEOBJECT_DYNAMIC_OBJECT_H_
