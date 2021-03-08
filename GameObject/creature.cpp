#include "creature.h"

#include <utility>

Creature::Creature(Coordinates coords,
                   const QPixmap& image,
                   std::string name,
                   int hp) : DynamicObject(coords, image),
                             Destroyable(hp),
                             name_(std::move(name)) {}

const std::string& Creature::GetName() const {
  return name_;
}
