#include "bot.h"

Bot::Bot(const QString& name, const Point& coords) :
    Creature(coords, name, constants::kHP) {
        storage_ = std::make_shared<Storage>();
    }

void Bot::Tick(int current_tick) {
  Creature::Tick(current_tick);
  MakeStep();
  UpdateClothesName();
}

void Bot::UpdateClothesName() {
  clothes_name_ = "";
  for (const auto& item : storage_->GetItems()) {
    if (item.GetType() == Item::Type::kPrisonerRoba) {
      clothes_name_ = constants::kPrisonerClothesName;
      break;
    } else if (item.GetType() == Item::Type::kPoliceRoba) {
      clothes_name_ = constants::kPoliceClothesName;
      break;
    }
  }
}

void Bot::MakeStep() {
  if (current_index_in_path_ >= targets_.size()) {
    return;
  }

  Point next_point = targets_[current_index_in_path_];
  if (((std::abs(GetX() - next_point.x) > constants::kSpeed) ||
        (std::abs(GetY() - next_point.y) > constants::kSpeed)) &&
      !speed_vector_.IsNull()) {
    return;
  }

  if ((std::abs(GetX() - next_point.x) <= constants::kSpeed) &&
      (std::abs(GetY() - next_point.y) <= constants::kSpeed)) {
    SetCoordinates(next_point);
    ++current_index_in_path_;
  }
  Point speed_vector = next_point - GetCoordinates();
  NormalizeSpeedVector(speed_vector);
}

void Bot::SetStorage(std::shared_ptr<Storage>&& storage) {
  storage_ = std::move(storage);
}

void Bot::OnDead() {
  Creature::OnDead();
}

Point Bot::GetFinish() const {
  return finish_;
}

void Bot::SetFinish(const Point& new_finish) {
  finish_ = new_finish;
}

void Bot::Rebuild() {
  targets_.clear();
  current_index_in_path_ = 0;
}

const std::vector<Point>& Bot::GetTargets() {
  return targets_;
}

void Bot::SetTargets(const std::vector<Point>& targets) {
  targets_ = targets;
}
