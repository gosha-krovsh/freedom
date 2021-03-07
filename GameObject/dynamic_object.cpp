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
    case kUp: {
      SetCoordinates(GetX() - speed_,
                     GetY() - speed_,
                     GetZ());
      break;
    }
    case kUpRight: {
      SetCoordinates(GetX() - speed_,
                     GetY(),
                     GetZ());
      break;
    }
    case kRight: {
      SetCoordinates(GetX() - speed_ / std::sqrt(3),
                     GetY() + speed_ / std::sqrt(3),
                     GetZ());
      break;
    }
    case kDownRight: {
      SetCoordinates(GetX(),
                     GetY() + speed_,
                     GetZ());
      break;
    }
    case kDown: {
      SetCoordinates(GetX() + speed_,
                     GetY() + speed_,
                     GetZ());
      break;
    }
    case kDownLeft: {
      SetCoordinates(GetX() + speed_,
                     GetY(),
                     GetZ());
      break;
    }
    case kLeft: {
      SetCoordinates(GetX() + speed_ / std::sqrt(3),
                     GetY() - speed_ / std::sqrt(3),
                     GetZ());
      break;
    }
    case kUpLeft: {
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
