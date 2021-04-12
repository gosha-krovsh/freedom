#include "bot.h"
#include "point.h"

Bot::Bot(const QString& name, Point coords, const QPixmap& image) :
    Creature(coords, image, name, constants::kHP) {}

void Bot::Tick(int current_tick) {
  Creature::Tick(current_tick);
  Move();

  if (route_) {
    if (route_->HasFinished()) {
      // SetMoving(false);
      route_ = nullptr;
    }
  } else {
    int k = rand() % possible_bot_targets_.size();
    route_ = new Route(GetCoordinates(), possible_bot_targets_[k]);
  }
}

void Bot::SetRoute(const Route& route) {
  if (route_) {
    delete route_;
    route_ = nullptr;
  }

  route_ = new Route(route);
  // SetMoving(true);
}

void Bot::Move() {
  // if (!IsMoving()) {
  //   return;
  // }

  if (route_ == nullptr) {
    return;
  }
  SetCoordinates(route_->GetNext());
}

void Bot::OnDead() {}
