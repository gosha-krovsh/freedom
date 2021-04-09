#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <map>
#include <utility>
#include <memory>
#include <vector>

#include <GameObject/action.h>
#include "GameObject/hero.h"
#include "GameObject/schedule.h"

class Model {
 public:
  using GameMap = std::vector<std::vector<std::vector<Object*>>>;

  explicit Model(const Schedule& schedule);

  const GameMap& GetMap() const;
  const Hero& GetHero() const;
  Hero& GetHero();
  const Schedule& GetSchedule() const;

  Time& GetTime();
  const Time& GetTime() const;

 private:
  std::vector<Object> objects_;
  GameMap map_;
  Hero hero_{Point(1, 6, 1)};

  Schedule schedule_;
  Time time_;

  std::shared_ptr<QPixmap>
      brick_image = std::make_shared<QPixmap>(":brick.png");

};

#endif  // MODEL_MODEL_H_
