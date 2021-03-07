#include "hero.h"

Hero::Hero(Coordinates coords, const QPixmap& image)
  : Creature(coords, image, "", constants::kHP) {}

void Hero::OnDead() {}
