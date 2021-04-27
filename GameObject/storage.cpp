#include "storage.h"

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

bool Storage::IsValidIndex(int index) {
  return index < items_.size();
}

std::vector<Item> Storage::GetItems() {
  return items_;
}

void Storage::PutItems(const std::vector<Item>& items) {
  for (const auto& item : items) {
    PutItem(item);
  }
}
