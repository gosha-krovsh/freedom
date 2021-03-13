#include "dynamic_object.h"

DynamicObject::DynamicObject(Coordinates coords, const QPixmap& image)
  : Object(coords, image) {
  is_touchable_ = false;
}

DynamicObject::ViewDirection DynamicObject::GetViewDirection() const {
  return view_direction_;
}

void DynamicObject::SetViewDirection(ViewDirection view_direction) {
  view_direction_ = view_direction;
}

void DynamicObject::SetMovingDirection(bool left, bool up,
                                       bool right, bool down) {
  int h = (right ? 1 : 0) - (left ? 1 : 0);
  int v = (up ? 1 : 0) - (down ? 1 : 0);

  SetViewDirection(ConvertVectorToViewDirection(h, v));
  SetMoving(std::abs(h) + std::abs(v) > 0);
}

double DynamicObject::GetSpeed() const {
  return speed_;
}

Coordinates DynamicObject::GetSpeedMultipliers() const {
  switch (GetViewDirection()) {
    case ViewDirection::kUp: return Coordinates({-1, -1, 0});
    case ViewDirection::kUpRight: return Coordinates({-1, 0, 0});
    case ViewDirection::kRight: return Coordinates({
     -constants::kHorizontalSpeedMultiplier,
      constants::kHorizontalSpeedMultiplier,
      0});
    case ViewDirection::kDownRight: return Coordinates({0, 1, 0});
    case ViewDirection::kDown: return Coordinates({1, 1, 0});
    case ViewDirection::kDownLeft: return Coordinates({1, 0, 0});
    case ViewDirection::kLeft: return Coordinates({
      constants::kHorizontalSpeedMultiplier,
     -constants::kHorizontalSpeedMultiplier,
      0});
    case ViewDirection::kUpLeft: return Coordinates({0, -1, 0});
  }
}


void DynamicObject::Move() {
  if (!IsMoving()) {
    return;
  }

  SetCoordinates(GetX() + speed_ * GetSpeedMultipliers().x,
                 GetY() + speed_ * GetSpeedMultipliers().y,
                 GetZ());
}

bool DynamicObject::IsMoving() const {
  return is_moving_;
}

void DynamicObject::SetMoving(bool flag) {
  is_moving_ = flag;
}

DynamicObject::ViewDirection
DynamicObject::ConvertVectorToViewDirection(int h, int v) {
  if (v > 0) {
    if (h > 0) {
      return ViewDirection::kUpRight;
    } else if (h < 0) {
      return ViewDirection::kUpLeft;
    } else {
      return ViewDirection::kUp;
    }
  } else if (v < 0) {
    if (h > 0) {
      return ViewDirection::kDownRight;
    } else if (h < 0) {
      return ViewDirection::kDownLeft;
    } else {
      return ViewDirection::kDown;
    }
  } else {
    if (h > 0) {
      return ViewDirection::kRight;
    } else if (h < 0) {
      return ViewDirection::kLeft;
    }
  }

  return view_direction_;
}

void DynamicObject::Tick(int current_tick) {
  Object::Tick(current_tick);
  Move();
}
