#include "creature.h"

Creature::Creature(const Point& coords, const QString& name, int hp)
    : DynamicObject(coords), Destroyable(hp), name_(name) {
  for (int i = 0; i < constants::kNumberOfViewDirections; ++i) {
    auto view_direction = static_cast<ViewDirection>(i);
    QString image_name = name_ + "_" + QString::number(i * 45);

    animator_.AssignStateToAnimation(State(Action::kRun, view_direction),
                                     {image_name,
                                      image_name + "_run_1",
                                      image_name,
                                      image_name + "_run_2"});
    animator_.AssignStateToAnimation(State(Action::kIdle, view_direction),
                                     {image_name});
  }
}

const QString& Creature::GetName() const {
  return name_;
}

void Creature::Tick(int current_tick) {
  image_ = animator_.GetImageByState(GetState());

  DynamicObject::Tick(current_tick);
  animator_.Tick();
}

void Creature::SetSpeedVector(const Point& speed_vector) {
  DynamicObject::SetSpeedVector(speed_vector);
  if (speed_vector_.IsNull()) {
    action_ = Action::kIdle;
  } else {
    action_ = Action::kRun;
  }
}

Creature::State Creature::GetState() const {
  return State(action_, view_direction_);
}
