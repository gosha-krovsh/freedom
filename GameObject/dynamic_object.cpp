#include "dynamic_object.h"

DynamicObject::DynamicObject(const Coordinates& coords, const QPixmap& image) :
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

void DynamicObject::SetViewDirection(ViewDirection view_direction) {
  view_direction_ = view_direction;
}

void DynamicObject::SetViewDirection(Coordinates speed) {
  if (speed.x > 0) {
    if (speed.y > 0) {
      SetViewDirection(ViewDirection::kDown);
    } else if (speed.y < 0) {
      SetViewDirection(ViewDirection::kLeft);
    } else {
      SetViewDirection(ViewDirection::kDownLeft);
    }
  } else if (speed.x < 0) {
    if (speed.y > 0) {
      SetViewDirection(ViewDirection::kRight);
    } else if (speed.y < 0) {
      SetViewDirection(ViewDirection::kUp);
    } else {
      SetViewDirection(ViewDirection::kUpRight);
    }
  } else {
    if (speed.y > 0) {
      SetViewDirection(ViewDirection::kDownRight);
    } else if (speed.y < 0) {
      SetViewDirection(ViewDirection::kUpLeft);
    }
  }
}

void DynamicObject::UpdateMoving(bool left, bool up, bool right, bool down) {
  double h = (right ? 1 : 0) - (left ? 1 : 0);
  double v = (up ? 1 : 0) - (down ? 1 : 0);
  SetSpeedVector(Coordinates{h, v});
  SetViewDirection(speed_vector);
}

Coordinates DynamicObject::GetSpeedVector() const {
  // TODO
  // rotate, ClampMagnitude, if r/l => add
}

void DynamicObject::Move() {
  SetCoordinates(GetCoordinates() + GetSpeedVector() * speed_);
}

void DynamicObject::SetSpeedVector(Coordinates coords) {
  speed_vector = coords;
}
