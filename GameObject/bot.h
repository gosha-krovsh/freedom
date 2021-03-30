#ifndef BOT_H_
#define BOT_H_

#include "creature.h"
#include "route.h"

class Bot : public Creature {
 public:
  explicit Bot(const QString& name, Coordinates coords,
      const QPixmap& image = QPixmap(":hero_0.png"));

  void SetRoute(const Route& route);
  void Tick(int current_tick) override;

  void OnDead() override;
 private:
  void Move() override;

  Route* route_ = nullptr;
};

#endif // BOT_H_
