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

void DynamicObject::UpdateMovement(bool left, bool up, bool right, bool down) {
  double h = (right ? 1 : 0) - (left ? 1 : 0);
  double v = (up ? 1 : 0) - (down ? 1 : 0);
  UpdateSpeedVector({h, v});
  UpdateViewDirection();
}

void DynamicObject::UpdateSpeedVector(Point iso_vector) {
  speed_vector_ = Point::FromIsometric(iso_vector);
  if (iso_vector.y == 0) {  // horizontal movement
    speed_vector_ *= constants::kIsometricSpeedCoefficient;
  } else if (iso_vector.x != 0 && iso_vector.y != 0) {  // diagonal movement
    speed_vector_ /= std::sqrt(2);
  }
}

void DynamicObject::UpdateViewDirection() {
  if (speed_vector_.x > 0) {
    if (speed_vector_.y > 0) {
      view_direction_ = ViewDirection::kDown;
    } else if (speed_vector_.y < 0) {
      view_direction_ = ViewDirection::kLeft;
    } else {
      view_direction_ = ViewDirection::kDownLeft;
    }
  } else if (speed_vector_.x < 0) {
    if (speed_vector_.y > 0) {
      view_direction_ = ViewDirection::kRight;
    } else if (speed_vector_.y < 0) {
      view_direction_ = ViewDirection::kUp;
    } else {
      view_direction_ = ViewDirection::kUpRight;
    }
  } else {
    if (speed_vector_.y > 0) {
      view_direction_ = ViewDirection::kDownRight;
    } else if (speed_vector_.y < 0) {
      view_direction_ = ViewDirection::kUpLeft;
    }
  }
}

void DynamicObject::Move() {
  SetCoordinates(GetCoordinates() + speed_vector_ * speed_value_);
}
