#include "chest.h"

Chest::Chest(const Point& coords,
             const std::weak_ptr<QPixmap>& image,
             const std::vector<Item>& items) :
    Object(coords, image) {
  storage_ = std::make_shared<Storage>();
  storage_->PutItems(items);
}
