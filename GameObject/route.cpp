#include "route.h"
#include "point.h"

#include <cmath>

Route::Route(const Point& start, const Point& finish) :
            start_point_(start),
            finish_point_(finish),
            current_point_(start) {}

Point Route::GetNext() {
  if (current_point_.x == finish_point_.x &&
      current_point_.y == finish_point_.y &&
      current_point_.z == finish_point_.z) {
    return finish_point_;
  }

  if (std::abs(current_point_.y - finish_point_.y) < 0.04) {
    current_point_.y = finish_point_.y;
  } else if (current_point_.y < finish_point_.y) {
    current_point_.y += 0.04;
  } else {
    current_point_.y -= 0.04;
  }

  if (std::abs(current_point_.x - finish_point_.x) < 0.08) {
    current_point_.x = finish_point_.x;
  } else if (current_point_.x < finish_point_.x) {
    current_point_.x += 0.08 * constants::kIsometricSpeedCoefficient;
  } else {
    current_point_.x -= 0.08 * constants::kIsometricSpeedCoefficient;
  }

  return current_point_;
}

bool Route::HasFinished() const {
  return (current_point_.x == finish_point_.x &&
          current_point_.y == finish_point_.y &&
          current_point_.z == finish_point_.z);
}

