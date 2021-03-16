#ifndef GAMEOBJECT_CREATURE_H_
#define GAMEOBJECT_CREATURE_H_

#include <QString>

#include "dynamic_object.h"
#include "destroyable.h"

class Creature : public DynamicObject, public Destroyable {
 public:
  Creature(const Coordinates& coords, const QPixmap& image, QString name,
           int hp);

  const QString& GetName() const;

  void Tick(int current_tick) override;

 private:
  QString name_;
};

#endif  // GAMEOBJECT_CREATURE_H_
