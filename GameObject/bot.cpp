#include "bot.h"

#include <QDebug>

Bot::Bot(const QString& name, const Point& coords,
         const std::vector<Point>& targets) :
    Creature(coords, name, constants::kHP), targets_(targets) {}

void Bot::Tick(int current_tick) {
  speed_vector_ = {0, 0};
  Creature::Tick(current_tick);
  Move();

  if (route_) {
    if (route_->HasFinished()) {
      route_ = nullptr;
    }
  } else {
    current_direction_ = (current_direction_ + 1) % targets_.size();
    route_ = std::make_unique<Route>(Point(GetX(), GetY(), GetZ()),
                                     targets_[current_direction_]);
  }
}

void Bot::SetRoute(const Route& route) {
  route_ = std::make_unique<Route>(route);
}

void Bot::Move() {
  if (route_ == nullptr) {
    return;
  }

  Point next_point = route_->GetNext();

  if (next_point.x == GetX()) {
    if (next_point.y > GetY()) {
      SetSpeedVector({0, 1});
    } else {
      SetSpeedVector({0, -1});
    }
  } else if (next_point.y == GetY()) {
    if (next_point.x > GetX()) {
      SetSpeedVector({1, 0});
    } else {
      SetSpeedVector({-1, 0});
    }
  }
  UpdateViewDirection();
  SetCoordinates(next_point);
}

void Bot::OnDead() {}
