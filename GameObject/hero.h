#ifndef GAMEOBJECT_HERO_H_
#define GAMEOBJECT_HERO_H_

#include "creature.h"
#include "interacting_object.h"

class Hero : public Creature, public InteractingObject {
 public:
  explicit Hero(const Point& coords);

  void Tick(int current_tick) override;

  Point GetViewVector() const;
  void UpdateMovement(bool, bool, bool, bool);
  void OnDead() override;

  int GetRoundedX() const override;
  int GetRoundedY() const override;
  int GetAttack() const override;

 private:
  void UpdateSpeedVector(const Point&);
};

#endif  // GAMEOBJECT_HERO_H_
