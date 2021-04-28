#include "object.h"

Object::Object(const Point& coords, const std::weak_ptr<QPixmap>& image)
  : coordinates_(coords), image_(image) {}

void Object::Tick(int) {}

void Object::Draw(QPainter* painter) const {
  if (image_.expired()) {
    return;
  }
  painter->save();

  int x = static_cast<int>(coordinates_.GetIsometricX() *
                           (constants::kSizeOfBlock / 2.));
  int y = static_cast<int>(coordinates_.GetIsometricY() *
                           (constants::kSizeOfBlock / 2.));

  painter->drawPixmap(x, y,
                      constants::kSizeOfBlock,
                      constants::kSizeOfBlock,
                      *image_.lock());

  painter->restore();
}

Point Object::GetCoordinates() const {
  return coordinates_;
}
double Object::GetX() const {
  return GetCoordinates().x;
}
double Object::GetY() const {
  return GetCoordinates().y;
}
double Object::GetZ() const {
  return GetCoordinates().z;
}
int Object::GetRoundedX() const {
  return static_cast<int>(std::round(GetX()));
}
int Object::GetRoundedY() const {
  return static_cast<int>(std::round(GetY()));
}
int Object::GetRoundedZ() const {
  return static_cast<int>(std::round(GetZ()));
}

void Object::SetCoordinates(const Point& coords) {
  coordinates_ = coords;
}
void Object::SetX(double x) {
  coordinates_.x = x;
}
void Object::SetY(double y) {
  coordinates_.y = y;
}
void Object::SetZ(double z) {
  coordinates_.z = z;
}

bool Object::IsTouchable() const {
  return is_touchable_;
}

int Object::GetFlooredX() const {
  return static_cast<int>(std::floor(GetX()));
}

int Object::GetFlooredY() const {
  return static_cast<int>(std::floor(GetY()));
}
