#include "dynamic_object.h"

DynamicObject::DynamicObject(const Point& coords, const QPixmap& image) :
    Object(coords, image) {
  is_touchable_ = false;
}

void DynamicObject::Tick(int current_tick) {
  Object::Tick(current_tick);
  Move();
}

DynamicObject::ViewDirection DynamicObject::GetViewDirection() const {
  return view_direction_;
}

void DynamicObject::UpdateViewDirection() {
  if (speed_vector_.x >= constants::kEps) {
    if (speed_vector_.y >= constants::kEps) {
      view_direction_ = ViewDirection::kDown;
    } else if (speed_vector_.y <= -constants::kEps) {
      view_direction_ = ViewDirection::kLeft;
    } else {
      view_direction_ = ViewDirection::kDownLeft;
    }
  } else if (speed_vector_.x <= constants::kEps) {
    if (speed_vector_.y >= constants::kEps) {
      view_direction_ = ViewDirection::kRight;
    } else if (speed_vector_.y <= -constants::kEps) {
      view_direction_ = ViewDirection::kUp;
    } else {
      view_direction_ = ViewDirection::kUpRight;
    }
  } else {
    if (speed_vector_.y >= constants::kEps) {
      view_direction_ = ViewDirection::kDownRight;
    } else if (speed_vector_.y <= -constants::kEps) {
      view_direction_ = ViewDirection::kUpLeft;
    }
  }
}

void DynamicObject::Move() {
  SetCoordinates(GetCoordinates() + speed_vector_ * speed_value_);
}
