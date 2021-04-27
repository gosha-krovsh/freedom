#ifndef GAMEOBJECT_CHEST_H_
#define GAMEOBJECT_CHEST_H_

#include "object.h"
#include "storage.h"

class Chest : public Object {
 public:
  explicit Chest(const Point& coords, const std::vector<Item>& items = {});

  static void SetImage(const std::shared_ptr<QPixmap>& image);
  static void DeleteImage();

 private:
  static std::shared_ptr<QPixmap> chest_image_;
};

#endif  // GAMEOBJECT_CHEST_H_
