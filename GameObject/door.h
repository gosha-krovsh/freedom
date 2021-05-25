#ifndef GAMEOBJECT_DOOR_H_
#define GAMEOBJECT_DOOR_H_

#include <memory>

#include "object.h"
#include "animator.h"

class Door : public Object {
 public:
  enum kDoorPolicy {
    kOpenable,
    kLocked,
  };
  using State = bool;

  Door(const Point& coords, const std::weak_ptr<QPixmap>& image, Type type);

  void Tick(int current_tick) override;
  void Interact(const InteractingObject& interacting_object) override;

  int GetPolicy() override;
  void SetPolicy(int policy) override;

  Point GetDrawOffset() const override;
  bool IsOpenable();
  void SetOpenable(bool openable);

  State GetState() const;

 private:
  void SetDrawOffset();
  bool IsObjectVeryClose(double object_x, double object_y) const;

 private:
  Animator<State> animator_{GetState()};
  bool is_opened_{false};
  bool is_openalbe_{true};
  Point draw_offset_{0, 0};
  kDoorPolicy policy_{kOpenable};
};

#endif  // GAMEOBJECT_DOOR_H_
