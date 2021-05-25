#include "shaking_object.h"

void ShakingObject::Shake(const Point& direction_of_shake) {
  direction_of_shake_ = direction_of_shake;
  direction_of_shake_.Normalize();
  direction_of_shake_ *= constants::kShakeAmplitude;
  remaining_shaking_ticks = Settings::GetDurationOfShaking();
}

void ShakingObject::Tick(int) {
  if (remaining_shaking_ticks != 0) {
    int sign =
        (remaining_shaking_ticks <= (Settings::GetDurationOfShaking() / 2))
        ? -1 : 1;
    offset_ += sign * direction_of_shake_;
    --remaining_shaking_ticks;
  }
}

void ShakingObject::SetOffset(const Point& offset) {
  offset_ = offset;
}
Point ShakingObject::GetOffset() const {
  return offset_;
}
