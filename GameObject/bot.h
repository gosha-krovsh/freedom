#ifndef GAMEOBJECT_BOT_H_
#define GAMEOBJECT_BOT_H_

#include <memory>
#include <vector>

#include "creature.h"
#include "route.h"
#include "point.h"

class Bot : public Creature {
 public:
  explicit Bot(const QString& name, Point coords, int direction);

  void SetRoute(const Route& route);
  void Tick(int current_tick) override;

  void OnDead() override;
 private:
  void Move();

  std::unique_ptr<Route> route_ = nullptr;
  int base_direction_;
  int current_direction_ = 0;
  std::vector<Point> possible_bot_targets{Point(1, 1, 1), Point(1, 6, 1),
                                          Point(4, 6, 1), Point(4, 1, 1),
                                          Point(7, 9, 1), Point(1, 9, 1),
                                          Point(7, 9, 1), Point(1, 9, 1)};
};

#endif  // GAMEOBJECT_BOT_H_
