#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "GameObject/action.h"
#include "GameObject/hero.h"
#include "GameObject/wall.h"
#include "GameObject/schedule.h"

class Model {
 public:
  using GameMap = std::vector<std::vector<std::vector<Object*>>>;

  explicit Model(const Schedule& schedule);
  ~Model();

  const GameMap& GetMap() const;
  GameMap& GetMap();
  std::vector<Object*>& GetObjects();
  const Hero& GetHero() const;
  Hero& GetHero();
  const Schedule& GetSchedule() const;

  Time& GetTime();
  const Time& GetTime() const;

 private:
  GameMap map_;
  Hero hero_{Point(2, 7, 1)};

  Schedule schedule_;
  Time time_;
};

#endif  // MODEL_MODEL_H_
