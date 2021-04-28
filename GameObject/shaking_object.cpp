#include "shaking_object.h"

void ShakingObject::Shake(const Point& direction_of_shake) {
  direction_of_shake_ = direction_of_shake;
  direction_of_shake_.Normalize();
  direction_of_shake_ *= constants::kShakeAmplitude;
  is_shaking_ = true;
}

void ShakingObject::Tick(int current_tick) {
  if (is_shaking_) {
    if (tick_begin_of_shake_ == -1) {
      tick_begin_of_shake_ = current_tick;
    }

    int delta_tick = current_tick - tick_begin_of_shake_;
    if (delta_tick >= constants::kDurationOfShaking) {
      is_shaking_ = false;
      tick_begin_of_shake_ = -1;
    } else {
      int sign = (delta_tick >= (constants::kDurationOfShaking / 2)) ? -1 : 1;
      offset_ += sign * direction_of_shake_;
    }
  }
}

Point ShakingObject::GetOffset() const {
  return offset_;
}
