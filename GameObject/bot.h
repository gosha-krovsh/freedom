#ifndef GAMEOBJECT_BOT_H_
#define GAMEOBJECT_BOT_H_

#include <QDebug>

#include <memory>
#include <vector>

#include "creature.h"
#include "object.h"
#include "point.h"

class Bot : public Creature {
 public:
  Bot(const QString& name,
               const Point& coords, const Point& finish);

  void Tick(int current_tick) override;

  void OnDead() override;

  const Point& GetFinish() const;
  void SetFinish(const Point& new_finish);

  std::vector<Point> targets_;

 private:
  void MakeStep();

  int current_direction_{0};
  int order_{1};
  Point finish_;
};

#endif  // GAMEOBJECT_BOT_H_
