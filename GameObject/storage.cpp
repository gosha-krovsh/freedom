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
  items_.erase(it);
  return *it;
}

bool Storage::IsValidIndex(int index) const {
  return index < items_.size();
}

std::vector<Item> Storage::GetItems() const {
  return items_;
}

void Storage::PutItems(const std::vector<Item>& items) {
  for (const auto& item : items) {
    PutItem(item);
  }
}
