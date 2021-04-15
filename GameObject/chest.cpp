#include "chest.h"

Chest::Chest(const Point& coords, const QPixmap& image) :
    Object(coords, image) {}

Chest::Chest(const Point& coords, const QPixmap& image,
             const std::vector<Item>& items) : Chest(coords, image) {
  for (auto& item : items) {
    PutItem(item);
  }
}
