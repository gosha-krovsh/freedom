#ifndef GAMEOBJECT_DYNAMIC_OBJECT_H_
#define GAMEOBJECT_DYNAMIC_OBJECT_H_

#include <cmath>
#include <utility>

#include "object.h"

class DynamicObject : public Object {
 public:
  enum class ViewDirection {
    kLeft,
    kUpLeft,
    kUp,
    kUpRight,
    kRight,
    kDownRight,
    kDown,
    kDownLeft
  };

 public:
  explicit DynamicObject(const Point& coords);

  void Tick(int current_tick) override;

  ViewDirection GetViewDirection() const;
  virtual void SetSpeedVector(const Point& speed_vector);

 protected:
  void UpdateViewDirection();

  Point speed_vector_{0, 0};
  ViewDirection view_direction_{ViewDirection::kDown};

 private:
  double GetSpeedValue() const;
  void Move();
};

#endif  // GAMEOBJECT_DYNAMIC_OBJECT_H_
