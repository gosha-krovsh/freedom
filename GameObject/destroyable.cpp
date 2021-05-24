#include "destroyable.h"

Destroyable::Destroyable(int max_hp) : max_hp_(max_hp), hp_(max_hp) {}

int Destroyable::GetHP() const {
  return hp_;
}

bool Destroyable::IsDestroyed() const {
  return (hp_ <= 0);
}

void Destroyable::Respawn() {
  hp_ = max_hp_;
}

void Destroyable::IncreaseHP(int hp) {
  if (IsDestroyed()) {
    return;
  }

  hp_ += hp;
  if (hp_ > max_hp_) {
    hp_ = max_hp_;
  }
}
void Destroyable::DecreaseHP(int hp) {
  if (IsDestroyed()) {
    return;
  }

  hp_ -= hp;
  if (IsDestroyed()) {
    hp_ = 0;
    OnDead();
  }
}
