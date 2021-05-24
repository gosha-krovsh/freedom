#include "item.h"

Item::Item(Type type,
           const QString& name,
           const std::weak_ptr<QPixmap>& image) :
    type_(type),
    name_(name),
    image_(image) {}

QString Item::GetNameByType(Type type) {
  switch (type) {
    case Type::kRoba: {
      return "roba";
    }
  }
  return "";
};

QString Item::GetName() const {
  return name_;
}

Item::Type Item::GetType() const {
  return type_;
}

const std::weak_ptr<QPixmap>& Item::GetImage() const {
  return image_;
}
