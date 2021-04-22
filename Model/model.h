#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include <GameObject/action.h>
#include "GameObject/game_map.h"
#include "GameObject/hero.h"
#include "GameObject/schedule.h"

class Model {
 public:
  Model(const Schedule& schedule, std::unique_ptr<GameMap> game_map);
  ~Model();

  const GameMap& GetMap() const;
  GameMap& GetMap();
  const Hero& GetHero() const;
  Hero& GetHero();
  const Schedule& GetSchedule() const;
  Time& GetTime();
  const Time& GetTime() const;

 private:
  std::unique_ptr<GameMap> map_;
  Hero hero_{Point(1, 1, 1)};
  Schedule schedule_;
  Time time_;
};

#endif  // MODEL_MODEL_H_
