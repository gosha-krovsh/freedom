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
  double hor = (right ? 1 : 0) - (left ? 1 : 0);
  double vert = (up ? 1 : 0) - (down ? 1 : 0);
  Point screen_vector{hor, vert};
  UpdateSpeedVector(screen_vector);
  UpdateViewDirection(screen_vector);
}

void DynamicObject::UpdateSpeedVector(const Point& screen_vector) {
  speed_vector_ = Point::FromScreenPoint(screen_vector);
  speed_vector_.Normalize();
  if (screen_vector.y == 0) {  // horizontal movement
    speed_vector_ *= constants::kIsometricSpeedCoefficient;
  } else if (screen_vector.x != 0 &&
             screen_vector.y != 0) {  // diagonal movement
    speed_vector_ /= std::sqrt(2);
  }
}

void DynamicObject::UpdateViewDirection(const Point& screen_vector) {
  if (screen_vector.IsNull()) {
    return;
  }
  view_direction_ = static_cast<ViewDirection>(
                      3 * (screen_vector.x + 1) + (screen_vector.y + 1));
}

void DynamicObject::Move() {
  SetCoordinates(GetCoordinates() + speed_vector_ * speed_value_);
}
