#include "chest.h"

Chest::Chest(const Point& coords, const QPixmap& image,
             const std::vector<Item>& items) : Object(coords, image) {
  PutItems(items);
}
