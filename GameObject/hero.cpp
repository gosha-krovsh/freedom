#include "hero.h"

#include <QDebug>

Hero::Hero(const Point& coords)
  : Creature(coords, "Hero", constants::kHP) {}

void Hero::Tick(int current_tick) {
  Creature::Tick(current_tick);
}

Point Hero::GetViewVector() const {
  Point view_vector(-1, 0);
  view_vector.Rotate(-135 + 45 * static_cast<int>(view_direction_));
  return view_vector;
}

void Hero::OnDead() {}

int Hero::GetRoundedX() const {
  return Object::GetRoundedX();
}
int Hero::GetRoundedY() const {
  return Object::GetRoundedY();
}
int Hero::GetAttack() const {
  return Creature::GetAttack();
}
