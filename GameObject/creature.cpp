#include "creature.h"

Creature::Creature(const Point& coords, const QString& name, int hp) :
    DynamicObject(coords),
    Destroyable(hp),
    name_(name) {
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
  DecrementAttackCooldown();

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

void Creature::NormalizeSpeedVector(Point* speed_vector) {
  speed_vector->Normalize();

  // Making movement more realistic in isometric world: equal displacement in
  // isometric view in all directions, except horizontal (a slow down here)
  if (std::abs(speed_vector->x) >= constants::kEps &&
      std::abs(speed_vector->y) >= constants::kEps &&
      speed_vector->x * speed_vector->y <= constants::kEps) {
    // horizontal movement
    *speed_vector *= constants::kIsometricSpeedCoefficient;
  } else if (std::abs(speed_vector->x) * std::abs(speed_vector->y)
      <= constants::kEps) {
    // diagonal movement
    *speed_vector /= std::sqrt(2);
  }
  SetSpeedVector(*speed_vector);
  UpdateViewDirection();
}
bool Creature::IsAbleToAttack() const {
  return attack_cooldown_ == 0;
}

void Creature::RefreshAttackCooldown() {
  attack_cooldown_ = constants::kAttackCooldown;
}

int Creature::GetAttack() const {
  return attack_;
}

void Creature::DecrementAttackCooldown() {
  if (attack_cooldown_ != 0) {
    --attack_cooldown_;
  }
}
