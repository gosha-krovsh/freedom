#include "bot.h"

Bot::Bot(const QString& name, const Point& coords, int hp, Type type)
  : Creature(coords, name, hp), type_(type) {
  storage_ = std::make_shared<Storage>();
}

void Bot::Tick(int current_tick) {
  Creature::Tick(current_tick);
  MakeStep();
}

void Bot::MakeStep() {
  if (current_point_ == targets_.end()) {
    SetSpeedVector(Point(0, 0));
    return;
  }

  if (GetCoordinates().DistanceFrom(*current_point_) < constants::kSpeed / 2) {
    SetCoordinates(*current_point_);
    ++current_point_;
    NormalizeSpeedVector(*current_point_ - GetCoordinates());
  }
}

Point Bot::GetFinish() const {
  if (targets_.empty()) {
    return GetCoordinates();
  }
  return targets_.back();
}

void Bot::SetStorage(std::shared_ptr<Storage>&& storage) {
  storage_ = std::move(storage);
}

void Bot::OnDead() {
  Creature::OnDead();
}

Bot::Type Bot::GetBotType() const {
  return type_;
}

const std::vector<Point>& Bot::GetTargets() {
  return targets_;
}

void Bot::SetTargets(const std::vector<Point>& targets) {
  targets_ = targets;
  current_point_ = targets_.begin();
  if (!targets_.empty() && *current_point_ == GetCoordinates()) {
    ++current_point_;
  }

  if (current_point_ != targets_.end()) {
    NormalizeSpeedVector(*current_point_ - GetCoordinates());
  }
}
