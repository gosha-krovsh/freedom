#include "chest.h"

Chest::Chest(const Point& coords,
             const std::weak_ptr<QPixmap>& image,
             const std::shared_ptr<Storage>& storage) :
    Object(coords, image) {
  storage_ = storage;
}
