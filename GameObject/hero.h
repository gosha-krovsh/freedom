#ifndef GAMEOBJECT_HERO_H_
#define GAMEOBJECT_HERO_H_

#include <QDebug>

#include <memory>
#include <utility>

#include "creature.h"
#include "storage.h"
#include "interacting_object.h"

class Hero : public Creature, public InteractingObject {
 public:
  explicit Hero(const Point& coords);

  void Tick(int current_tick) override;

  void SetStorage(std::shared_ptr<Storage>&& storage) {
    storage_ = std::move(storage);
  }

  Point GetViewVector() const;
  void UpdateMovement(bool left, bool up, bool right, bool down);

  void Respawn() override;
  void OnDead() override;

  double GetX() const override;
  double GetY() const override;
  int GetRoundedX() const override;
  int GetRoundedY() const override;
  int GetAttack() const override;

 private:
  void UpdateSpeedVector(const Point& screen_vector);
};

#endif  // GAMEOBJECT_HERO_H_
