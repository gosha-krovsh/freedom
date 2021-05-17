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

  void RebuildPath(const Point& new_finish, int stay_at_finish = 0);
  void Normalize();

  std::vector<Point> targets_;
  bool need_to_rebuild_{false};
  bool need_to_return_{false};
  Point base_start_{Point(-1, -1, -1)};
  Point base_finish_{Point(-1, -1, -1)};

 private:
  void MakeStep();

  int current_direction_{0};
  int order_{1};
  Point finish_;
  int stay_at_finish_{0};
  int current_stay_{0};
};

#endif  // GAMEOBJECT_BOT_H_
