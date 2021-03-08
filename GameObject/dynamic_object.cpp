#include "dynamic_object.h"

DynamicObject::DynamicObject(Coordinates coords, const QPixmap& image)
  : Object(coords, image) {
  is_touchable_ = false;
}

ViewDirection DynamicObject::GetViewDirection() const {
  return view_direction_;
}
void DynamicObject::SetViewDirection(ViewDirection view_direction) {
  view_direction_ = view_direction;
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
