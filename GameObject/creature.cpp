#include "creature.h"

#include <utility>

Creature::Creature(const Point& coords,
                   const QPixmap& image,
                   const QString& name,
                   int hp) : DynamicObject(coords, image),
                             Destroyable(hp),
                             name_(name) {}

const QString& Creature::GetName() const {
  return name_;
}

void Creature::Tick(int current_tick) {
  DynamicObject::Tick(current_tick);
}
