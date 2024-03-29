#include "creature.h"

namespace {

void AddClothesSuffix(QString* name, const char* suffix) {
  QString string_suffix = QString(suffix);
  *name += (string_suffix.isEmpty() ? "" : "_") + string_suffix;
}

}  // namespace

Creature::Creature(const Point& coords, const QString& name, int hp) :
    DynamicObject(coords),
    Destroyable(hp),
    name_(name) {
  for (int i = 0; i < constants::kNumberOfViewDirections; ++i) {
    auto view_direction = static_cast<ViewDirection>(i);
    QString angle = QString::number(i * 45);
    for (const auto& clothes_name : constants::kClothes) {
      QString image_name = angle;
      AddClothesSuffix(&image_name, clothes_name);

      animator_.AssignStateToAnimation(State(Action::kIdle,
                                             view_direction,
                                             clothes_name),
                                       {image_name});
      animator_.AssignStateToAnimation(State(Action::kDead,
                                             view_direction,
                                             clothes_name),
                                       {image_name + "_dead"});
      animator_.AssignStateToAnimation(State(Action::kFight,
                                             view_direction,
                                             clothes_name),
                                       {"cloud"});
      animator_.AssignStateToAnimation(State(Action::kRun,
                                             view_direction,
                                             clothes_name),
                                       {image_name,
                                        image_name + "_run_1",
                                        image_name,
                                        image_name + "_run_2"});
    }
  }
  storage_ = std::make_shared<Storage>();
  gun_storage_ = std::make_shared<Storage>();
  clothing_storage_ = std::make_shared<Storage>();
}
const QString& Creature::GetName() const {
  return name_;
}

void Creature::Tick(int current_tick) {
  image_ = animator_.GetImageByState(GetState());
  ShakingObject::Tick(current_tick);

  DecrementAttackCooldown();
  if (!IsDestroyed() && action_ != Action::kFight) {
    DynamicObject::Tick(current_tick);
  }

  // Temp code.
  // TODO: In the future, there will be separate cell in inventory for clothes.
  clothes_name_ = "";
  for (const auto& item : clothing_storage_->GetItems()) {
    if (item.GetType() == Item::Type::kPrisonerRoba) {
      clothes_name_ = constants::kPrisonerClothesName;
      break;
    } else if (item.GetType() == Item::Type::kPoliceRoba) {
      clothes_name_ = constants::kPoliceClothesName;
      break;
    }
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

const std::string& Creature::GetClothesName() const {
  return clothes_name_;
}
Creature::State Creature::GetState() const {
  return State(action_, view_direction_, clothes_name_);
}

void Creature::NormalizeSpeedVector(const Point& speed_vector) {
  Point new_speed = speed_vector;
  new_speed.Normalize();

  // Making movement more realistic in isometric world: equal displacement in
  // isometric view in all directions, except horizontal (a slow down here)
  if (std::abs(new_speed.x) >= constants::kEps &&
      std::abs(new_speed.y) >= constants::kEps &&
      new_speed.x * new_speed.y <= constants::kEps) {
    // horizontal movement
    new_speed *= constants::kIsometricSpeedCoefficient;
  } else if (std::abs(new_speed.x) * std::abs(new_speed.y)
      <= constants::kEps) {
    // diagonal movement
    new_speed /= std::sqrt(2);
  }
  SetSpeedVector(new_speed);
  UpdateViewDirection();
}

bool Creature::IsAbleToAttack() const {
  return attack_cooldown_ == 0 && !IsDestroyed();
}

void Creature::RefreshAttackCooldown() {
  attack_cooldown_ = Settings::GetAttackCooldown();
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

Point Creature::GetDrawOffset() const {
  return ShakingObject::GetOffset();
}

std::shared_ptr<Conversation> Creature::GetCurrentConversation() const {
  return current_conversation_;
}

void Creature::SetCurrentConversation(
    const std::shared_ptr<Conversation>& conversation) {
  current_conversation_ = conversation;
}

void Creature::Respawn() {
  Destroyable::Respawn();
}
