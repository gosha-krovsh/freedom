#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <map>
#include <utility>
#include <vector>

#include <GameObject/action.h>
#include "GameObject/hero.h"
#include "GameObject/schedule.h"

class Model {
 public:
  using GameMap = std::vector<std::vector<std::vector<Object*>>>;

  explicit Model(Schedule schedule);

  const GameMap& GetMap() const;
  const Hero& GetHero() const;
  Hero& GetHero();
  const Schedule& GetSchedule() const;

  Time& GetTime();
  const Time& GetTime() const;

 private:
  std::vector<Object> objects_;
  GameMap map_;
  Schedule schedule_;
  Time time_;
  Hero hero_{Point(1, 6, 1) };
};

#endif  // MODEL_MODEL_H_
