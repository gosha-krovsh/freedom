#ifndef GAMEOBJECT_CREATURE_H_
#define GAMEOBJECT_CREATURE_H_

#include <QDebug>
#include <QString>

#include <memory>
#include <string>
#include <utility>
#include <tuple>
#include <vector>

#include "animator.h"
#include "destroyable.h"
#include "dynamic_object.h"
#include "shaking_object.h"
#include "Conversations/conversation.h"

class Creature : public DynamicObject,
                 public Destroyable,
                 public ShakingObject {
 public:
  enum class Action {
    kIdle,
    kRun,
    kFight,
    kDead,
    kBotLunch
  };

  using State = std::tuple<Action, DynamicObject::ViewDirection, std::string>;

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

  std::shared_ptr<Conversation> GetCurrentConversation() const;
  void SetCurrentConversation(const std::shared_ptr<Conversation>&);

 protected:
  Action action_{Action::kIdle};
  void NormalizeSpeedVector(const Point& speed_vector);

  std::string clothes_name_;

 private:
  State GetState() const;
  void DecrementAttackCooldown();
  void SetAction(Action action);

 private:
  QString name_;
  Animator<State> animator_{GetState()};
  int attack_cooldown_{0};
  int attack_{constants::kAttack};
  std::shared_ptr<Conversation> current_conversation_;
};

#endif  // GAMEOBJECT_CREATURE_H_
