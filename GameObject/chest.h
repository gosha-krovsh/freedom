#ifndef GAMEOBJECT_CHEST_H_
#define GAMEOBJECT_CHEST_H_

#include "object.h"
#include "storable_object.h"

class Chest : public Object, public StorableObject {
 public:
  Chest(const Point& coords, const QPixmap& image,
        const std::vector<Item>& items = {});
};

#endif  // GAMEOBJECT_CHEST_H_
