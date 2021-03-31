#ifndef GAMEOBJECT_CREATURE_H_
#define GAMEOBJECT_CREATURE_H_

#include <QString>

#include <utility>

#include "dynamic_object.h"
#include "animated_object.h"
#include "destroyable.h"

enum class Action {
  Idle,
  Run,
};
using State = std::pair<Action, DynamicObject::ViewDirection>;

class Creature : public DynamicObject, public Destroyable,
 public AnimatedObject<State> {
 public:
  Creature(const Point& coords, QString name, int hp);

  const QString& GetName() const;
  void SetSpeedVector(const Point& speed_vector) override;

  void Tick(int current_tick) override;

 protected:
  Action action_{Action::Idle};

 private:
  QString name_;
};

#endif  // GAMEOBJECT_CREATURE_H_
