#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <list>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include <GameObject/action.h>
#include <GameObject/bot.h>
#include "GameObject/game_map.h"
#include "GameObject/hero.h"
#include "GameObject/wall.h"
#include "GameObject/schedule.h"
#include "Quests/quest.h"

class Model {
 public:
  Model(const Schedule& schedule, std::unique_ptr<GameMap> game_map);
  ~Model();

  const GameMap& GetMap() const;
  GameMap& GetMap();
  const Hero& GetHero() const;
  const std::vector<Bot>& GetBots() const;
  std::vector<Bot>& GetBots();

  Hero& GetHero();
  const Schedule& GetSchedule() const;
  Time& GetTime();
  const Time& GetTime() const;

  const Quest& GetQuestById(int id) const;
  const std::list<Quest>& GetCurrentQuests() const;
  std::list<Quest>& GetCurrentQuests();

 private:
  Hero hero_{Point(1, 1, 1)};
  std::unique_ptr<GameMap> map_;
  Schedule schedule_;
  Time time_;
  std::vector<Bot> bots_;

  std::vector<Quest> quests_;
  std::list<Quest> current_quests_;
};

#endif  // MODEL_MODEL_H_
