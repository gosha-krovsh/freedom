#ifndef GAMEOBJECT_BOT_H_
#define GAMEOBJECT_BOT_H_

#include <QDebug>

#include <memory>
#include <utility>
#include <vector>

#include "creature.h"
#include "object.h"
#include "point.h"

class Bot : public Creature, public InteractingObject{
 public:
  Bot(const QString& name, const Point& coords);

  void Tick(int current_tick) override;
  void SetStorage(std::shared_ptr<Storage>&& storage);
  void OnDead() override;

  Point GetFinish() const;
  void SetFinish(const Point& new_finish);
  void Rebuild();

  double GetX() const override;
  double GetY() const override;
  int GetRoundedX() const override;
  int GetRoundedY() const override;
  int GetAttack() const override;

  const std::vector<Point>& GetTargets();
  void SetTargets(const std::vector<Point>& targets);

 private:
  void MakeStep();

  std::vector<Point> targets_;
  int current_index_in_path_{0};
  Point finish_;
};

#endif  // GAMEOBJECT_BOT_H_
