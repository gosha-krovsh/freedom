#include "destroyable.h"

Destroyable::Destroyable(int max_hp) : max_hp_(max_hp), hp_(max_hp) {}

int Destroyable::GetHP() const {
  return hp_;
}

bool Destroyable::IsDestroyed() const {
  return (hp_ <= 0);
}

void Destroyable::IncreaseHP(int hp) {
  if (hp < 0) {
    return;
  }

  hp_ += hp;
  if (hp_ > max_hp_) {
    hp_ = max_hp_;
  }
}
void Destroyable::DecreaseHP(int hp) {
  if (hp < 0) {
    return;
  }

  hp_ -= hp;
  if (hp_ < 0) {
    hp_ = 0;
  }
}
