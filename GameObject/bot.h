#ifndef GAMEOBJECT_BOT_H_
#define GAMEOBJECT_BOT_H_

#include <QDebug>

#include <memory>
#include <utility>
#include <vector>

#include "creature.h"
#include "object.h"
#include "point.h"

class Bot : public Creature {
 public:
  enum class Type {
    kPrisoner,
    kPolice
  };

  Bot(const QString& name,
      const Point& coords,
      int hp = constants::kHP,
      Type type = Type::kPrisoner);

  void Tick(int current_tick) override;
  void SetStorage(std::shared_ptr<Storage>&& storage);
  void OnDead() override;

  Type GetBotType() const;
  Point GetFinish() const;

  const std::vector<Point>& GetTargets();
  void SetTargets(const std::vector<Point>& targets);

 private:
  void MakeStep();

  std::vector<Point> targets_;
  void UpdateClothesName();
  std::vector<Point>::iterator current_point_{targets_.end()};
  Type type_;
};

#endif  // GAMEOBJECT_BOT_H_
