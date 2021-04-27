#include "storable_object.h"

void StorableObject::PutItem(const Item& item) {
  if (items_.size() < constants::kMaxElementsInItemBar) {
    items_.emplace_back(item);
  }
}

Item StorableObject::RemoveItem(int index) {
  auto it = items_.begin() + index;
  items_.erase(it);
  return *it;
}

bool StorableObject::IsValidIndex(int index) {
  return index < items_.size();
}

std::vector<Item> StorableObject::GetItems() {
  return items_;
}

void StorableObject::PutItems(const std::vector<Item>& items) {
  for (const auto& item : items) {
    PutItem(item);
  }
}
