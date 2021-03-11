#include "creature.h"

#include <utility>

Creature::Creature(Coordinates coords,
                   const QPixmap& image,
                   QString name,
                   int hp) : DynamicObject(coords, image),
                             Destroyable(hp),
                             name_(std::move(name)) {}

const QString& Creature::GetName() const {
  return name_;
}
