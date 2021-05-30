#include "storage.h"

Storage::Storage(const std::vector<Item>& items) {
  PutItems(items);
}

void Storage::PutItem(const Item& item) {
  if (items_.size() < constants::kMaxElementsInItemBar) {
    items_.emplace_back(item);
  }
}

Item Storage::RemoveItem(int index) {
  auto it = items_.begin() + index;
  Item item = *it;
  items_.erase(it);
  return item;
}

bool Storage::IsValidIndex(int index) const {
  return (index >= 0 && index < items_.size());
}

std::vector<Item> Storage::GetItems() const {
  return items_;
}

void Storage::PutItems(const std::vector<Item>& items) {
  for (const auto& item : items) {
    PutItem(item);
  }
}

bool Storage::HasLessItems(int amount) {
  return items_.size() < amount;
}

bool Storage::HasItem(const Item::Type& item_type) const {
  for (const auto& item : items_) {
    if (item.GetType() == item_type) {
      return true;
    }
  }
  return false;
}
