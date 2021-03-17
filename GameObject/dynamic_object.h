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

  void UpdateMoving(bool left, bool up, bool right, bool down);


 private:
  void SetViewDirection(ViewDirection view_direction);
  void SetViewDirection(Coordinates speed_vector);

  void SetSpeedVector(Coordinates coords);
  Coordinates GetSpeedVector() const;
  void Move();

 private:
  double speed_{constants::kSpeed};
  Coordinates speed_vector{0, 0};
  ViewDirection view_direction_{ViewDirection::kDown};
};

#endif  // GAMEOBJECT_DYNAMIC_OBJECT_H_
