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
void DynamicObject::SetMovingDirection(MovementCondition condition) {
  bool up = condition.up;
  bool right = condition.right;
  bool down = condition.down;
  bool left = condition.left;

  SetMoving(true);
  if (up && !down) {
    if (right && !left) {
      SetViewDirection(ViewDirection::kUpRight);
    } else if (left && !right) {
      SetViewDirection(ViewDirection::kUpLeft);
    } else {
      SetViewDirection(ViewDirection::kUp);
    }
  } else if (down && !up) {
    if (right && !left) {
      SetViewDirection(ViewDirection::kDownRight);
    } else if (left && !right) {
      SetViewDirection(ViewDirection::kDownLeft);
    } else {
      SetViewDirection(ViewDirection::kDown);
    }
  } else {
    if (right && !left) {
      SetViewDirection(ViewDirection::kRight);
    } else if (left && !right) {
      SetViewDirection(ViewDirection::kLeft);
    } else {
      SetMoving(false);
    }
  }
}

double DynamicObject::GetSpeed() const {
  return speed_;
}

void DynamicObject::Move() {
  if (!IsMoving()) {
    return;
  }

  switch (GetViewDirection()) {
    case ViewDirection::kUp: {
      SetCoordinates(GetX() - speed_,
                     GetY() - speed_,
                     GetZ());
      break;
    }
    case ViewDirection::kUpRight: {
      SetCoordinates(GetX() - speed_,
                     GetY(),
                     GetZ());
      break;
    }
    case ViewDirection::kRight: {
      SetCoordinates(GetX() - speed_ / std::sqrt(3),
                     GetY() + speed_ / std::sqrt(3),
                     GetZ());
      break;
    }
    case ViewDirection::kDownRight: {
      SetCoordinates(GetX(),
                     GetY() + speed_,
                     GetZ());
      break;
    }
    case ViewDirection::kDown: {
      SetCoordinates(GetX() + speed_,
                     GetY() + speed_,
                     GetZ());
      break;
    }
    case ViewDirection::kDownLeft: {
      SetCoordinates(GetX() + speed_,
                     GetY(),
                     GetZ());
      break;
    }
    case ViewDirection::kLeft: {
      SetCoordinates(GetX() + speed_ / std::sqrt(3),
                     GetY() - speed_ / std::sqrt(3),
                     GetZ());
      break;
    }
    case ViewDirection::kUpLeft: {
      SetCoordinates(GetX(),
                     GetY() - speed_,
                     GetZ());
      break;
    }
  }
}

bool DynamicObject::IsMoving() const {
  return is_moving_;
}
void DynamicObject::SetMoving(bool flag) {
  is_moving_ = flag;
}
