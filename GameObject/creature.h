#ifndef GAMEOBJECT_CREATURE_H_
#define GAMEOBJECT_CREATURE_H_

#include <QString>

#include <utility>
#include <memory>

#include "dynamic_object.h"
#include "animator.h"
#include "destroyable.h"

class Creature : public DynamicObject, public Destroyable {
 public:
  enum class Action {
    kIdle,
    kRun,
  };
  using State = std::pair<Action, DynamicObject::ViewDirection>;

  Creature(const Point& coords, const QString& name, int hp);

  const QString& GetName() const;
  void SetSpeedVector(const Point& speed_vector) override;

  void Tick(int current_tick) override;

  bool IsAbleToAttack() const;
  void UpdateAttackCooldown();

 protected:
  Action action_{Action::kIdle};

 private:
  State GetState() const;

 private:
  QString name_;
  Animator<State> animator_{GetState()};
  int attack_cooldown_{0};
};

#endif  // GAMEOBJECT_CREATURE_H_
