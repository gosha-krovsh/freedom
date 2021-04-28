#include "wall.h"

Wall::Wall(const Point& coords)
  : Object(coords, wall_image_),
    Destroyable(constants::kHP) {
  type_ = Type::kWall;
}

void Wall::Tick(int current_tick) {
  Object::Tick(current_tick);
  ShakingObject::Tick(current_tick);
}

void Wall::OnDead() {
  is_touchable_ = false;
  delete_on_next_tick_ = true;
}

void Wall::SetImage(const std::shared_ptr<QPixmap>& image) {
  wall_image_ = image;
}

void Wall::Interact(const InteractingObject& interacting_object) {
  DecreaseHP(interacting_object.GetAttack());

  Point direction_of_shake{GetRoundedX() - interacting_object.GetRoundedX(),
                           GetRoundedY() - interacting_object.GetRoundedY()};
  Shake(direction_of_shake);
}

Point Wall::GetDrawOffset() const {
  return ShakingObject::GetOffset();
}

void Wall::DeleteImage() {
  wall_image_.reset();
}

std::shared_ptr<QPixmap> Wall::wall_image_;
