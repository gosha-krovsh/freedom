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
