#include "wall.h"

Wall::Wall(const Point& coords) : Object(coords, wall_image_),
                                  Destroyable(constants::kHP) {}

void Wall::Tick(int current_tick) {
  Object::Tick(current_tick);

  if (is_shaking_) {
    if (tick_begin_of_shake_ == -1) {
      tick_begin_of_shake_ = current_tick;
    }

    int delta_tick = current_tick - tick_begin_of_shake_;
    if (delta_tick >= constants::kDurationOfShakingInTicks) {
      is_shaking_ = false;
      tick_begin_of_shake_ = -1;
    } else {
      int sign =
          (delta_tick >= (constants::kDurationOfShakingInTicks / 2)) ? -1 : 1;
      SetX(GetX() + sign * direction_of_shake_.x * constants::kShakeAmplitude);
      SetY(GetY() + sign * direction_of_shake_.y * constants::kShakeAmplitude);
    }
  }
}

void Wall::OnDead() {
  is_touchable_ = false;
  image_ = nullptr;
}

void Wall::SetImage(const std::shared_ptr<QPixmap>& image) {
  wall_image_ = image;
}

void Wall::Shake(const Point& direction_of_shake) {
  direction_of_shake_ = direction_of_shake;
  is_shaking_ = true;
}

std::shared_ptr<QPixmap> Wall::wall_image_;
