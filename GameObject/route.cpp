#include "route.h"
#include "point.h"
#include "dynamic_object.h"
#include <cmath>
#include<qdebug.h>

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

  double current_speed = constants::kSpeed / (sqrt(2));
  if (current_point_.y != finish_point_.y) {
    if (std::abs(current_point_.y - finish_point_.y) < current_speed) {
      current_point_.y = finish_point_.y;
    } else if (current_point_.y < finish_point_.y) {
      current_point_.y += current_speed;
    } else {
      current_point_.y -= current_speed;
    }
  } else {
    if (std::abs(current_point_.x - finish_point_.x)
        < current_speed) {
      current_point_.x = finish_point_.x;
    } else {
      if (current_point_.x < finish_point_.x) {
        current_point_.x += current_speed;
      } else {
        current_point_.x -= current_speed;
      }
    }

  }
  // UpdateViewDirection();
  return current_point_;
}

bool Route::HasFinished() const {
  return (current_point_.x == finish_point_.x &&
      current_point_.y == finish_point_.y &&
      current_point_.z == finish_point_.z);
}

