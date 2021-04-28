#ifndef GAMEOBJECT_WALL_H_
#define GAMEOBJECT_WALL_H_

#include <memory>

#include "shaking_object.h"
#include "destroyable.h"
#include "object.h"

class Wall : public Object, public Destroyable, public ShakingObject {
 public:
  explicit Wall(const Point& coords);
  void Tick(int current_tick) override;
  void OnDead() override;

  static void SetImage(const std::shared_ptr<QPixmap>& image);
  static void DeleteImage();

  void Interact(const InteractingObject& interacting_object) override;

  Point GetDrawOffset() const override;

 private:
  static std::shared_ptr<QPixmap> wall_image_;

  int tick_begin_of_shake_{-1};
  bool is_shaking_{false};
  Point direction_of_shake_{0, 0};
};

#endif  // GAMEOBJECT_WALL_H_
