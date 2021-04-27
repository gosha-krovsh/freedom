#ifndef GAMEOBJECT_HERO_H_
#define GAMEOBJECT_HERO_H_

#include "creature.h"
#include "storable_object.h"
#include "interacting_object.h"

class Hero : public Creature, public StorableObject, public InteractingObject {
 public:
  explicit Hero(const Point& coords);

  void Tick(int current_tick) override;
  void UpdateMovement(bool left, bool up, bool right, bool down);
  Point GetViewVector() const;
  void OnDead() override;

  int GetRoundedX() const override;
  int GetRoundedY() const override;
  int GetAttack() const override;

 private:
  void UpdateSpeedVector(const Point& screen_vector);
};

#endif  // GAMEOBJECT_HERO_H_
