#include "object.h"

Object::Object(const Point& coords,
               const std::weak_ptr<QPixmap>& image,
               Type type) :
               coordinates_(coords),
               image_(image),
               type_(type) {}

void Object::Tick(int) {}

void Object::Draw(QPainter* painter) const {
  if (image_.expired()) {
    return;
  }
  painter->save();

  Point coords_to_draw = coordinates_ + GetDrawOffset();
  int x = static_cast<int>(coords_to_draw.GetIsometricX() *
                           (Settings::kBlockSize / 2.));
  int y = static_cast<int>(coords_to_draw.GetIsometricY() *
                           (Settings::kBlockSize / 2.));

  painter->drawPixmap(x, y,
                      Settings::kBlockSize,
                      Settings::kBlockSize,
                      *image_.lock());

  painter->restore();
}

Point Object::GetDrawOffset() const {
  return Point(0, 0);
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

int Object::GetFlooredX() const {
  return static_cast<int>(std::floor(GetX()));
}

int Object::GetFlooredY() const {
  return static_cast<int>(std::floor(GetY()));
}

bool Object::IsTouchable() const {
  return is_touchable_;
}

bool Object::IsStorable() const {
  return storage_ != nullptr;
}

bool Object::IsType(Object::Type object_type) const {
  return type_ == object_type;
}

bool Object::ToDelete() const {
  return delete_on_next_tick_;
}

void Object::Interact(const InteractingObject& interacting_object) {}

std::shared_ptr<Storage> Object::GetStorage() {
  return storage_;
}

std::shared_ptr<Storage> Object::GetClothingStorage() {
  return clothing_storage_;
}

std::shared_ptr<Storage> Object::GetGunStorage() {
  return gun_storage_;
}
