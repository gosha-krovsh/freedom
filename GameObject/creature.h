#ifndef GAMEOBJECT_CREATURE_H_
#define GAMEOBJECT_CREATURE_H_

#include <QString>

#include <utility>

#include "dynamic_object.h"
#include "animated_object.h"
#include "destroyable.h"

namespace {
  enum class CreatureAction {
    kIdle,
    kRun,
  };
  using State = std::pair<CreatureAction, DynamicObject::ViewDirection>;
}  // anonymous namespace

class Creature : public DynamicObject, public Destroyable,
                 public AnimatedObject<State> {
 public:
  using Action = CreatureAction;
  Creature(const Point& coords, QString name, int hp);

  const QString& GetName() const;
  void SetSpeedVector(const Point& speed_vector) override;

  void Tick(int current_tick) override;

 protected:
  Action action_{Action::kIdle};

 private:
  QString name_;
};

#endif  // GAMEOBJECT_CREATURE_H_
