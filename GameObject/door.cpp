#include "door.h"

Door::Door(const Point& coords,
           const std::weak_ptr<QPixmap>& image,
           Type type) :
           Object(coords, image, type) {
  if (type != Object::Type::kDoor_225 && type != Object::Type::kDoor_315) {
    qDebug() << "Invalid door type";
  }

  if (type == Object::Type::kDoor_225) {
    animator_.AssignStateToAnimation(State(true), {"door_315"});
    animator_.AssignStateToAnimation(State(false), {"door_225"});
  } else if (type == Object::Type::kDoor_315) {
    animator_.AssignStateToAnimation(State(true), {"door_225"});
    animator_.AssignStateToAnimation(State(false), {"door_315"});
  }
}

void Door::Tick(int current_tick) {
  image_ = animator_.GetImageByState(is_openalbe_);
  Object::Tick(current_tick);
}

void Door::Interact(const InteractingObject& interacting_object) {
  if (IsObjectVeryClose(interacting_object.GetX(), interacting_object.GetY())) {
    return;
  }
  is_opened_ = !is_opened_;
  is_touchable_ = !is_opened_;
  SetDrawOffset();
}

bool Door::IsObjectVeryClose(double object_x, double object_y) const {
  return ((std::abs(object_x - GetX()) <
           constants::kDoorInteractingDistanceCoefficient) &&
          (std::abs(object_y - GetY()) <
           constants::kDoorInteractingDistanceCoefficient));
}

void Door::SetDrawOffset() {
  if (!is_opened_) {
    draw_offset_ = Point(0, 0);
  } else {
    if (type_ == Object::Type::kDoor_225) {
      draw_offset_ = Point(constants::kDoorOpenOffset, 0.);
    } else if (type_ == Object::Type::kDoor_315) {
      draw_offset_ = Point(0., constants::kDoorOpenOffset);
    }
  }
}

Point Door::GetDrawOffset() const {
  return draw_offset_;
}

int Door::GetPolicy() {
  return static_cast<int>(policy_);
}

void Door::SetPolicy(int policy) {
  policy_ = static_cast<kDoorPolicy>(policy);
}

bool Door::IsOpenable() {
  return is_openalbe_;
}

Door::State Door::GetState() {
  return static_cast<State>(is_opened_);
}

void Door::SetState(bool state) {
  is_opened_ = state;
}