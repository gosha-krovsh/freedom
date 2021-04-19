#include "bot.h"
#include "point.h"
#include <qdebug.h>

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
