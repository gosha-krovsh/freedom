#include "item.h"

Item::Item(Type type,
           const QString& name,
           const std::weak_ptr<QPixmap>& image) :
    type_(type),
    name_(name),
    image_(image) {}

QString Item::GetName() const {
  return name_;
}

Item::Type Item::GetType() const {
  return type_;
}

const std::weak_ptr<QPixmap>& Item::GetImage() const {
  return image_;
}

bool Item::IsUsable() {
  switch (type_) {
    case Type::kApple: {
      return true;
    }
    default: {
      return false;
    }
  }
}
