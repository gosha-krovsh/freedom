#ifndef GAMEOBJECT_CREATURE_H_
#define GAMEOBJECT_CREATURE_H_

#include <QDebug>
#include <QString>

#include <memory>
#include <utility>

#include "animator.h"
#include "destroyable.h"
#include "dynamic_object.h"
#include "shaking_object.h"

class Creature : public DynamicObject,
                 public Destroyable,
                 public ShakingObject {
 public:
  enum class Action {
    kIdle,
    kRun,
    kFight,
    kDead,
  };
  using State = std::pair<Action, DynamicObject::ViewDirection>;

  Creature(const Point& coords, const QString& name, int hp);

  const QString& GetName() const;
  void SetSpeedVector(const Point& speed_vector) override;

  void Tick(int current_tick) override;

  bool IsAbleToAttack() const;
  void RefreshAttackCooldown();
  int GetAttack() const;
  void StartFighting();
  void StopFighting();
  bool IsDestroyed() const;
  int GetHP() const;
  void OnDead() override;
  Point GetDrawOffset() const override;

 protected:
  Action action_{Action::kIdle};
  void NormalizeSpeedVector(const Point& speed_vector);

 private:
  State GetState() const;
  void DecrementAttackCooldown();
  void SetAction(Action action);

 private:
  QString name_;
  Action action_{Action::kIdle};
  Animator<State> animator_{GetState()};
  int attack_cooldown_{0};
  int attack_{constants::kAttack};
};

#endif  // GAMEOBJECT_CREATURE_H_
