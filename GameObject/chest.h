#ifndef GAMEOBJECT_CHEST_H_
#define GAMEOBJECT_CHEST_H_

#include <memory>
#include <vector>

#include "object.h"
#include "storage.h"

class Chest : public Object {
 public:
  Chest(const Point& coords,
        const std::weak_ptr<QPixmap>& image,
        const std::shared_ptr<Storage>& storage = {});
};

#endif  // GAMEOBJECT_CHEST_H_
