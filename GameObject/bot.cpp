#include "bot.h"

Bot::Bot(const QString& name, Point coords, int base) :
    Creature(coords, name, constants::kHP), base_direction_(base) {}

void Bot::Tick(int current_tick) {
  speed_vector_ = {0, 0};
  Creature::Tick(current_tick);
  Move();

  if (route_) {
    if (route_->HasFinished()) {
      route_ = nullptr;
    }
  } else {
    if (current_direction_ < 3) {
      ++current_direction_;
    } else {
      current_direction_ = 0;
    }
    route_ = std::make_unique<Route>(Point(GetX(), GetY(), GetZ()),
                                     Point(possible_bot_targets[base_direction_
                                               + current_direction_].x,
                                           possible_bot_targets[base_direction_
                                               + current_direction_].y,
                                           possible_bot_targets[base_direction_
                                               + current_direction_].z));
  }
}

void Bot::SetRoute(const Route& route) {
  if (route_) {
    route_ = nullptr;
  }
  route_ = std::make_unique<Route>(route);
}

void Bot::Move() {
  if (route_ == nullptr) {
    return;
  }
  Point next_point = route_->GetNext();
  bool right = ((GetX() - next_point.x) < constants::kEps);
  bool left = ((next_point.x - GetX()) < constants::kEps);
  bool up = ((GetY() - next_point.y) < constants::kEps);
  bool down = ((next_point.y - GetY()) < constants::kEps);
  double x = (right ? 1 : 0) - (left ? 1 : 0);
  double y = (up ? 0 : 1) - (down ? 0 : 1);
  Point speed_vector = {x, y};
  UpdateViewDirection();
  SetSpeedVector(speed_vector);
  SetCoordinates(next_point);
}

void Bot::OnDead() {}
