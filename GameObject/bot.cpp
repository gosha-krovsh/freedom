#include "bot.h"

Bot::Bot(const QString& name, const Point& coords, const Point& finish) :
    Creature(coords, name, constants::kHP), finish_(finish),
    base_finish_(finish), base_start_(coords) {}

void Bot::Tick(int current_tick) {
  Creature::Tick(current_tick);
  if (current_stay_ > 0 && !need_to_rebuild_) {
    --current_stay_;
    if (speed_vector_ != Point(0, 0)) {
      speed_vector_ = Point(0, 0);
    }
    if (current_stay_ == 0) {
      need_to_return_ = true;
    }
    return;
  }
  MakeStep();
}

void Bot::MakeStep() {
  Point next_point = targets_[current_direction_];
  if (((std::abs(GetX() - next_point.x) > constants::kSpeed)
      || (std::abs(GetY() - next_point.y) > constants::kSpeed)) &&
      !speed_vector_.IsNull()) {
    return;
  }

  if ((std::abs(GetX() - next_point.x) <= constants::kSpeed) &&
      (std::abs(GetY() - next_point.y) <= constants::kSpeed)) {
    SetCoordinates(next_point);
    current_direction_ += order_;
    if (current_direction_ == targets_.size() || current_direction_ == -1) {
      order_ *= -1;
      if (order_ == -1 && !need_to_rebuild_) {
        current_stay_ = stay_at_finish_;
        stay_at_finish_ = 0;
      }
      current_direction_ += order_;
      if (need_to_rebuild_) {
        current_direction_ = 0;
        order_ = 1;
        targets_.clear();
        return;
      }
    }
    if (!targets_.empty()) {
      next_point = targets_[current_direction_];
    }
  }

  Point speed_vector = next_point - GetCoordinates();
  NormalizeSpeedVector(speed_vector);
}

void Bot::OnDead() {
  Creature::OnDead();
}

const Point& Bot::GetFinish() const {
  return finish_;
}

void Bot::SetFinish(const Point& new_finish) {
  finish_ = new_finish;
}

void Bot::RebuildPath(const Point& new_finish, int stay_at_finish) {
  need_to_rebuild_ = true;
  finish_ = new_finish;
  stay_at_finish_ = stay_at_finish;
}

void Bot::Normalize() {
  current_direction_ = 0;
  order_ = 1;
}
