#include "route.h"

Route::Route(const Point& start, const Point& finish) :
    start_(start),
    finish_(finish),
    current_(start) {}

Point Route::GetNext() {
  if (HasFinished()) {
    return finish_;
  }

  double current_speed = constants::kSpeed / (std::sqrt(2));
  if (current_.y != finish_.y) {
    if (std::abs(current_.y - finish_.y) < current_speed) {
      current_.y = finish_.y;
    } else if (current_.y < finish_.y) {
      current_.y += current_speed;
    } else {
      current_.y -= current_speed;
    }
  } else {
    if (std::abs(current_.x - finish_.x)
        < current_speed) {
      current_.x = finish_.x;
    } else {
      if (current_.x < finish_.x) {
        current_.x += current_speed;
      } else {
        current_.x -= current_speed;
      }
    }
  }
  // UpdateViewDirection();
  return current_;
}

bool Route::HasFinished() const {
  return current_ == finish_;
}

