#include "item.h"

Item::Item(Type type,
           const QString& name,
           const std::weak_ptr<QPixmap>& image) :
    type_(type),
    name_(name),
    image_(image) {}

QString Item::GetNameByType(Type type) {
  switch (type) {
    case Type::kPrisonerRoba: {
      return constants::kPrisonerClothesName;
    }
    case Type::kPoliceRoba: {
      return constants::kPoliceClothesName;
    }
  }
  return "";
}

QString Item::GetName() const {
  return name_;
}

Item::Type Item::GetType() const {
  return type_;
}

const std::weak_ptr<QPixmap>& Item::GetImage() const {
  return image_;
}

bool Item::IsUsable() const {
  switch (type_) {
    case Type::kApple:
    case Type::kSoap: {
      return true;
    }
    default: {
      return false;
    }
  }
}
