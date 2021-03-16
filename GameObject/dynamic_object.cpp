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

void DynamicObject::SetViewDirection(int h, int v) {
  if (v > 0) {
    if (h > 0) {
      SetViewDirection(ViewDirection::kUpRight);
    } else if (h < 0) {
      SetViewDirection(ViewDirection::kUpLeft);
    } else {
      SetViewDirection(ViewDirection::kUp);
    }
  } else if (v < 0) {
    if (h > 0) {
      SetViewDirection(ViewDirection::kDownRight);
    } else if (h < 0) {
      SetViewDirection(ViewDirection::kDownLeft);
    } else {
      SetViewDirection(ViewDirection::kDown);
    }
  } else {
    if (h > 0) {
      SetViewDirection(ViewDirection::kRight);
    } else if (h < 0) {
      SetViewDirection(ViewDirection::kLeft);
    }
  }
}

void DynamicObject::SetMovingDirection(bool left, bool up,
                                       bool right, bool down) {
  int h = (right ? 1 : 0) - (left ? 1 : 0);
  int v = (up ? 1 : 0) - (down ? 1 : 0);

  SetMoving(h != 0 || v != 0);
  SetViewDirection(h, v);
}

Coordinates DynamicObject::GetSpeedVector() const {
  switch (GetViewDirection()) {
    case ViewDirection::kLeft: return Coordinates({
      constants::kIsometricSpeedCoefficient,
      -constants::kIsometricSpeedCoefficient});
    case ViewDirection::kUpLeft: return Coordinates({0, -1});
    case ViewDirection::kUp: return Coordinates({-1, -1});
    case ViewDirection::kUpRight: return Coordinates({-1, 0});
    case ViewDirection::kRight: return Coordinates({
      -constants::kIsometricSpeedCoefficient,
      constants::kIsometricSpeedCoefficient});
    case ViewDirection::kDownRight: return Coordinates({0, 1});
    case ViewDirection::kDown: return Coordinates({1, 1});
    case ViewDirection::kDownLeft: return Coordinates({1, 0});
  }
}

void DynamicObject::Move() {
  if (!IsMoving()) {
    return;
  }
  SetCoordinates(GetCoordinates() + GetSpeedVector() * speed_);
}

bool DynamicObject::IsMoving() const {
  return is_moving_;
}

void DynamicObject::SetMoving(bool flag) {
  is_moving_ = flag;
}
