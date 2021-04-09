#ifndef GAMEOBJECT_HERO_H_
#define GAMEOBJECT_HERO_H_

#include "creature.h"

class Hero : public Creature {
 public:
  explicit Hero(const Point& coords);

  void Tick(int current_tick) override;
  void UpdateMovement(bool left, bool up, bool right, bool down);
  void OnDead() override;

 private:
  void UpdateSpeedVector(const Point& screen_vector);
};

#endif  // GAMEOBJECT_HERO_H_
