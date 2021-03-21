#ifndef GAMEOBJECT_DYNAMIC_OBJECT_H_
#define GAMEOBJECT_DYNAMIC_OBJECT_H_

#include <cmath>

#include "object.h"

class DynamicObject : public Object {
 public:
  // The order is important for |UpdateViewDirection()|.
  enum class ViewDirection {
    kDownLeft = 0,
    kLeft = 1,
    kUpLeft = 2,
    kDown = 3,
    kUp = 5,
    kDownRight = 6,
    kRight = 7,
    kUpRight = 8,
  };

 public:
  DynamicObject(const Point& coords, const QPixmap& image);

  void Tick(int current_tick) override;

  ViewDirection GetViewDirection() const;


 protected:
  void UpdateViewDirection(const Point& screen_vector);

 private:
  void Move();

 protected:
  double speed_value_{constants::kSpeed};
  Point speed_vector_{0, 0};
  ViewDirection view_direction_{ViewDirection::kDown};
};

#endif  // GAMEOBJECT_DYNAMIC_OBJECT_H_
