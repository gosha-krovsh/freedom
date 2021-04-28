#include "creature.h"

Creature::Creature(const Point& coords, const QString& name, int hp):
    DynamicObject(coords),
    Destroyable(hp),
    name_(name) {
  for (int i = 0; i < constants::kNumberOfViewDirections; ++i) {
    auto view_direction = static_cast<ViewDirection>(i);
    QString image_name = name_ + "_" + QString::number(i * 45);

    animator_.AssignStateToAnimation(State(Action::kIdle, view_direction),
                                     {image_name});
    animator_.AssignStateToAnimation(State(Action::kDead, view_direction),
                                     {image_name + "_dead"});
    animator_.AssignStateToAnimation(State(Action::kFight, view_direction),
                                     {"cloud"});
    animator_.AssignStateToAnimation(State(Action::kRun, view_direction),
                                     {image_name,
                                      image_name + "_run_1",
                                      image_name,
                                      image_name + "_run_2"});
  }
}
const QString& Creature::GetName() const {
  return name_;
}

void Creature::Tick(int current_tick) {
  image_ = animator_.GetImageByState(GetState());
  DecrementAttackCooldown();

  if (!IsDestroyed() && action_ != Action::kFight) {
    DynamicObject::Tick(current_tick);
  }

  animator_.Tick();
}

void Creature::SetSpeedVector(const Point& speed_vector) {
  DynamicObject::SetSpeedVector(speed_vector);

  if (action_ != Action::kFight) {
    if (speed_vector_.IsNull()) {
      SetAction(Action::kIdle);
    } else {
      SetAction(Action::kRun);
    }
  }
}

Creature::State Creature::GetState() const {
  return State(action_, view_direction_);
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

void Creature::StartFighting() {
  SetAction(Action::kFight);
}
void Creature::StopFighting() {
  SetAction(Action::kIdle);
}

void Creature::SetAction(Creature::Action action) {
  if (!IsDestroyed()) {
    action_ = action;
  }
}

bool Creature::IsDestroyed() const {
  return Destroyable::IsDestroyed();
}
int Creature::GetHP() const {
  return Destroyable::GetHP();
}

void Creature::OnDead() {
  action_ = Action::kDead;
}
