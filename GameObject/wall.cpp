#include "wall.h"

Wall::Wall(const Point& coords, const std::weak_ptr<QPixmap>& image)
  : Object(coords, image, Type::kWall),
    Destroyable(constants::kBlockHP) {}

void Wall::Tick(int current_tick) {
  Object::Tick(current_tick);
  ShakingObject::Tick(current_tick);
}

void Wall::OnDead() {
  is_touchable_ = false;
  delete_on_next_tick_ = true;
}

void Wall::Interact(const InteractingObject& interacting_object) {
  DecreaseHP(interacting_object.GetAttack());

  Point direction_of_shake{GetRoundedX() - interacting_object.GetRoundedX(),
                           GetRoundedY() - interacting_object.GetRoundedY()};
  Shake(direction_of_shake);

  ShakingObject::SetOffset((1. - GetHP() / (1. * constants::kBlockHP)) *
                           constants::kMaxBlockOffset *
                           direction_of_shake);
}

Point Wall::GetDrawOffset() const {
  return ShakingObject::GetOffset();
}
