#include "object.h"

Object::Object(Coordinates coords, const QPixmap& image) : coordinates_(coords),
                                                           image_(image) {}

void Object::Draw(QPainter* painter) const {
  painter->save();

  int x =
      static_cast<int>(coordinates_.GetIsometricX() * (constants::kSizeOfBlock / 2.));
  int y =
      static_cast<int>(coordinates_.GetIsometricY() * (constants::kSizeOfBlock / 2.));

  painter->drawPixmap(x, y,
                      constants::kSizeOfBlock,
                      constants::kSizeOfBlock,
                      image_);

  painter->restore();
}

Coordinates Object::GetCoordinates() const {
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

void Object::SetCoordinates(Coordinates coords) {
  coordinates_ = coords;
}
void Object::SetCoordinates(double x, double y, double z) {
  SetCoordinates(Coordinates(x, y, z));
}

bool Object::IsTouchable() const {
  return is_touchable_;
}
