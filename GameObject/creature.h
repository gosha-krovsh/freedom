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

  Creature(const Point& coords, QString name, int hp);

  const QString& GetName() const;
  void SetSpeedVector(const Point& speed_vector) override;

  void Tick(int current_tick) override;

 protected:
  Action action_{Action::kIdle};

 private:
  State GetState() const {
    return State(action_, view_direction_);
  }

 private:
  QString name_;
  Animator<State> animator_{State(Action::kIdle, ViewDirection::kDown)};
};

#endif  // GAMEOBJECT_CREATURE_H_
