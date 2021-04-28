#include "wall.h"

Wall::Wall(const Point& coords, const std::weak_ptr<QPixmap>& image)
  : Object(coords, image),
    Destroyable(constants::kHP) {
  type_ = Type::kWall;
}

void Wall::Tick(int current_tick) {
  Object::Tick(current_tick);

  ProcessShaking(current_tick);
}

void Wall::OnDead() {
  is_touchable_ = false;
  delete_on_next_tick_ = true;
}

void Wall::Shake(const Point& direction_of_shake) {
  direction_of_shake_ = direction_of_shake;
  is_shaking_ = true;
}

void Wall::ProcessShaking(int current_tick) {
  if (is_shaking_) {
    if (tick_begin_of_shake_ == -1) {
      tick_begin_of_shake_ = current_tick;
    }

    int delta_tick = current_tick - tick_begin_of_shake_;
    if (delta_tick >= constants::kDurationOfWallShaking) {
      is_shaking_ = false;
      tick_begin_of_shake_ = -1;
    } else {
      int sign =
          (delta_tick >= (constants::kDurationOfWallShaking / 2)) ? -1 : 1;
      SetX(GetX() + sign * direction_of_shake_.x * constants::kShakeAmplitude);
      SetY(GetY() + sign * direction_of_shake_.y * constants::kShakeAmplitude);
    }
  }
}

void Wall::Interact(const InteractingObject& interacting_object) {
  DecreaseHP(interacting_object.GetAttack());

  Point direction_of_shake{GetRoundedX() - interacting_object.GetRoundedX(),
                           GetRoundedY() - interacting_object.GetRoundedY()};
  Shake(direction_of_shake);
}
