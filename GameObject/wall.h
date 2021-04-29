#ifndef GAMEOBJECT_WALL_H_
#define GAMEOBJECT_WALL_H_

#include <memory>

#include "destroyable.h"
#include "object.h"

class Wall : public Object, public Destroyable {
 public:
  explicit Wall(const Point& coords, const std::weak_ptr<QPixmap>& image);
  void Tick(int current_tick) override;
  void OnDead() override;

  void Shake(const Point& direction_of_shake);

  void Interact(const InteractingObject& interacting_object) override;

 private:
  void ProcessShaking(int current_tick);

 private:
  int tick_begin_of_shake_{-1};
  bool is_shaking_{false};
  Point direction_of_shake_{0, 0};
};

#endif  // GAMEOBJECT_WALL_H_
