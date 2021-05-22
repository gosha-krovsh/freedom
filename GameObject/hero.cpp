#include "hero.h"
Hero::Hero(const Point& coords)
  : Creature(coords, "Hero", constants::kHP) {
  storage_ = std::make_shared<Storage>();
}

void Hero::Tick(int current_tick) {
  Creature::Tick(current_tick);

  // Temp code.
  // TODO: In the future, there will be separate cell in inventory for clothes.
  bool is_roba = false;
  for (const auto& item : storage_->GetItems()) {
    if (item.GetName() == "roba") {
      is_roba = true;
      break;
    }
  }
  if (is_roba) {
    clothes_name_ = "roba";
  } else {
    clothes_name_ = "";
  }
}

Point Hero::GetViewVector() const {
  Point view_vector(-1, 0);
  view_vector.Rotate(-135 + 45 * static_cast<int>(view_direction_));
  return view_vector;
}

void Hero::UpdateMovement(bool left, bool up, bool right, bool down) {
  double x = (right ? 1 : 0) - (left ? 1 : 0);
  double y = (up ? 1 : 0) - (down ? 1 : 0);
  Point screen_vector{x, y};
  UpdateSpeedVector(screen_vector);
  UpdateViewDirection();
}

double Hero::GetX() const {
  return Object::GetX();
}

double Hero::GetY() const {
  return Object::GetY();
}

int Hero::GetRoundedX() const {
  return Object::GetRoundedX();
}
int Hero::GetRoundedY() const {
  return Object::GetRoundedY();
}

int Hero::GetAttack() const {
  return Creature::GetAttack();
}

void Hero::UpdateSpeedVector(const Point& screen_vector) {
  Point speed_vector = Point::FromScreenPoint(screen_vector);
  NormalizeSpeedVector(speed_vector);
}

void Hero::OnDead() {
  Creature::OnDead();
}
