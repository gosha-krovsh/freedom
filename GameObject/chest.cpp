#include "chest.h"

Chest::Chest(const Point& coords, const std::vector<Item>& items) :
    Object(coords, chest_image_) {
  storage_ = std::make_shared<Storage>();
  storage_->PutItems(items);
}

void Chest::SetImage(const std::shared_ptr<QPixmap>& image) {
  chest_image_ = image;
}

void Chest::DeleteImage() {
  chest_image_.reset();
}

std::shared_ptr<QPixmap> Chest::chest_image_;
