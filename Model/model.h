#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include <GameObject/action.h>
#include "GameObject/game_map.h"
#include "GameObject/hero.h"
#include <GameObject/bot.h>
#include "GameObject/schedule.h"

class Model {
 public:
  Model(const Schedule& schedule, std::unique_ptr<GameMap> game_map);

  const GameMap& GetMap() const;
  GameMap& GetMap();
  const Hero& GetHero() const;
  const std::vector<std::unique_ptr<Bot>>& GetBots() const;
  Hero& GetHero();
  const Schedule& GetSchedule() const;
  Time& GetTime();
  const Time& GetTime() const;

 private:
  std::unique_ptr<GameMap> map_;
  Hero hero_{Point(1, 1, 1)};
  Schedule schedule_;
  Time time_;
  std::vector<std::unique_ptr<Bot>> bots_;
  // {std::make_unique<Bot>("",Point(1, 1, 1)),};
    // std::make_unique<Bot>("",Point(1, 1, 1))};

};

#endif  // MODEL_MODEL_H_
