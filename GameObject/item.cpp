#include "item.h"

Item::Item(int id, const QString& name, const std::weak_ptr<QPixmap>& image) :
    name_(name),
    id_(id),
    image_(image) {}

QString Item::GetName() const {
  return name_;
}

int Item::GetId() const {
  return id_;
}

const std::weak_ptr<QPixmap>& Item::GetImage() const {
  return image_;
}
