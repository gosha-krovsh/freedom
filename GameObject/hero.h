#ifndef GAMEOBJECT_HERO_H_
#define GAMEOBJECT_HERO_H_

#include "creature.h"

class Hero : public Creature {
 public:
  explicit Hero(Coordinates coords,
                const QPixmap& image = QPixmap(":hero_0.png"));

  void OnDead() override;
};

#endif  // GAMEOBJECT_HERO_H_
