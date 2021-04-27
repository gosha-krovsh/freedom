#include "item.h"

Item::Item(int id, const QString& name, const QPixmap& image) :
    name_(std::move(name)),
    id_(id),
    image_(image){}

QString Item::GetName() const {
  return name_;
}

int Item::GetId() const {
  return id_;
}

const QPixmap& Item::GetImage() const {
  return image_;
}
