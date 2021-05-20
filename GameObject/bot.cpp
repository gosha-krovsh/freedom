#include "bot.h"

Bot::Bot(const QString& name, const Point& coords, const Point& finish) :
    Creature(coords, name, constants::kHP), finish_(finish) {}

void Bot::Tick(int current_tick) {
  Creature::Tick(current_tick);
  MakeStep();
}

void Bot::MakeStep() {
  if (current_direction_ >= targets_.size()) {
    return;
  }
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
    if (current_direction_ == targets_.size()) {
      SetViewDirection({next_point.x, next_point.y});
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
void Bot::Rebuild() {
  targets_.clear();
  current_direction_ = 0;
}
