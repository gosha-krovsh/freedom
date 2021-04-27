#ifndef GAMEOBJECT_CREATURE_H_
#define GAMEOBJECT_CREATURE_H_

#include <QDebug>
#include <QString>

#include <memory>
#include <utility>

#include "animator.h"
#include "destroyable.h"
#include "dynamic_object.h"

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
  void RefreshAttackCooldown();
  int GetAttack() const;

 protected:
  Action action_{Action::kIdle};
  void NormalizeSpeedVector(Point&);


 private:
  State GetState() const;
  void DecrementAttackCooldown();

 private:
  QString name_;
  Animator<State> animator_{GetState()};
  int attack_cooldown_{0};
  int attack_{constants::kAttack};
};

#endif  // GAMEOBJECT_CREATURE_H_
