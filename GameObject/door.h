#ifndef GAMEOBJECT_DOOR_H_
#define GAMEOBJECT_DOOR_H_

#include <memory>

#include "object.h"
#include "animator.h"

class Door : public Object {
 public:
  using State = bool;

  Door(const Point& coords, const std::weak_ptr<QPixmap>& image, Type type);

  void Tick(int current_tick) override;
  void Interact(const InteractingObject& interacting_object) override;
  Point GetDrawOffset() const override;

 private:
  State GetState() const;
  void SetDrawOffset();
  bool IsObjectVeryClose(double object_x, double object_y) const;

 private:
  Animator<State> animator_{GetState()};
  bool is_opened_{false};
  Point draw_offset_{0, 0};
};

#endif  // GAMEOBJECT_DOOR_H_
