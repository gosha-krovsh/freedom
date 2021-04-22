#ifndef GAMEOBJECT_CREATURE_H_
#define GAMEOBJECT_CREATURE_H_

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
  void UpdateMovement(bool, bool, bool, bool);

  void Tick(int current_tick) override;

 protected:
  Action action_{Action::kIdle};
  void UpdateSpeedVector(const Point&);

 private:
  State GetState() const;

 private:
  QString name_;
  Animator<State> animator_{GetState()};
};

#endif  // GAMEOBJECT_CREATURE_H_
