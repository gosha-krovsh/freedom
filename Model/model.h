#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "GameObject/action.h"
#include "GameObject/game_map.h"
#include "GameObject/hero.h"
#include "GameObject/wall.h"
#include "GameObject/schedule.h"

class Model {
 public:
  Model(const Schedule& schedule, std::unique_ptr<GameMap> game_map);
  ~Model();

  void CreateFightingPair(Creature* first, Creature* second);
  void DeleteFightingPair(const std::pair<Creature*, Creature*>& pair);
  std::pair<Creature*, Creature*> GetFightingPairWithIndex(int index);
  int GetNumberOfFightingPairs() const;

  const GameMap& GetMap() const;
  GameMap& GetMap();
  const Hero& GetHero() const;
  Hero& GetHero();
  const Schedule& GetSchedule() const;
  Time& GetTime();
  const Time& GetTime() const;

  // Temp code for adding bots
  std::vector<Creature>& GetBots();

 private:
  Hero hero_{Point(1, 1, 1)};
  std::unique_ptr<GameMap> map_;
  Schedule schedule_;
  Time time_;
  std::vector<Creature> bots_;
  std::vector<std::pair<Creature*, Creature*>> fighting_pairs_;
};

#endif  // MODEL_MODEL_H_
