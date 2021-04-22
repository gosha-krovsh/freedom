#include "hero.h"

#include <QDebug>

Hero::Hero(const Point& coords)
  : Creature(coords, "Hero", constants::kHP) {}

void Hero::Tick(int current_tick) {
  Creature::Tick(current_tick);
}

void Hero::OnDead() {}
