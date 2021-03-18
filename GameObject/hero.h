#ifndef GAMEOBJECT_HERO_H_
#define GAMEOBJECT_HERO_H_

#include "creature.h"

class Hero : public Creature {
 public:
  explicit Hero(Point coords,
                const QPixmap& image = QPixmap(":hero_0.png"));

  void Tick(int current_tick) override;

  void OnDead() override;
};

#endif  // GAMEOBJECT_HERO_H_
