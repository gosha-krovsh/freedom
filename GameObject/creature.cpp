#include "creature.h"

#include <utility>

Creature::Creature(const Point& coords, QString name, int hp)
    : DynamicObject(coords), Destroyable(hp),
      AnimatedObject<DynamicObject::State>(&image_,
                                           State(action_, view_direction_)),
      name_(std::move(name)) {
  for (int i = 0; i < 8; ++i) {
    auto view_direction = static_cast<ViewDirection>(i);
    QString image_name = name_ + "_" + QString::number(i * 45);

    AssignStateToAnimation(State(Action::Run, view_direction),
                           {image_name,
                            image_name + "_run_1",
                            image_name,
                            image_name + "_run_2"});
    AssignStateToAnimation(State(Action::Idle, view_direction), {image_name});
  }
}

const QString& Creature::GetName() const {
  return name_;
}

void Creature::Tick(int current_tick) {
  DynamicObject::Tick(current_tick);
  AnimatedObject::Tick(current_tick);
}
