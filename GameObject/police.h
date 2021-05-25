#ifndef GAMEOBJECT_POLICE_H_
#define GAMEOBJECT_POLICE_H_

#include "bot.h"

class Police : public Bot {
 public:
  Police(const QString& name,
         const Point& coords,
         int hp = constants::kPoliceHP);

  void Tick(int current_tick) override;
};

#endif  // GAMEOBJECT_POLICE_H_
