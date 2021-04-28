#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <list>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "image_manager.h"

#include "GameObject/action.h"
#include "GameObject/game_map.h"
#include "GameObject/hero.h"
#include "GameObject/wall.h"
#include "GameObject/schedule.h"
#include "Quests/quest.h"

class Model {
 public:
  Model();

  void SetMap(std::unique_ptr<GameMap>&& game_map);
  void SetSchedule(std::unique_ptr<Schedule>&& schedule);

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
  std::weak_ptr<QPixmap> GetImage(const QString& name);

  const Quest& GetQuestById(int id) const;
  const std::vector<Quest>& GetCurrentQuests() const;
  std::vector<Quest>& GetCurrentQuests();

  // Temp code for adding bots
  std::vector<Creature>& GetBots();

 private:
  std::unique_ptr<GameMap> map_;
  std::unique_ptr<Schedule> schedule_;
  Hero hero_{Point(1, 1, 1)};
  Time time_{Time(8, 30)};
  ImageManager image_manager;
  std::vector<Quest> quests_;
  std::vector<Quest> current_quests_;
  std::vector<std::pair<Creature*, Creature*>> fighting_pairs_;
  // Temp code for adding bots
  std::vector<Creature> bots_;
};

#endif  // MODEL_MODEL_H_
