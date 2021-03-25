#include "object.h"

Object::Object(const Point& coords, const QPixmap& image) :
    coordinates_(coords), image_(image) {}

void Object::Tick(int) {}

void Object::Draw(QPainter* painter) const {
  painter->save();

  int x = static_cast<int>(coordinates_.GetIsometricX() *
                           (constants::kSizeOfBlock / 2.));
  int y = static_cast<int>(coordinates_.GetIsometricY() *
                           (constants::kSizeOfBlock / 2.));

  painter->drawPixmap(x, y,
                      constants::kSizeOfBlock,
                      constants::kSizeOfBlock,
                      image_);

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
