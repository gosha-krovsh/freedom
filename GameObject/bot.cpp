#include "bot.h"

Bot::Bot(const QString& name, const Point& coords,
         const std::vector<Point>& targets) :
    Creature(coords, name, constants::kHP), targets_(targets) {}

void Bot::Tick(int current_tick) {
  Creature::Tick(current_tick);
  Move();
  if (GetCoordinates() == targets_[current_direction_]) {
      speed_vector_ = Point(0, 0);
      current_direction_ = (current_direction_ + order_);
      if (current_direction_ == targets_.size() || current_direction_ == -1) {
        order_ *= -1;
        current_direction_ += order_;
      }
  }
}

void Bot::SetRoute(const Route& route) {
  route_ = std::make_unique<Route>(route);
}

void Bot::Move() {
  Point next_point = targets_[current_direction_];
  if (!(std::abs(GetX() - next_point.x) <= constants::kSpeed
      && std::abs(GetY() - next_point.y) <= constants::kSpeed) &&
      (speed_vector_ != Point(0, 0))) {
    return;
  } else if (speed_vector_ != Point(0, 0)) {
    SetCoordinates(next_point);
    speed_vector_ = {0, 0};
    return;
  }

  Point speed_vector = next_point - GetCoordinates();
  NormalizeAsSpeedVector(speed_vector);
}

void Bot::OnDead() {}
