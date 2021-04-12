#ifndef BOT_H_
#define BOT_H_

#include "creature.h"
#include "route.h"
#include "point.h"

class Bot : public Creature {
 public:
  explicit Bot(const QString& name, Point coords,
      const QPixmap& image = QPixmap(":hero_0.png"));

  void SetRoute(const Route& route);
  void Tick(int current_tick) override;

  void OnDead() override;
 private:
  void Move();

  const std::vector<Point> possible_bot_targets_{Point(3, 7, 1), Point(3, 6, 1),
                                           Point(1, 6, 1), Point(1, 7, 1)};
  Route* route_ = nullptr;
};

#endif // BOT_H_
