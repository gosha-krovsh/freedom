#include "image_manager.h"

std::map<QString, std::shared_ptr<QPixmap>> ImageManager::images_{};

std::weak_ptr<QPixmap> ImageManager::GetImage(const QString& name) {
  auto iter = images_.find(name);

  if (iter != images_.end()) {
    return iter->second;
  } else {
    std::shared_ptr<QPixmap> image =
        std::make_shared<QPixmap>(":" + name + ".png");
    images_[name] = image;
    return image;
  }
}

void ImageManager::Wipe() {
  images_.clear();
}
