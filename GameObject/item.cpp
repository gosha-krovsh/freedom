#include "item.h"

Item::Item(std::string name, int id, const QPixmap& image) :
  name_(std::move(name)),
  id_(id),
  image_(image){}

std::string Item::GetName() const {
  return name_;
}

int Item::GetId() const {
  return id_;
}

QPixmap& Item::GetImage() {
  return image_;
}
