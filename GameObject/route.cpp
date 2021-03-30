#include "route.h"

#include <cmath>

Route::Route(const Coordinates& start, const Coordinates& finish) :
            start_point_(start),
            finish_point_(finish),
            current_point_(start) {}

Coordinates Route::GetNext() {
  if (current_point_.x == finish_point_.x &&
      current_point_.y == finish_point_.y &&
      current_point_.z == finish_point_.z) {
    return finish_point_;
  }

  if (std::abs(current_point_.y - finish_point_.y) < 1) {
    current_point_.y = finish_point_.y;
  } else if (current_point_.y < finish_point_.y) {
    current_point_.y += 1;
  } else {
    current_point_.y -= 1;
  }

  if (std::abs(current_point_.x - finish_point_.x) < 1) {
    current_point_.x = finish_point_.x;
  } else if (current_point_.x < finish_point_.x) {
    current_point_.x += 1;
  } else {
    current_point_.x -= 1;
  }

  return current_point_;
}

bool Route::HasFinished() const {
  return (current_point_.x == finish_point_.x &&
          current_point_.y == finish_point_.y &&
          current_point_.z == finish_point_.z);
}

