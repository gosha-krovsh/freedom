#include "storable_object.h"

void StorableObject::PutItem(const Item& item) {
  if (items_.size() < constants::kMaxElementsInItemBar) {
    items_.emplace_back(item);
  }
}

Item StorableObject::RemoveItem(int index) {
  auto it = items_.begin() + index;
  Item item = *it;
  items_.erase(it);

  return item;
}

bool StorableObject::isValidIndex(int index) {
  return index < items_.size();
}

std::vector<Item> StorableObject::GetItems() {
  return items_;
}
