#include "hero.h"

Hero::Hero(Point coords, const QPixmap& image)
  : Creature(coords, image, "", constants::kHP) {}

void Hero::Tick(int current_tick) {
  Creature::Tick(current_tick);
}

void Hero::OnDead() {}
