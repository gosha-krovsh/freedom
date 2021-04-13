#ifndef GAMEOBJECT_WALL_H_
#define GAMEOBJECT_WALL_H_

#include <memory>

#include "object.h"
#include "destroyable.h"

class Wall : public Object, public Destroyable {
 public:
  explicit Wall(const Point& coords);
  void Tick(int current_tick) override;
  void OnDead() override;

  static void SetImage(std::shared_ptr<QPixmap> image);

  void Shake(const Point& direction_of_shake);

 private:
  void ProcessShaking(int current_tick);

 private:
  int tick_begin_of_shake_{-1};
  bool is_shaking_{false};
  Point direction_of_shake_{0, 0};
  static std::shared_ptr<QPixmap> wall_image_;
};

#endif  // GAMEOBJECT_WALL_H_
