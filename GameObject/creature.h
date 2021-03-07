#ifndef GAMEOBJECT_CREATURE_H_
#define GAMEOBJECT_CREATURE_H_

#include <string>

#include "dynamic_object.h"
#include "destroyable.h"

class Creature : public DynamicObject, public Destroyable {
 public:
  Creature(Coordinates coords, const QPixmap& image, std::string name, int hp);

  std::string GetName() const;

 private:
  std::string name_;
};

#endif  // GAMEOBJECT_CREATURE_H_
